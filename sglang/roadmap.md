---
layout: toc
title: "无 NPU 性能预测：学习路线与进度"
description: "七阶段学习顺序、源码入口与完成标准"
---

# 无 NPU 性能预测：学习路线与进度

顺序确认日期：2026-10-19。
初始源码基线：`sim-on-upstream` / `0957288be0818686034f33a3a7441434e4f5ba33`。

按下列七个阶段学习。源码入口均相对 `python/sglang/srt/`。阶段内遇到依赖概念可作局部补充，整体顺序以本文为准；后续调整在本文记录理由。

## 路线总览

| 阶段 | 主题 | 状态 | 功能与架构文档 |
| --- | --- | --- | --- |
| 1 | 请求、batch 与调度主循环 | 学习中：普通生成主路径 | [功能](features/01-requests-and-scheduling.md)、[架构](architecture/01-scheduler-loop.md) |
| 2 | 调度器到模型执行的接口 | 待学习 | 待创建 |
| 3 | 模型 forward 与算子路径 | 待学习 | 待创建 |
| 4 | KV Cache 与内存容量 | 待学习 | 待创建 |
| 5 | 异步执行、overlap 与完成事件 | 待学习 | 待创建 |
| 6 | 配置、平台选择与启动流程 | 待学习 | 待创建 |
| 7 | 性能指标统计 | 待学习 | 待创建 |

状态使用“待学习 / 学习中 / 已学习，待补充 / 已完成”。完成意味着已讨论核心问题、核对源码、固化文档，并记录验证方式或未验证边界；不要求每节都运行实验，也不把未运行描述为已验证。

## 1. 请求、batch 与调度主循环

**要回答：** prefill 和 decode 有何不同？请求数与本轮计算 token 数有何不同？请求为什么进入、等待或离开某个 batch？哪些状态影响下一轮调度？

**源码入口：** `managers/schedule_batch.py` 的 `Req`、`ScheduleBatch`、`prepare_for_extend()`、`prepare_for_decode()`；`managers/scheduler.py` 的 `event_loop_normal()`、`get_next_batch_to_run()`、`run_batch()`、`process_batch_result()`；`managers/schedule_policy.py` 的 `PrefillAdder`。

**学习方式：** 从 `event_loop_normal()` 的短循环入手，用一个请求解释 prefill/decode，再加入第二个请求观察连续批处理。此阶段把模型执行当作接口，只识别输入输出，不展开算子。

**完成标准：** 能画出接收请求、选择 batch、执行、处理结果的循环，并解释一个具体例子的请求状态变化；知道这些逻辑必须真实执行。

**文档产物：** 功能文档 `features/01-requests-and-scheduling.md`；架构文档 `architecture/01-scheduler-loop.md`。记录对象职责、状态变化、逐轮例子和控制流图。

## 2. 调度器到模型执行的接口

**要回答：** 调度 batch 如何转换为模型输入？执行需要哪些长度、shape、模式和 KV 位置？执行结果包含什么，如何交回真实状态处理？

**源码入口：** `managers/tp_worker.py` 的 `forward_batch_generation()`；`model_executor/forward_batch_info.py` 的 `ForwardBatch.init_new()`；`model_executor/model_runner.py` 的 `forward()`、`_forward_raw()` 和 `ModelRunnerOutput`；Scheduler 的调用与结果处理位置。

**完成标准：** 能串起 Scheduler → Worker → ForwardBatch → ModelRunner → 结果处理；列出性能查询需要的输入与执行适配必须提供的结果字段。

**文档产物：** `features/02-execution-interface.md`；`architecture/02-execution-chain.md`。记录接口契约、数据转换和候选接入点；区分实际调用关系与方案建议。

## 3. 模型 forward 与算子路径

**要回答：** 一个 decoder layer 执行什么操作？prefill/decode 的输入形状怎样变化？在哪里提取算子描述、查询打桩耗时？NPU 融合算子与 Python/PyTorch 调用是什么关系？

**源码入口：** 先以 `models/qwen2.py` 学习结构，再进入选定目标模型；沿 `layers/radix_attention.py` 到实际 attention 后端，并跟踪 linear、norm、RoPE 和 MLP。

**完成标准：** 能画出一个 decoder layer 的操作与形状流，说明被替代计算应提供的元数据或副作用；明确算子耗时打桩与算子结果替代的区别。无需先掌握内核优化。

**文档产物：** `features/03-model-and-operators.md`；`architecture/03-operator-path.md`。记录算子边界、描述字段、代价查询接口与未覆盖的数据相关行为。

## 4. KV Cache 与内存容量

**要回答：** 目标设备预算怎样转成 KV 容量？逻辑索引和物理存储有何区别？前缀复用、淘汰和容量压力怎样影响计算量、准入和回退？

**源码入口：** `mem_cache/kv_cache_configurator.py`、`allocation.py`、`allocator/`、`memory_pool.py`，以及实际配置选中的 radix cache。

**完成标准：** 能推演分配、复用、释放的资源账本，区分请求释放与缓存保留；定位可替换的设备探测/存储边界，保留真实容量推导和管理逻辑。

**文档产物：** `features/04-kv-cache.md`；`architecture/04-memory-and-cache.md`。记录容量来源、索引关系、生命周期及其对调度/性能的影响。

## 5. 异步执行、overlap 与完成事件

**要回答：** 任务提交、设备完成、CPU 可读结果有什么区别？结果队列、延迟采样和同步等待如何衔接？虚拟完成事件怎样满足真实调度的等待语义？

**源码入口：** `scheduler.py` 的 `event_loop_overlap()`、`result_queue`、`launch_batch_sample_if_needed()`；沿真实执行路径查找 stream/event、结果复制、同步等待和相关屏障。

**完成标准：** 能画出相邻批次的执行时序与依赖；区分可重叠工作与必须等待的工作，明确虚拟设备接口必须实现的行为。不能用 normal 循环替代目标 overlap 路径。

**文档产物：** `features/05-overlap-and-completion.md`；`architecture/05-time-and-events.md`。记录事件、依赖、资源、结果可见时机与计时责任。

## 6. 配置、平台选择与启动流程

**要回答：** 模型、后端、并行度和图模式如何决定执行路径？哪些初始化查询真实设备？如何让 CPU 宿主保留目标 NPU 的逻辑分支？

**源码入口：** `server_args.py`、`runtime_context.py`、`platforms/npu.py`、`hardware_backend/npu/`、`model_executor/model_runner_components/`。

**完成标准：** 能画出关键初始化与配置传播关系，列出设备依赖和适配边界；分清宿主执行环境与目标硬件配置。

**文档产物：** `features/06-configuration-and-startup.md`；`architecture/06-platform-and-initialization.md`。记录配置来源、生效位置、生命周期与平台能力选择。

若前序实验需要启动服务，可提前查看最小启动链，系统学习仍放在本阶段。

## 7. 性能指标统计

**要回答：** TTFT、逐 token 间隔、端到端时延和吞吐从哪里计时？如何聚合？哪些开销被覆盖？如何追溯打桩规则，未来怎样校准？

**源码入口：** Scheduler 结果处理和时间记录、`observability/`；需要完整服务指标时再跟踪 TokenizerManager、DetokenizerManager、HTTP 入口与 benchmark。具体统计符号在本阶段按实际路径核对。

**完成标准：** 能给出指标定义与时间点，用小例子手算核对；区分虚拟时间、宿主墙钟和目标 CPU 开销；打桩阶段不宣称预测准确率。

**文档产物：** `features/07-performance-metrics.md`；`architecture/07-observability-and-validation.md`。记录指标口径、时间来源、数据流和分阶段验证方式。

## 按目标配置追加的专题

TP/DP/EP/PP、PD 分离、MoE、图执行与融合、完整 HTTP 服务链路，按目标配置加入相应阶段或独立专题。目标部署用到的能力必须覆盖后才声称支持该部署。多模态、投机解码、LoRA、HiCache、网关/Rust 服务和 Diffusion 暂按需学习。

## 进度记录

| 日期 | 学习内容 | 已固化内容 | 下次起点 |
| --- | --- | --- | --- |
| 2026-10-19 | 确认七阶段顺序，尚未开展阶段 1 的共同学习 | 路线、功能与架构文档规范、性能仿真约束 | 阶段 1：prefill/decode、Req/ScheduleBatch 与 `event_loop_normal()` |
| 2026-10-19 | 阶段 1 第一讲：结合 Qwen2 解释 prefill/decode、KV 位置、主循环和双请求连续批处理；源码核对，未运行 | [请求与调度](features/01-requests-and-scheduling.md)、[调度架构](architecture/01-scheduler-loop.md) | 继续阶段 1：准入预算、资源不足时的回退，以及取消/超时 |
| 2026-10-19 | 补充理解：decode 仅投影新 Q/K/V，但 QK 打分与 V 加权需访问所有可见 KV；用矩阵形状解释长度与工作量 | [功能文档第 5 节](features/01-requests-and-scheduling.md) | 继续阶段 1；区分新 token 计算量与历史 KV 访问量 |
| 2026-10-19 | 补充理解：变长 batch 的总工作量、kernel 内负载分配和尾部效应；保留逐请求长度、预测批量调用代价，调度不重写 | [功能文档第 8 节](features/01-requests-and-scheduling.md)、[架构边界](architecture/01-scheduler-loop.md) | 继续阶段 1 的准入预算；后续阶段深入实际算子与时间接口 |
| 2026-10-19 | 补充理解：Triton split-KV 的局部计算/归并、Ascend 证据边界，以及分页、chunked prefill、overlap、PP 的区别 | [分块与流水架构](architecture/attention-parallelism-and-batch-pipeline.md) | 主线仍在阶段 1；不将本次概念补充视为完成阶段 3/5 |
| 2026-10-19 | 补充理解：单请求独立耗时、batch 完成边界与逐请求 token 间隔的区别；真实调度不保证请求时延相等 | [功能文档第 8 节](features/01-requests-and-scheduling.md) | 继续阶段 1：准入与调度节奏；相关策略仅确认入口，未深入 |
| 2026-10-19 | 补充核对：排队顺序与 prefill 准入的作用边界、缓存命中不等于短 decode；Triton 按长度差与设备并行度规划 split 的启发式及适用条件 | [排队与准入说明](features/01-requests-and-scheduling.md)、[split-KV 机制](architecture/attention-parallelism-and-batch-pipeline.md) | 阶段 1 继续核对具体预算和回退；尚无运行验证 |
| 2026-10-19 | 专题：policy 手动配置、FCFS 默认值、排序依据与适用场景、缓存/大队列降级和优先级限制 | [排队策略](features/scheduling-policies.md) | 阶段 1 继续具体准入预算与回退；策略收益尚待实验 |
| 2026-10-19 | 用户总结校正：排队与准入分开；普通 decode 每步检查结束，每轮有调度机会；split-KV 不扩增 FFN token 数，也不保留固定资源槽位 | [总结校正](features/01-requests-and-scheduling.md)、[split 与 FFN 边界](architecture/attention-parallelism-and-batch-pipeline.md) | 第一阶段仍在学习中，继续准入预算/回退或针对未理解点讨论 |
| 2026-10-19 | 补充：Triton 固定份数、确定性固定段长、动态启发式三种拆分路径；本轮 metadata 重新规划与最大 grid 的区别 | [split 规划模式](architecture/attention-parallelism-and-batch-pipeline.md) | 不泛化为 Ascend；仍需后续明确目标执行后端 |
| 2026-10-19 | 逐步解读 get_num_kv_splits：变量、动态两个提议、对齐后的实际范围；FFN 沿矩阵维度组织任务，无需匹配 attention split 数 | [规划器详解](architecture/kv-split-planner-walkthrough.md) | 已做 Python 算术核对，未执行原 kernel；主线仍在阶段 1 |
| 2026-10-19 | 补充 FFN 并行专题：Qwen2 GEMM 形状、TP 权重切分、DualGemm 融合、量化、提高 M 维 batch token | [FFN 并行架构](architecture/ffn-parallelism.md) | 源码阅读；实际瓶颈与优化收益需目标设备 profiling |

开始每阶段时标记“学习中”。每次学习后添加简短记录，链接实际形成的文档，记录未解决问题与下一次具体起点。
