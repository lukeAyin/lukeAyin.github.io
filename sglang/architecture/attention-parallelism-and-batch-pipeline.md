---
layout: toc
title: "KV 分块、算子并行与 batch 流水"
description: "分页、tile、split-KV、chunked prefill、overlap 与 PP 的边界"
---

# KV 分块、算子并行与 batch 流水

状态：第一阶段补充学习，跨阶段概念辨析；不代表已完成算子或 overlap 专题。
源码基线：`0957288be0818686034f33a3a7441434e4f5ba33`，核对日期：2026-10-19。
证据：本地源码核对及 [PyTorch 的 Flash-Decoding 原理说明](https://pytorch.org/blog/flash-decoding/)，未运行硬件实验。

## 1. “分块”与“流水”分别指什么

| 机制 | 划分的对象 | 主要作用 | 是否直接针对一个 attention 调用内部的并行利用率 |
| --- | --- | --- | --- |
| KV 存储分页 | KV 缓存的物理存储 | 分配、回收、复用与非连续寻址 | 否；分页不自动等于计算负载均衡 |
| attention 内部 tile | 一个计算任务访问的 Q/K/V 区域 | 控制局部存储、访存与计算粒度 | 取决于任务组织；循环处理 tile 本身不保证增加独立并行任务 |
| split-KV | 一个 query/head 所需访问的 KV 序列范围 | 增加可并行的子任务，最后归并结果 | 是，但是否启用和如何切分取决于后端与形状 |
| chunked prefill | prompt 的本轮输入范围 | 控制单轮 prefill 工作量和调度节奏 | 否，是多轮模型执行的组织方式 |
| overlap 调度 | CPU 调度/结果处理与设备执行 | 减少设备等待 CPU 的空隙 | 否，属于 batch 执行与主机工作的重叠 |
| PP 流水 | 模型层的不同 stage 和多个 microbatch | 让多个设备 stage 并行处理不同 microbatch | 否，属于跨设备执行组织 |

## 2. 本仓库可确认的 split-KV 实现

以下路径相对 `python/sglang/`：

- `srt/layers/attention/triton_backend.py` 的 `get_num_kv_splits()` 准备拆分数，decode 调用传入逐请求长度与 split 元数据。
- `kernels/ops/attention/decode_attention.py` 的普通 decode stage 1 使用 `(batch, head, split)` 的 grid 组织任务，读取当前请求的 `num_kv_splits`，计算该 split 的 KV 起止范围。
- 每个 split 内继续按 `BLOCK_N` 循环处理 KV tile；这与 split 之间的独立任务并行是两种粒度。
- stage 1 写出局部 attention 输出与 log-sum-exp；`_fwd_kernel_stage2()` 按归一化信息合并各 split 的结果。

因此，可以确认仓库内存在沿 KV 长度拆分并行计算的 attention 实现。但不能将这一结论泛化为所有 SGLang attention 后端都采用相同任务划分。

进一步核对 `kernels/ops/attention/metadata.py` 的 `get_num_kv_splits_triton()`：普通动态规划路径同时考虑两类因素。一类使用 batch 内最长/最短长度推导 chunk 大小，另一类参考序列数、head/GQA 分组提供的并行任务数、设备核心数与序列长度启发式；最终产生逐请求 split 数并受配置影响。

例如 `[1024, 1024, 8192]` 且 split 上限足够时，单看最长/最短长度这一项，会得到 1024 的 chunk 大小，对应 `[1, 1, 8]` 个 split。最终拆分数还要结合核心利用率等另一项，不能将此例当作最终运行结果。`triton_backend.py` 中还存在固定拆分和确定性配置分支，不是所有配置都执行相同启发式。

例如一个请求的 KV 为 8,192 个位置，可以概念性地拆成 8 段，每段 1,024 个位置。query 保持同一个，8 个子任务分别计算局部结果，再归并。这个切分比例只是说明原理，不是当前默认配置或自动规划策略的承诺。split 过多会增加中间结果、启动与归并开销；batch/head 维度已经提供足够并行度时，继续拆分未必收益更高。

### 拆分数是固定还是动态

两种方式都存在，并且“固定份数”和“固定每段长度”不同。以下是当前 Triton 后端 `get_num_kv_splits()` 的分支，不代表 Ascend 算子内部策略：

| 模式 | 代码条件与行为 | 变化方式 |
| --- | --- | --- |
| 固定拆分份数 | 非确定性模式下，启用 `static_kv_splits` 或无法取得有效核心数时，将每请求拆分数设为 `max_kv_splits` | 请求长度不同，则各 split 覆盖的实际范围不同；还受计算块对齐与空 split 处理影响 |
| 固定目标段长度 | 确定性模式且存在 `split_tile_size` 时，份数为 `ceil(seq_len / split_tile_size)` | 段长度目标固定，实际份数随请求长度改变；最后一段可不足目标长度 |
| 动态启发式 | 其他对应路径调用 `get_num_kv_splits_triton()` | 使用当前 batch 长度分布、请求/head 分组、设备核心数及拆分上限，产生逐请求 split 数 |

初始化中静态拆分开关默认关闭；确定性与其他执行配置可能改变所走分支。因此不能只凭 `max_kv_splits` 就认定每个请求始终使用同样的实际拆分数。

普通 decode 的 forward metadata 初始化会分配 `num_kv_splits` 数组，并传入本轮序列长度计算它；图执行的相关 capture/replay metadata 更新路径也调用这一规划函数。动态规划是对当前执行元数据的计算，不是模型启动时仅计算一次。长度或 batch 成员变化后会重新评估，但由于阈值、对齐和上限，结果不一定每轮变化。

同时要区分“逻辑有效 split 数”“预分配中间 buffer 大小”和“kernel launch grid”。本仓库部分路径按最大 split 数预分配/启动，再由有效长度和 split 范围决定哪些任务有实际计算，不能把这些数量无条件视为同一个值。

固定段长示例：目标 1024，长度 `[1024, 2048, 8192]` 对应份数 `[1, 2, 8]`。固定份数示例：都设为 8，则各自 KV 范围大致分成 8 份，短序列可能存在对齐或无有效范围的任务。动态模式则不能仅用上述任一固定公式概括。

对性能仿真，记录拆分模式、有效拆分数/长度分布、配置上限和后端比强行假设固定 1024 更合理。若代价提供器只给整体算子耗时，可以由该提供器内部吸收拆分影响；不要求当前就实现一个设备级 split 调度器。

补充精度说明：上述固定“段长”是规划份数的目标粒度，后续普通 kernel 会结合规划份数和 32-token 对齐重新计算实际边界，不一定每段都恰等于目标值。变量表、两个动态提议、完整数值演算与 FFN 任务划分见 [get_num_kv_splits 逐步解读](kv-split-planner-walkthrough.md)。

## 3. 为什么分块结果不能直接相加

attention 的 softmax 分母覆盖全部可见 key。各 split 内单独归一化得到的输出不能直接相加或平均。

设第 i 个 split 保存局部输出 O_i 和该 split 分数的 log-sum-exp s_i，数学上可以用权重 `exp(s_i) / sum_j exp(s_j)` 合并 O_i；实际实现采用稳定的最大值重标定等方式避免溢出。这与本仓库 stage 1 保存 `Att_Lse`、stage 2 归并的结构对应。Flash-Decoding 的原理说明也明确包含 KV 切分、并行局部计算和带归一化信息的归并三步。

这一方式保留全量 attention 的数学语义，浮点计算的归约顺序可能使结果存在微小数值差异。

### 为什么不是每个算子、每次 attention 都使用 split-KV

- split-KV 针对 attention 沿 KV 序列范围的归约。QKV 投影、MLP、RoPE 没有“对历史 KV 做 attention”这一计算，不能直接套用它；GEMM 的 split-K 等属于其他计算轴的优化。
- decode 的 query 长度通常为 1，小 batch 下仅按请求/head 分工可能无法充分占用设备；长 KV 又让少数任务执行很久，split-KV 能增加独立任务并改善长任务的分工。这既针对并行度不足，也可缓解批内长度差异导致的尾部效应。
- prefill 往往有较多 query 位置，可沿 query 维度提供并行任务；batch/head 任务数已经很多时，也可能没有必要继续拆 KV。prefill 并非数学上禁止 split-KV，是否值得取决于形状与实现。
- 拆分会增加局部结果及归一化信息的写入/读取、归并计算和调度开销，部分 query/元数据也可能重复处理。短 KV、已有足够并行度或其他资源成为瓶颈时，收益可能不足以抵消开销。
- split-KV 不减少全量 attention 需要处理的逻辑 KV 范围，也不会无限增加有效带宽；其收益是改进任务组织和资源利用，不是去掉历史上下文。
- 硬件、数据布局、量化、mask、图模式和确定性要求影响可用实现；有的后端内部融合这些步骤，有的使用不同任务规划。仅看外部 API 是否有 `split` 参数不能判断内部是否切分。

### split 任务不会变成后续 FFN 的输入 token

拆分只扩展 attention 内部的工作维度；归并后，每个原 query/head 仍输出一个向量。三个 decode 请求的 KV 长度即使是 1K/1K/8K，按示例拆成 1/1/8 个任务后，模型的当前 token 数仍为三个。QKV 投影和 FFN 不会继承十个 split 槽位。

因此不能把某个请求在 attention 使用的计算资源理解为贯穿整个 forward 的固定分区。不同算子会按自身输入形状和实现调度设备任务；小 batch FFN 仍可能存在利用率问题，但与“保留了七个无效 split token”是两回事。详见 [功能文档中的总结校正](../features/01-requests-and-scheduling.md)。

## 4. Ascend 路径能确认到哪里

`srt/hardware_backend/npu/attention/ascend_backend.py` 的 `forward_decode()` 在相应 FIA 分支将以下信息传入 `npu_fused_infer_attention_score`：

- query 与 paged K/V；
- `block_table`、`block_size`；
- `actual_seq_lengths_kv`；
- query/KV head 数和缩放参数。

这些代码证明后端按真实长度和页表调用 NPU attention 算子。SGLang 调用位置没有展示这个算子内部如何分核、是否 split-KV、拆分数量如何选择，不能仅凭 block table 推断内部策略；需要目标 CANN/算子版本的实现、说明或 profiling 继续确认。

因此，仿真中不能把 Triton 的 split 规则无条件当作 Ascend 的规则。当前先保留 NPU 批量算子边界和完整形状/长度信息，耗时打桩；内部任务结构若要细化，必须标记假设和适用后端。

## 5. batch 流水与 split-KV 的关系

### CPU 与设备的 overlap

`srt/managers/scheduler.py` 的 `event_loop_overlap()` 使用 `result_queue`，交错当前 batch 的提交、上一 batch 的结果处理以及当前 batch 的采样安排。`run_batch()` 中还有 stream 依赖和结果复制等机制。

它允许设备执行某轮 forward 时，CPU 做可独立完成的调度/结果处理工作。它不意味着相邻两轮依赖 token 的 forward 可以任意并行，也不意味着长请求尚未结束时，短请求就自动绕开批量同步进入下一层。

可以将嵌套关系理解为：

```text
batch/主机时间组织：CPU 的调度和结果处理，与设备执行重叠
  └─ 某个设备 forward
       └─ 某一层 attention
            └─ 可能采用 split-KV 子任务并行与归并
```

两者能够同时使用。split-KV 改变设备算子时长，间接改变可重叠的时间窗口；overlap 本身不负责重新分配 attention 内部任务。

### 多设备的 PP 流水

若“流水 batch”指 pipeline parallelism，入口是 `srt/managers/scheduler_pp_mixin.py` 的 `event_loop_pp()`。不同设备运行不同模型 stage，多个 microbatch 经 stage 间传递，涉及中间张量、结果的收发和处理。

PP 的负载不均衡主要体现在 stage 工作量、通信和流水空隙。stage 内部仍可采用 split-KV，但二者处在不同层级。本次仅确认 PP 入口及职责，未展开其调度算法。

## 6. 对性能模型的要求

- 存储分页、算子耗时、batch 事件和 PP stage 依赖分别建模，不把它们合成一种“分块”。
- 如果耗时表返回整个 attention 调用的时间，其内部 split 与归并代价应包含在内；不能再重复追加一遍。
- 如果显式模拟算子内部任务，就要包含局部计算、归并、资源竞争与依赖，不能把所有 split 时长机械相加。
- 真实 overlap/PP 调度保持原有路径，设备完成事件按建模时间满足真实等待语义。

关联文档：[请求与调度功能](../features/01-requests-and-scheduling.md)、[调度循环架构](01-scheduler-loop.md)。
