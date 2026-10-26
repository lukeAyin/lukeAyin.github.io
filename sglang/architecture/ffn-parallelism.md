---
layout: toc
title: "FFN 并行度与常见优化"
description: "Qwen2 矩阵形状、TP 分片、融合、量化与 batch token 维度"
---

# FFN 并行度与常见优化

状态：源码阅读专题；未运行性能实验。
基线：`0957288be0818686034f33a3a7441434e4f5ba33`，2026-10-19。
源码入口：`srt/models/qwen2.py`、`srt/layers/linear.py`、`srt/layers/dual_gemm.py`。

## 1. 先看 FFN 的矩阵形状

Qwen2 使用 SwiGLU 风格 MLP。令当前 token 数为 M、hidden size 为 H、intermediate size 为 I：

```text
输入 X：[M, H]
gate/up 投影：[M, H] × W_gate_up[H, 2I] → [M, 2I]
SiluAndMul：[M, 2I] → [M, I]
down 投影：[M, I] × W_down[I, H] → [M, H]
```

权重可能以转置布局存储；这里是数学 shape。普通单 token decode 的单请求 M=1，小 batch 时 M 较小。小 M 可能使矩阵 tile 的行方向利用率低，但不意味着只有 M 个设备任务。

矩阵乘实现通常沿 M 和 N 两个输出轴分 tile。概念网格为：

```text
任务数 ≈ ceil(M / tile_M) × ceil(N / tile_N)
```

因此 M 很小时，gate/up 的宽输出维 `2I` 仍可能提供多个 N 向 tile。真实 kernel 的 tile 参数、融合方式和硬件映射需看实际后端；上述式子用于理解任务空间，不用于直接预测耗时。

## 2. SGLang Qwen2 当前的张量并行切分

`Qwen2MLP` 使用 `MergedColumnParallelLinear` 做 gate/up 投影，使用 `RowParallelLinear` 做 down 投影。概念上 TP=P 时：

```text
每个 rank 的 gate/up 权重列分片：W_gate_up[:, 2I/P]
每个 rank 计算：X[M,H] × W_r[H,2I/P] → [M,2I/P]
每 rank 在本地完成对应 gate/up 分片和激活

down 权重按输入维切分：W_down[I/P,H]
每 rank 的局部输入：[M,I/P]
局部 down 输出：[M,H]
通常需要跨 TP ranks reduce 局部输出，得到完整结果
```

`ColumnParallelLinear` 的代码注释说明沿权重输出维分片；`RowParallelLinear` 沿权重输入维切分，输出可能需要归约。特定模型可设置延迟归约或融合通信，以上是 Qwen2 常见契约，不代表所有 MLP 都在每层以同样方式同步归约。

TP 能把大权重与计算分到多个设备，也可能增加小 batch 下的通信和启动开销，并缩小每 rank 的局部矩阵。它是跨设备权重/计算切分，不是自动增加同一设备上的总算术工作量。

## 3. FFN 如何获得更多并行与降低执行时间

| 方法 | 主要改善 | 代价/限制 |
| --- | --- | --- |
| 批内增加 token（更大 decode batch） | 提高 M，更多独立行 tile，也可摊薄权重读取和启动成本 | 更多并发请求会受容量与延迟目标限制；调度由真实 Scheduler 决定 |
| 连续批处理 | 请求加入/结束后改变后续 decode batch 的 M | 不是主动填满到某个目标，也不保证每请求等待相同 |
| TP | 沿 FFN 权重输出/输入维切分到多个设备 | 有通信、同步和每 rank 小矩阵成本；收益依模型、batch、链路而变 |
| 输出维/矩阵 tile 调度 | 将大 N 维划成多个 CTA/program，提高矩阵乘并行 | 依赖 kernel 的 tile、寄存器和共享存储配置；小 M 时每 tile 仍可能较小 |
| 融合 gate/up、激活和量化计算 | 减少 kernel launch、中间张量读写或重复转换 | 是否支持取决于 dtype、量化方式、GPU 架构、token 数、TP/spatial parallel 配置 |
| 量化权重/激活 | 减少带宽占用，可能使用更高吞吐的矩阵指令 | 可能改变精度、量化开销和 kernel 可用性；不是并行任务数量本身的增加 |
| 专家并行（MoE 模型） | 将不同 token 路由到多个专家/设备 | 路由负载不均、token dispatch/通信成本；不是 dense FFN 的直接替代优化 |

若瓶颈在读取权重，量化、融合或摊薄 weight loads 往往比“再切更多 KV”相关；若瓶颈是 M 方向任务不足，提高 batch token 数可能有效；若矩阵 N 已提供很多 tile，单纯沿 reduction K 再切也可能多出 partial-sum 归并成本。必须用目标 kernel 和真实 profiling 判断瓶颈。

Speculative decoding 等方法可能让一次 target forward 验证多个候选 token，提高 token 维度工作量，但引入 draft、verify、接受/拒绝逻辑，可能改变输出路径。它不属于可以无成本套上的 FFN 并行开关。

## 4. Qwen2 的融合示例：DualGemm

`Qwen2MLP.forward()` 在条件满足时调用 `DualGemm`，否则走 `gate_up_proj → SiluAndMul → down_proj` 常规路径。

当前 `DualGemm`（`python/sglang/srt/layers/dual_gemm.py`）实现检查 CUDA、dtype/量化方式、本地 intermediate 宽度和 decode token 数等条件；是否支持不只由 batch size 决定。可用路径将 gate/up 投影与 SwiGLU 相关计算融合，FP8 分支还可融合 quantization 处理，减少中间结果往返。

这是减少 launch/中间带宽成本的例子，不会复用 Attention 的 KV split，也不会让 FFN 输出多出 KV split 数量的行。DualGemm 仍需按自身 GEMM 形状和硬件 tile 组织并行。

## 5. 对性能仿真的含义

- attention 与 FFN 分开建模，输入特征分别使用 per-request KV 长度和矩阵 M/N/K、dtype、量化、TP、后端等。
- 每个算子返回自身批量执行耗时；按真实 forward 的依赖关系组合。Attention 的 split 配置只属于 attention 代价，不能作为 FFN 的 task 数。
- 一个 `[M,H]` 输入对应 FFN 当前 token 数 M；融合可以改变操作边界和内存/launch 开销，不改变其语义 shape。
- 打桩阶段可用按 M、N、dtype/量化、TP 桶化的规则表达形状敏感性，但标注为合成参数。没有 profiler 或 NPU benchmark 时，不能声称已找出瓶颈或确定真实算子利用率。
- 目标后端启用融合、图执行、TP 或 MoE 时，仿真需要对应的整体代价/依赖数据；不能用当前 Qwen2 单卡解释覆盖所有模型。

关联：[Qwen2 请求与 decode 例子](../features/01-requests-and-scheduling.md)、[KV split planner](kv-split-planner-walkthrough.md)。
