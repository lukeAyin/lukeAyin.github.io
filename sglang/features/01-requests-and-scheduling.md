---
layout: default
title: "请求、batch 与调度主循环"
description: "Qwen2 prefill/decode、请求与 batch、KV 位置和调度主循环"
---

# 请求、batch 与调度主循环

状态：学习中，第一讲覆盖普通文本生成主路径；准入预算细节、回退和取消待继续学习。
源码基线：`0957288be0818686034f33a3a7441434e4f5ba33`，核对日期：2026-10-19。
验证方式：源码阅读与手工推演，未运行模型或仿真实验。

对应架构：[调度循环与模型执行](../architecture/01-scheduler-loop.md)。

## 1. 本讲配置与符号

用 Qwen2 风格的 decoder-only 模型解释普通自回归生成。假设单 rank、关闭 overlap 和投机解码，无前缀命中，内存充足，prompt 不分块，关闭 prefill/decode 混合，无额外 prefill 延迟策略。这里只分析生成路径，不包括 embedding、beam search、多模态与 PD 分离。

以下 token 用抽象符号表示，不假定一个汉字等于一个 token，也不代表某组真实权重的实际输出。位置从 0 开始。H 表示 hidden size，V 表示词表大小。

## 2. 三类关键对象

| 对象或状态 | 职责 | 本讲关注内容 |
| --- | --- | --- |
| `Req` | 一次生成请求的长期状态 | `origin_input_ids`、`output_ids`、采样/停止参数、KV 相关状态 |
| `ScheduleBatch` | 一组请求某次执行的组织方式 | `reqs`、`forward_mode`、输入 token、序列长度、扩展长度与 KV 写入位置 |
| `waiting_queue` | 等待被调度的请求 | 调度器从中选择可准入的请求，也可能包含被回退的请求 |
| `running_batch` | 持续生成请求的工作集合 | 在后续 decode 继续执行；成员会合并或过滤，不是永远固定的 batch |
| `last_batch` | 上次提交的 batch | 用于 prefill 之后的合并等跨轮协调；不能当作“所有历史请求” |

请求经过多轮执行产生多个输出 token。batch 是当前执行单位；多请求可以共享同一次模型执行，但各自的上下文、KV 索引和结束状态独立。

## 3. 从请求到 prefill

文本经 tokenizer 转为 token ID，Scheduler 接收已分词请求。普通请求的 `handle_generate_request()` / `_handle_generate_request()` 创建 `Req`，经相应路径进入待调度队列。

`get_next_batch_to_run()` 在本讲配置下先尝试构造可运行的 prefill batch；`PrefillAdder` 等逻辑检查预算和容量。不是队列里有多少请求就全部执行。没有可执行 prefill 时，才尝试推进 running batch 的 decode。

被选中的请求通过 `ScheduleBatch.init_new()` 组成 batch，再调用 `prepare_for_extend()`：

- 设定 `ForwardMode.EXTEND`。
- 从各请求取待计算部分：`r.get_fill_ids()[r.prefix_len:]`。
- 汇总 `extend_num_tokens`，构造长度信息并准备扁平化 token 输入。
- `alloc_for_extend()` 分配本轮所需的 KV 写入位置。

本讲无缓存命中，因此待计算部分就是全部 prompt。一般情形下，EXTEND 也可能处理未命中的后缀或一个 prefill chunk，不能一律理解为重新计算全部 prompt。

## 4. 结合 Qwen2 看第一次模型执行

请求 A 的 prompt 为 `[p0, p1, p2, p3]`，最多生成 3 个 token。

一次完整 prefill 的逻辑计算：

```text
input_ids [4]，positions [0, 1, 2, 3]
    → Embedding：hidden_states [4, H]
    → 逐个 decoder layer
        → 归一化与残差处理
        → QKV 投影 → Q/K 的 RoPE
        → causal attention，并保存本层输入位置的 K/V
        → 输出投影、归一化/残差、MLP
    → 最终归一化
    → LogitsProcessor / LM head
    → 本请求末尾位置的 next-token logits [1, V]
    → 按采样参数选择第一个输出 token a1
```

这是语义图，不表示每个方框都是独立设备 kernel；归一化/残差等可能经 boundary 或融合实现。

prefill 能一起处理已知 prompt 的多个位置。因果 attention 保证位置 i 只使用允许的历史位置，不会让未来 token 泄漏。各位置输出的作用是预测其后续 token；普通生成取 prompt 最后一个位置的 logits 来产生 a1。

源码对应：`Qwen2Model.forward()` 执行 embedding、decoder layers 与 final norm；`Qwen2Attention.forward()` 执行 QKV 投影、RoPE、`RadixAttention` 和输出投影；`Qwen2ForCausalLM.forward()` 调用 logits processor。无额外 logprob 等要求的普通 extend 路径会按各请求的最后位置选择 hidden state，避免将每个 prompt 位置都当作新的生成结果。

KV Cache 保存各层的 K/V，用于下一轮 attention；不是保存“下一次输出答案”，也不意味着后续无需执行所有层。

## 5. decode 为什么只输入一个 token

prefill 已产生 a1，但它此时只是采样出的 ID，还没有作为模型输入通过各层。下一轮输入 a1，才生成 a1 对应的各层 K/V，并据此预测 a2。

| 模型执行 | 新输入 | 本轮输入位置 | 各层可用的 KV 位置数（计算后、释放前） | 新输出 |
| --- | --- | --- | --- | --- |
| prefill | p0、p1、p2、p3 | 0、1、2、3 | 4 | a1 |
| decode 1 | a1 | 4 | 5 | a2 |
| decode 2 | a2 | 5 | 6 | a3 |

表中 KV 数量表示该请求在每层的逻辑位置数，不是显存字节或跨层总量。若 a3 达到长度上限，请求就结束，不必再输入 a3 做一次 forward。

decode 同样通过 embedding 和所有 decoder layers。区别是本轮只为一个新输入位置计算 Q/K/V，attention 的 Q 是新位置，而 K/V 包含缓存的历史与当前新位置。因此输入 token 数很少，attention 仍需读取历史上下文；相同 decode batch size、不同上下文长度的代价可能不同。

### 为什么历史长度影响 decode attention 的工作量

用户提出：每轮只计算新 token 的 K/V，是否因为历史 KV 数量不同，导致 Q 与 KV 的计算量不同？对普通全量 causal attention，理解正确；具体包含 Q 与所有可见 K 的打分，以及按分数对所有可见 V 加权求和。

以一层的一个 attention head 为例，设已经缓存 L 个历史位置，当前新增一个输入位置，head dimension 为 d，且 Q/K/V 的 head dimension 相同。以下形状为数学视图，不要求设备实际拼接成连续张量：

```text
当前输入投影：q_new [1, d]，k_new [1, d]，v_new [1, d]
历史加当前：K_all [L+1, d]，V_all [L+1, d]

scores  = q_new @ K_all.T / sqrt(d)     # [1, L+1]
weights = softmax(scores)              # [1, L+1]
output  = weights @ V_all              # [1, d]
```

Q/K 可在打分前应用 RoPE；这里省略了位置处理与其他实现细节，聚焦序列长度维度。

- 新 Q/K/V 的投影只处理当前 token，在固定模型与 batch 条件下，其矩阵规模不随 L 增长。
- QK 打分需要与 L+1 个 key 计算点积；加权求和需要处理 L+1 个 value，二者算术工作量均为 O((L+1)d)，softmax 为 O(L+1)。
- KV Cache 避免重新计算历史 K/V，但这些历史 K/V 仍参与当前 attention，需要被读取。
- 输出始终是 `[1, d]`，输出形状相同不代表内部计算量相同。

例如总可见 KV 长度分别为 1,024 和 8,192 时，一个 head 分别需要 1,024 和 8,192 个打分项，并对相应数量的 V 加权；这部分的算术规模约差 8 倍。整个 decode 步骤还包括投影、MLP 等工作，实际时延也取决于带宽、并行和 kernel 实现，不能据此断言整轮慢 8 倍。

此分析针对普通全量 attention。滑动窗口、稀疏 attention 应按实际访问的 KV 位置计算；线性 attention 使用不同计算形式。GQA/MQA 改变 KV head 数与共享关系，但不消除普通 attention 中对可见序列位置的访问。因此性能代价查询应记录 attention 类型、新 query 数、实际可见 KV 长度、head 数/维度和 dtype 等信息。

`prepare_for_decode()` 在普通路径设定 `DECODE`，通过 `alloc_for_decode(..., token_per_req=1)` 为每个请求申请新位置，并增加序列长度。输入来自前次执行结果的传递路径；此函数不重新计算整个历史 prompt。

## 6. 执行结果如何回到真实状态

`TpModelWorker.forward_batch_generation()` 将 batch 转为 `ForwardBatch`，调用 `ModelRunner.forward()` 得到 logits，再在本讲普通非 overlap 路径采样 `next_token_ids`。

Scheduler 的 `process_batch_result()` 根据模式分派到 `batch_result_processor`。普通 prefill 的结果处理会追加输出 token，调用 `Req.update_finish_state()`，并根据是否结束处理 KV 生命周期；decode 也会提交生成结果并检查结束状态。

结束条件包括长度上限、EOS/停止规则等，具体受请求参数影响。没结束的请求继续参与后续执行；结束请求经结果处理和后续过滤退出活动集合。释放请求不等于所有 KV 立即成为空闲，可能保留为可复用的前缀缓存。

普通场景下，prefill 后仍在生成的请求会在下一次 `get_next_batch_to_run()` 中从 last batch 合并到 running batch。这个状态转换在真实调度中完成，不由仿真代码预先安排。

## 7. 两个请求如何连续组 batch

仍用上述配置。A 的 prompt 长度为 4，输出长度为 3；B 的 prompt 长度为 3，输出长度为 2。没有提前 EOS；B 在 A 的 prefill 期间到达，并在下一轮接收时可见。

| 轮次 | 调度选择 | 本轮实际新输入 | 输出 | 状态变化 |
| --- | --- | --- | --- | --- |
| 1 | A prefill | A 的 4 个 prompt token | a1 | A 等待后续生成 |
| 2 | B prefill | B 的 3 个 prompt token | b1 | A 本轮未 decode；B 随后可并入 running batch |
| 3 | A、B decode | `[a1, b1]`，两个 token | a2、b2 | B 达到 2 个输出，结束 |
| 4 | A decode | `[a2]`，一个 token | a3 | A 达到 3 个输出，结束 |

这是在明确假设下的源码推演，不是运行日志或所有配置的固定结果。prefill 延迟、混合批次、chunked prefill、内存不足和 overlap 都可能改变顺序。

第 3 轮的两个新 token 可组成 `[2, H]` 的 hidden states，通过同一套模型权重计算。A 的 attention 使用 A 的上下文，B 使用 B 的上下文；batch 元数据与 KV 索引区分请求，不会把它们当成一条相互可见的序列。

连续批处理允许新请求在执行过程中加入、结束请求退出。batch size 因而是每轮的运行结果，不能在性能模型中假定永远不变。

## 8. 对性能仿真的直接要求

- 真实调度决定上表的 batch 成员、执行模式和资源变化；仿真不能直接写死这张时间表。
- 代价输入至少要区分新计算 token 数与各请求历史长度；只看请求数不足以刻画 prefill/decode 工作量。
- 操作耗时来自打桩表，但请求到达、执行完成、结果可见时机必须反馈到真实调度。
- a1/a2 等结果可以由执行端约定的机制提供，但必须通过真实结果处理与结束判断；不能直接将请求改成“已完成”。
- 本讲未核对具体 NPU kernel 列表、真实性能、异步事件适配或完整服务端计时范围。

### 不同 KV 长度与 batch 内工作量不均衡

性能模型需要评估不同 KV 长度造成的 forward 耗时差异，但预测单位通常应是实际批量执行的算子及整个 batch，而不是先得到各请求独立 forward 耗时再相加或取最大值。

普通 dense 模型的 decode 中，每个请求本轮提供一个新 token。固定模型、dtype 和并行配置时，投影与 MLP 的主要矩阵形状由本轮 token 数决定；attention 还取决于每个请求的可见 KV 长度。MoE、图模式和其他配置会增加额外因素。

例：一个 decode batch 的可见 KV 长度为 `[1024, 1024, 8192]`。三个 query 的逻辑打分项总数为 `10240`（按一个 query head 计）；如果按最大长度完整 padding 后都计算，形状规模会是 `3 × 8192 = 24576`。这是两种工作量视图，不代表当前后端一定执行其中某个精确数量。实际 kernel 会涉及分块、对齐、mask、共享、padding 和工作分配。

项目已有表示不同请求长度的接口：`ForwardBatch.seq_lens` 等字段携带长度信息，Ascend attention 后端维护序列长度和 block table，并在相应算子调用中传入实际长度。接口支持逐请求长度不等于已经证明 kernel 的负载完全均衡，也不能据此推断它一定没有 padding 或额外开销。

“平衡”需要分三个层面理解：

| 层面 | 谁负责 | 对我们当前方案的要求 |
| --- | --- | --- |
| 组 batch：哪些长短请求放在一起 | 真实 Scheduler 与既有策略 | 保留真实决定，不在仿真器里重新按长度组批 |
| 批量算子内部：任务如何分到设备执行单元 | 具体 kernel、编译/运行时和硬件 | 耗时模型应反映并行利用率、分块和尾部工作；没有数据时只能显式作假设 |
| 性能建模：怎样表达不均衡 | 算子/执行代价提供器 | 保留每请求长度，建模整个调用的完成时间，不把平均长度当作唯一特征 |

kernel 可以采用按请求/head 分工、按 KV 块拆分长请求、合并部分结果等方式利用并行资源；这些是可能的机制，不是本次已核对的 Ascend kernel 内部实现。少数长任务也可能造成执行尾部拖延。多个请求共享设备资源，因此 batch 延迟通常不等于独立请求延迟的和，也不等于独立延迟的最大值。

即使 `[1024, 1024, 8192]` 和 `[3072, 3072, 4096]` 的总长度与平均长度相同，长度分布也不同，在不同 kernel 的分工策略下可能产生不同利用率和耗时；不能仅由分布推断哪一组必然更快。

当前耗时打桩的建议：

- 输入保留每请求 `query_len`、`kv_len`，以及 attention 类型、head 信息、dtype、后端、并行/图模式。字段含义必须明确 KV 长度是否包含本轮新位置。
- 规则可以先使用总可见长度、最大长度和 batch size，表达总工作量与可能的尾部效应；完整长度列表继续记录，便于未来增加分桶、tile 数和实测匹配。
- 若用 `固定开销 + α × 总长度 + β × 最大长度` 之类规则，仅将其视为合成实验参数，不能当作 NPU 的物理规律或校准模型。
- 为每个实际批量算子调用返回一个代价，再按真实执行依赖组合成 forward 时间；不要对整轮 forward 和内部算子重复计时。
- 普通 batch 结果处理受批量执行与结果可见事件约束，短请求不能仅凭其较小的独立工作量就提前提交该轮 token。它仍可在真实结束条件满足后退出后续 batch。

如果未来研究按长度分桶、限制单 batch 长度差异等优化，应作为真实调度策略的独立变更评估，同时考虑排队、公平性与吞吐，不能悄悄加进基准仿真路径。当前优先复现原有策略下的不均衡及其影响。

后续源码核对已确认仓库内 Triton decode attention 的 split-KV 两阶段实现；Ascend 调用位置只能确认实际长度与页表的传递，未确认 NPU 算子内部的分核方式。相关区别及其与流水 batch 的关系见 [KV 分块、算子并行与 batch 流水](../architecture/attention-parallelism-and-batch-pipeline.md)。

### 不同请求每次自回归时间是否被“调平”

普通批量 decode 不会给每个请求启动一个独立、可以按各自速度无限前进的完整模型执行。输入 token 一起通过批量算子链，得到整批结果；请求间的工作量差异由实际算子实现承接。

因此，同一 batch 中短请求与长请求的 attention 工作量可以不同，但 token 结果处理通常共享这一批的完成边界。`BatchResultProcessor.process_batch_result_decode()` 若存在 `copy_done` 则先同步该事件，随后归一化批量输出、逐请求追加 token 和判断结束，最后调用 `stream_output(batch.reqs, ...)`。这不是逐请求独立完成就立即进入下一次 forward 的执行模型。CPU 处理、流式输出间隔和网络会使客户端实际可见时间不同，不能保证所有请求严格同时收到 token。

需要区分三种时间：

| 时间 | 含义 |
| --- | --- |
| 单请求独立运行的 decode 耗时 | 在特定上下文、配置和资源条件下单独执行的基准值，不可直接当作混合 batch 内该请求的耗时 |
| batch 执行耗时 | 共享设备资源、批量算子形状与执行依赖共同产生的结果 |
| 某请求相邻输出 token 的间隔 | 还包含它等待再次被调度、相关执行完成、结果处理及选定观测边界内的输出开销 |

SGLang 的处理方式是提高批量执行效率并管理调度机会，而不是保证所有请求自回归延迟相等：

- 算子级并行（如某些后端的 split-KV）改善长请求的执行利用率，但不保证长短请求完全无相互影响。
- 连续批处理会移除已完成请求并接纳新请求；短输出请求不必等其他请求整段生成结束。
- 按配置使用 chunked prefill、混合批次或 prefill/decode 节奏控制，可限制长 prefill 对正在 decode 请求的干扰；并不消除长上下文 decode 的 KV 读取量。
- waiting queue 的 `SchedulePolicy.calc_priority()` 支持多种排队策略，当前代码可见 FCFS、LPM、HRRN、shortest-prefill-first 等；它们影响准入机会或复用/排队表现，不等价于按每请求 decode 毫秒数分配资源。其具体行为与权衡尚未深入。
- overlap 减少主机与设备之间的空隙，不能让一个请求跳过模型结果依赖，也不自动提供时延隔离。

本版本还可见 `_should_defer_prefill()` / `_arm_prefill_decode_interval()` 对 prefill/decode 节奏的控制。这里只确认机制存在，不宣称所有配置默认启用或自动提供延迟保障。

仿真应让真实调度决定每轮 batch，对该 batch 预测耗时，并在真实结果可见时点记录每个请求的 token 时间；最后计算逐请求 token 间隔及分位数。不能预先将各请求时间平均，也不能直接用单请求基准的最大值代表 batch 延迟。

### 排队与准入究竟缓解了什么

此前“排队策略缓解不均衡”应限定含义：它们主要控制请求等待、批次组成和资源压力，不直接消除已经进入同一个 decode batch 的长短 KV 计算差异，也不默认把请求按预测 decode 耗时分桶。

`SchedulePolicy.calc_priority()` 决定等待队列的候选顺序，`PrefillAdder.add_one_req()` 及 `_select_prefill_admission()` 决定候选能否以什么 prefill 形状加入。两个层次不能混为“自动负载均衡”。

| 已核对机制 | 可以改善的情形 | 不保证的效果 |
| --- | --- | --- |
| shortest-prefill-first | 按未缓存的待计算输入规模排序，让小 prefill 有机会先执行；本版本还有为较短请求保留 chunk 预算的逻辑 | 不能保证后续 decode 的上下文短或时间相同；短请求持续到达时需关注公平性 |
| LPM | 优先较长前缀匹配，利用已有 KV，减少重复 prefill | 复用的历史 KV 在普通全量 decode attention 中仍被读取，命中多不代表 decode 便宜 |
| HRRN | 使用 token 进度表达等待老化，结合未缓存输入量考虑排队顺序 | 不是精准的每请求毫秒代价模型，也不是 decode 时延隔离 |
| 请求数、输入 token、内存等准入约束 | 控制本轮或活动集合的规模，降低资源过载和内存压力；被延迟请求仍承担排队等待 | 不保证每轮严格限定在某个毫秒预算内，也不等于按 KV 长度差分组 |
| chunked prefill / 混合批次 | 按配置限制长 prompt 一次提交的新 token 数、为其他工作留下调度机会 | 一个 chunk 仍可能读取较长前缀；不能仅由 chunk token 数推断精确耗时 |

预算例子：等待队列有一个需计算 8K 新 token 的请求和一个 1K 请求。shortest-prefill-first 可把 1K 请求先作为候选；若启用 2K chunk 预算，长请求在相应条件下分块进入。这样控制的是排队顺序和每轮提交量，不是将 8K 上下文的 decode 变成 1K 上下文的计算量。具体接纳组合仍取决于其他预算、对齐和策略。

源码中特别存在例外：未启用 chunking 时，`_select_prefill_admission()` 可允许首个请求超过 input cap。因此不能把所有 token 预算描述为每个配置下都不可突破的硬上限。

应按三类问题分别判断：队头等待/准入压力由调度处理；设备内任务长短差异由算子分工处理；跨批次的主机/设备空隙由 overlap 等机制处理。某种优化改善吞吐，也可能增加个别请求的排队，须用逐请求时延与整体吞吐共同评估。

各 policy 的默认选择、排序例子、适用场景推导和显式降级已单独整理为 [排队策略的选择与降级](scheduling-policies.md)。

### 第一阶段总结校正：调度粒度与 split-KV 的作用范围

用户提出三点总结后，核对并明确以下结论：

1. `fcfs`、`lpm`、`hrrn` 等属于等待队列的**排队策略**：决定先考虑哪个候选。**准入检查**在候选排序后判断请求数、token、KV 和其他约束，决定是否接纳及是否分块；两者共同形成 batch，不能统称为上述 policy。
2. 普通自回归生成以**迭代**为调度机会。一次普通 decode forward 通常为每个参与请求生成一个 token；结果处理追加 token 后调用结束判断。完整 prefill 通常也会产生第一个 token，并进行结果处理。不会将一个 batch 的请求全部运行到 EOS 后才回到调度器。
3. 请求结束会释放或转移资源，让新请求更容易准入，但不是重新调度的唯一触发条件。每轮循环都会接收请求并选择下一批；已有资源余量时，即使没有请求结束，也可接纳新请求。队列为空、`batch_is_full`、延迟策略等可能使该轮跳过新 prefill 构建，不能理解为每轮必定接纳或完整重排所有请求。
4. 新请求一般先执行 prefill，之后才加入 decode 的活动集合；是否与已有 decode 混合执行取决于配置。连续批处理不是固定槽位一空就直接填一个尚未 prefill 的 decode 请求。
5. 长短 KV 导致同一批中 attention 的工作量差异，影响整批执行时间；普通路径并没有为每个请求提供独立的完整 forward 完成事件。
6. split-KV 是 attention 内部的计算任务拆分，不增加请求数或当前 query token 数。它可改善并行度和任务长短差异，但不能保证完全均衡，也不减少全量 attention 所需读取的逻辑 KV 范围。

不含图 padding、TP 切分等额外因素的 dense 模型 decode 例子：

```text
三个请求 A/B/C，本轮各输入一个 token，KV 长度为 1K / 1K / 8K

hidden states [3, H]
    → QKV 投影：三个 token 的 Q/K/V
    → 某个 attention head 内：
          A：1 个 split
          B：1 个 split
          C：8 个 split（示例配置）
      产生局部结果，分别归并为 A/B/C 各一个 head 输出
    → 多 head 输出及输出投影：[3, H]
    → FFN：[3, H] → [3, I] → [3, H]（示意，门控结构省略）
```

这里 H 为 hidden size，I 为 FFN intermediate size。attention 内虽然示意为每个 head 共 10 个子任务，FFN 仍然只处理三个新 token，不会扩成十个 token 再让七个“空位”闲置。设备执行资源不会固定绑定某请求的 split 并保留到所有后续层；后续算子按自身形状安排任务。FFN 在小 batch 下仍可能利用率不足，但那属于 FFN 自己的计算形状与 kernel 问题，不能归因为上个 attention 的 split 留下空位。

本节讨论普通非投机生成。投机解码一次可能提交多个 token，overlap 也会使提交与结果处理跨轮交错；它们仍须保留各自真实结束检查和依赖，后续专题展开。

### `event_loop_normal()` 一次循环到底生成几个 token

对普通非投机 decode，一次循环选择一个执行 batch，调用一次 `run_batch()`，通常为其中每个参与请求生成一个新 token，再调用 `process_batch_result()` 更新状态和检查结束。该次循环不会继续调用 forward 直到某个请求出现 EOS；即使所有请求都未结束，也会进入下一次循环重新进行接收与调度。

示例：本轮 batch 为 `[A, B]`，执行后得到 `[a1, b1]`。若两者均未结束，下一轮可能继续 `[A, B]` 得到 `[a2, b2]`，也可能因新 prefill 或其他调度条件选择不同的工作。若 b2 是 EOS，结果处理将 B 标记结束，之后的 batch 过滤会将其移出；A 可以继续。

这里的“每个请求”只指本轮实际执行 batch 中的普通 decode 请求，不包括等待队列或未被选中执行的活动请求。完整 prefill 通常产生第一个输出 token；chunked prefill 的中间块可能不提交生成 token；投机解码一次可能提交多个 token；空闲轮没有输出。因此不能把“一轮每请求一个 token”扩展为所有配置、所有 forward mode 的统一规则。

## 9. 源码入口与后续问题

源码路径相对 `python/sglang/srt/`：

- `managers/scheduler.py`：上述循环、选择、执行和结果分派。
- `managers/schedule_batch.py`：`Req`、`ScheduleBatch`、`prepare_for_extend()`、`prepare_for_decode()`、`update_finish_state()`。
- `managers/schedule_policy.py`：`PrefillAdder`，后续深入预算和准入条件。
- `managers/scheduler_components/batch_result_processor.py`：prefill/decode 输出提交与资源处理。
- `managers/tp_worker.py`：`forward_batch_generation()`，阶段 2 展开接口。
- `models/qwen2.py`、`layers/radix_attention.py`、`layers/logits_processor.py`：本讲模型计算的源码对应，阶段 3 深入。

第一阶段待继续：用具体 token/KV 预算推演准入限制；内存不足时的 decode 回退；区分正常结束、取消和超时。阶段 2 再深入 ForwardBatch 字段契约。
