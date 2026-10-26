---
layout: toc
title: "排队策略的选择、适用场景与降级"
description: "八类排队策略的排序依据、适用场景与降级"
---

# 排队策略的选择、适用场景与降级

状态：第一阶段专题，已核对排序、配置和主要降级路径；未运行 benchmark。
源码基线：`0957288be0818686034f33a3a7441434e4f5ba33`，核对日期：2026-10-19。

## 1. 策略由谁选择

本版本 `arg_groups/fields/schedule.py` 定义 `schedule_policy`，默认 `fcfs`；用户通过启动参数 `--schedule-policy` 指定。Scheduler 初始化 `SchedulePolicy`，随后在等待队列上调用 `calc_priority()`。这不是根据工作负载自动选择最优 policy 的系统。

这些策略主要决定等待请求的候选顺序。实际能否进入 batch、是否需要 chunk、是否受 KV 容量限制，继续由 `PrefillAdder` 等准入逻辑判断。它们不直接按每请求 decode 毫秒数给设备分配资源。

下文“适用场景”是根据排序机制推导的实验选择依据，不是已验证的性能排名。相关路径均相对 `python/sglang/srt/`。

## 2. 各策略的实际排序依据

| Policy | 已核对的行为 | 可考虑的负载/目标 | 取舍与边界 |
| --- | --- | --- | --- |
| `fcfs` | 普通路径保留队列先后；启用优先级时先按优先级、再按入队时间 | 通用服务基线、解释调度行为、希望按到达顺序提供执行机会 | 不主动偏向短输入或高缓存命中；长 prefill 干扰还需看 chunk/准入配置 |
| `lpm` | 匹配前缀越长越靠前，同时存在批内重复前缀的临时降优先级处理 | 多请求共享长前缀，目标是利用缓存、减少重复 prefill | 按命中长度排序，不是按未缓存工作量或 decode 耗时排序；低命中请求可能等更久 |
| `dfs-weight` | 按请求所匹配的缓存树节点，对请求聚集较多的子树优先进行加权 DFS 排序 | 多个请求群共享不同前缀分支，想研究缓存树局部性 | 依赖缓存树实现支持，非到达顺序/时延公平策略；不等同于单请求 LPM |
| `shortest-prefill-first` | 按 `max(1, prompt_len + output_len - matched_prefix_len)` 从小到大；同工作量再看入队时间，临时降优先级请求另行处理 | 长短输入混合，希望改善小 prefill 的排队与 TTFT | 本版本标为 experimental 且要求前缀缓存；没有通用等待老化项，长任务可能等待较久；不是按生成长度排序 |
| `hrrn` | 按等待期间系统已处理的 prefill token 数 / 本请求未缓存 prompt token 数，比例高者优先 | 长短输入混合，同时希望较长时间等待的请求逐渐获得机会 | token 进度代理，不是真实毫秒估计；队列大时降级，PD decode/DLLM 等未提供进度的调用不具备同样老化语义 |
| `lof` | `max_new_tokens` 较大者优先，可叠加业务优先级 | 离线实验中输出长度上限较可信，想研究优先启动长输出任务的效果 | 使用声明上限，不知道实际 EOS 时间；对短交互请求可能不利，不默认保证吞吐提升 |
| `random` | 随机打乱等待队列 | 随机对照实验、检查排序策略是否造成特定偏差 | 不提供到达顺序公平性；复现实验需固定随机性与输入 |
| `routing-key` | 优先与 running batch 中已有 routing key 匹配的请求；其中按该 key 在 running batch 的出现次数降序；无匹配者随后 | 应用明确提供 routing key，希望同 key 请求聚集的场景 | 不是自动按 prompt 或 MoE 专家匹配；running batch 无有效 key 时不排序，收益须验证 |

## 3. 几个容易混淆的区别

### LPM 与 shortest-prefill-first

假设没有批内重复前缀降优先级，三个请求按 A、B、C 顺序到达：

| 请求 | prompt token 数 | 命中前缀 | 待计算量 |
| --- | --- | --- | --- |
| A | 8000 | 6000 | 2000 |
| B | 1000 | 0 | 1000 |
| C | 12000 | 8000 | 4000 |

- FCFS 的候选顺序为 A、B、C。
- LPM 的候选顺序为 C、A、B，关注缓存命中长度。
- shortest-prefill-first 的候选顺序为 B、A、C，关注未计算的输入量。

上述是排序例子，实际 batch 成员还取决于准入。命中前缀只省去已有 KV 对应位置的重复 prefill，不会从普通全量 decode attention 的可见历史中删除这些位置。

### HRRN 怎样兼顾短任务和等待

本实现排序的核心量为：

```text
waited_tokens = 当前系统 prefill 进度 - 请求入队时的 prefill 进度
score = waited_tokens / uncached_prompt_tokens
```

score 越大越靠前。经典响应比中的常数 1 不影响排序，因此实现使用比值增量。对同样等待进度，短未缓存输入更有利；长输入等待足够久后也可能排到前面。例如 8000 token 的任务等待了 64000 token 的处理进度，其分数为 8；1000 token 的任务等待 2000 token 进度，其分数为 2，前者靠前。

这里的等待不是墙钟秒数，不能理解为严格的最大等待时间保障；同分有稳定的请求 ID 排序，零未缓存量与临时降优先级还存在特殊处理。

### LOF 与短 prefill 优先不针对同一个长度

shortest-prefill-first 关注本次尚需处理的输入；LOF 关注请求声明的输出上限。输入短但要求输出很长的请求，可能同时在两种策略下靠前，不能把两者视为同一指标的升序/降序。

## 4. 当前代码的显式调整与限制

1. `_determine_active_policy()`：配置为 LPM 或 HRRN，且等待队列长度大于 `WAITING_QUEUE_PREFIX_MATCH_MAX = 128` 时，本次候选排序采用 FCFS。不是自动换成另一个性能更优的策略；源码理由是控制前缀匹配/排序开销。不能据此断言所有前缀操作都完全关闭，其他 fast-match 路径仍可能运行。
2. `_validate_and_adjust_policy()`：tree cache 禁用时，LPM、DFS-weight、HRRN 降为 FCFS；shortest-prefill-first 不接受该条件，会报错。
3. 优先级调度是单独开关 `--enable-priority-scheduling`，当前验证只允许搭配 `fcfs` 或 `lof`。默认优先级数值越大越靠前；方向可配置。
4. 当前 CLI choices 中列有 `priority`，但 `SchedulePolicy` 的策略枚举和解析没有对应独立 policy。学习和配置示例使用 `fcfs`/`lof` 加优先级开关，不将 `--schedule-policy priority` 描述为已验证可用。本轮只记录，不修改实现。
5. policy 依赖的缓存能力、目标部署模式和输入元数据也需满足；例如 routing-key 不会凭空生成应用语义，DFS-weight 要求缓存实现提供对应遍历。

## 5. 用于本项目学习与仿真的选择顺序

建议先用 FCFS 建立可解释基线，然后固定其他配置和同一到达 trace，一次改变一个 policy：

- 前缀复用专题：比较 FCFS、LPM；有明显前缀树请求群时再比较 DFS-weight。
- 长短输入与等待专题：比较 FCFS、shortest-prefill-first、HRRN。
- 输出长短专题：在输出上限有意义时比较 LOF。
- 业务优先级专题：使用受支持的基础 policy 加优先级配置。
- routing-key 和 random 仅在对应应用/对照实验中纳入。

观察吞吐、TTFT、逐 token 间隔、端到端时延、长短请求分组的尾延迟、缓存命中与回退次数。要记录配置 policy 和每轮实际 active policy，以免将显式 FCFS 降级误当作目标策略效果。

当前代价来自打桩，比较结果只说明这些合成假设下的调度行为，不作为真实 NPU 的性能排名。

## 6. 源码与关联文档

- `arg_groups/fields/schedule.py`：默认值、CLI 选项、优先级参数。
- `arg_groups/validation_hook.py`：优先级与基础 policy 的组合限制。
- `managers/schedule_policy.py`：枚举、策略选择、排序、缓存依赖与准入。
- `mem_cache/base_prefix_cache.py` 的 `_dfs_weight_order()` 及实际缓存树实现：加权 DFS。
- [请求、batch 与调度主循环](01-requests-and-scheduling.md)：policy 所处的执行链和准入边界。
- [学习路线](../roadmap.md)：当前仍在第一阶段，尚未完成具体资源预算和回退实验。
