---
layout: default
title: "get_num_kv_splits 逐步解读与 FFN 并行边界"
description: "get_num_kv_splits 的三个分支、动态启发式与实际 split 范围"
---

# get_num_kv_splits 逐步解读与 FFN 并行边界

状态：源码学习专题；未运行 GPU/NPU kernel。
基线：`0957288be0818686034f33a3a7441434e4f5ba33`，2026-10-19。
范围：当前 Triton 后端的拆分规划与普通 decode 两阶段实现。GQA/MLA、Lean 等路径可能有不同 launch 方式，不泛化为 Ascend。

源码入口（相对 `python/sglang/`）：

- `srt/layers/attention/triton_backend.py`：初始化、`get_num_kv_splits()`、decode metadata 更新。
- `kernels/ops/attention/metadata.py`：`get_num_kv_splits_triton()`。
- `kernels/ops/attention/decode_attention.py`：stage 1 的实际 KV 范围与 stage 2 归并。
- `srt/models/qwen2.py`：attention 输出投影与 MLP 的张量边界。

## 1. 函数职责：填写规划结果，不搬运 KV

```python
get_num_kv_splits(self, num_kv_splits, seq_lens)
```

`seq_lens` 是输入长度数组；`num_kv_splits` 是预分配的输出数组，由函数原地填写。函数不返回 KV 块，不在此复制 K/V，也不实际执行 attention。

| 变量 | 含义 |
| --- | --- |
| `seq_lens` | 每个原序列传入规划器的 KV 长度；可能已被 DCP 本地化或滑动窗口处理，不能总等同于完整 prompt 长度 |
| `num_kv_splits` | 每个执行条目的规划拆分数；普通 decode 通常每请求一项 |
| `num_seq` | `seq_lens.shape[0]`，原序列条目数 |
| `num_token` | 输出数组 `num_kv_splits.shape[0]`，本函数使用的执行条目数；不是 KV 长度总和，也不是 prefill token 总数 |
| `num_group` | `num_token // num_seq`，一个原序列对应多少执行条目；普通 decode 为 1，某些投机展开路径可能大于 1 |
| `self.num_head` | 此后端执行布局中的 query head 数，已受 TP/DCP 等配置调整 |
| `self.num_kv_head` | 对应布局中的 KV head 数 |
| `self.device_core_count` | 设备并行资源计数，供规划使用；不是当前空闲核心的实时测量 |
| `self.max_kv_splits` | 本路径拆分容量/上限，初始化时可能被 MLA、最大上下文或 tile 配置调整；不是动态路径每请求必用的份数 |
| `self.static_kv_splits` | 是否请求固定份数路径；初始化读取的开关默认关闭 |
| `self.enable_deterministic` | 是否启用确定性推理相关行为 |
| `self.split_tile_size` | 用于某些路径的目标 KV 段长；与 `num_group`、head 分组、page size 均不同 |

开头的整除断言要求 `num_group * num_seq == num_token`。它把原序列与展开执行条目的映射固定为每序列相同条目数。例如 `num_group=2` 时，输出拆分数按 `[sA, sA, sB, sB, ...]` 复制。不要将这里的 `num_group` 与 GQA 的 head 分组混淆。

## 2. Python 包装函数的三个分支

### 固定份数

```python
if (static_kv_splits or device_core_count <= 0) and not enable_deterministic:
    num_kv_splits.fill_(max_kv_splits)
    return
```

所有条目使用同一规划份数。短序列可能因对齐而出现没有有效计算范围的 split；实际范围由后面的 kernel 决定。

### 确定性相关的目标段长

```python
if split_tile_size is not None and enable_deterministic:
    expanded_seq_lens = seq_lens.repeat_interleave(num_group)  # 当 group > 1
    num_kv_splits[:] = ceil_div(expanded_seq_lens, split_tile_size)
    return
```

这将拆分数主要绑定到该序列的长度，而不是同批其他请求的长短或 batch 大小。初始化注释说明其用于 batch invariance；不能仅凭这个函数就证明完整推理所有算子均具有确定性。

需要收紧此前“固定段长”的表述：这里固定的是计算份数时使用的**目标段长**，普通 stage 1 仍会按长度、份数和最小计算块重新确定实际边界，见第 6 节。不能保证每个实际 split 都严格等于 `split_tile_size`。

### 动态规划

其他对应路径设置：

```python
SCHEDULE_SEQ = 256 if num_seq < 256 else next_power_of_2(num_seq)
get_num_kv_splits_triton[(1,)](..., MAX_NUM_SEQ=SCHEDULE_SEQ)
```

`SCHEDULE_SEQ` 是规划 kernel 处理长度数组时的向量容量，不是 batch size、split 数或设备核心数。padding 后的位置会被 mask。`[(1,)]` 表示启动一个用于规划的 Triton program；不表示 attention 只有一个并行任务。

## 3. 动态规划：先处理长度差异

以下记 `ceil_div(a,b)` 为向上取整的整数除法，输入有效长度为正。

`offs_seq` 是向量索引，`mask_seq` 区分有效请求。求最大值时无效位置填 0，求最小值时无效位置填最大长度，避免 padding 的 0 把最小值错误变成 0。

```python
max_seq_len = max(seq_lens)
min_seq_len = min(seq_lens)
if max_seq_len * 8 < min_seq_len * 10:
    min_seq_len = max_seq_len
```

最大长度小于最小长度的 1.25 倍时，这一分支把它们视为足够接近，忽略长度差异的拆分动机。其他利用率分支仍然可以拆分。

```python
max_kv_splits_1 = min(ceil_div(max_seq_len, min_seq_len), max_kv_splits)
kv_chunk_size_1 = ceil_div(max_seq_len, max_kv_splits_1)
```

`max_kv_splits_1` 是“长度差异”给最长序列提出的拆分数；`kv_chunk_size_1` 是据此得到的目标粒度。各请求再按自己的长度映射到份数。它不是保证每个任务严格等长的精确最优化算法。

## 4. 动态规划：再估计需要多少并行任务

```python
ext_seq_len = max_seq_len / 64.0
ext_device_core_count = int(device_core_count * max(log2(ext_seq_len), 1.0))
```

这里的 `ext_device_core_count` 是经过长度放大的**启发式并行任务预算**，不是硬件真的增加了核心。源码注明希望拆分数随序列长度逐渐增长。这不是实测延迟模型。

```python
num_kv_group = num_head // num_kv_head
if num_kv_group == 1:
    token_grid = num_seq * num_group * num_head
else:
    block_h = min(16, num_kv_group)
    token_grid = num_seq * num_group * ceil_div(num_head, block_h)
```

- `num_kv_group` 是每个 KV head 对应多少 query heads，即 GQA/MQA 的 head 共享比例。
- `block_h` 在此表示分组路径一起处理的 query head 数，最大取 16；不是 KV 段长。
- `token_grid` 估计未沿 KV 拆分时，序列、执行条目与 head 分组已经提供多少任务。

```python
max_kv_splits_2 = min(ceil_div(ext_device_core_count, token_grid), max_kv_splits)
kv_chunk_size_2 = ceil_div(max_seq_len, max_kv_splits_2)
```

现有任务多时，为满足该启发式预算所需的额外拆分通常较少；现有任务少时，可能沿 KV 增加拆分。这个趋势受另一分支、上限和离散取整共同影响，不是严格的 batch size 与 split 数反比例规律。

## 5. 合并两个提议与数值例子

```python
num_kv_splits[i] = max(
    ceil_div(seq_lens[i], kv_chunk_size_1),
    ceil_div(seq_lens[i], kv_chunk_size_2),
)
```

最后通过 `offs_token = offs_seq * num_group` 将每个序列的份数写入对应输出位置；`num_group > 1` 时重复写入各展开条目。

使用以下明确假设做算术演示，不代表某个实际 NPU：

```text
seq_lens         = [1024, 1024, 8192]
num_seq          = 3
num_group        = 1
num_head         = 32
num_kv_head      = 8
device_core_count= 80
max_kv_splits    = 16
```

| 步骤 | 计算结果 |
| --- | --- |
| 长度差异提议 | `splits_1=8`，`chunk_1=1024`，各请求提议 `[1,1,8]` |
| 长度放大预算 | `log2(8192/64)=7`，启发式预算 `80*7=560` |
| 现有并行任务 | GQA 比例 `32/8=4`，`block_h=4`，`token_grid=3*1*ceil(32/4)=24` |
| 利用率提议 | `splits_2=min(ceil(560/24),16)=16`，`chunk_2=512`，各请求提议 `[2,2,16]` |
| 最终逐请求份数 | 取逐项最大值，得到 `[2,2,16]` |

以上数字已用独立 Python 整数运算核对，没有执行原 Triton kernel 或测量性能。此前 `[1,1,8]` 只描述长度差异这一项，在本组完整假设下不是最终结果。

## 6. 规划份数怎样变成实际计算范围

普通 stage 1 使用：

```python
kv_len_per_split = ceil_div(ceil_div(L, S), MIN_BLOCK_KV) * MIN_BLOCK_KV
start = kv_len_per_split * split_id
end = min(start + kv_len_per_split, L)
```

其中 L 是该执行条目的实际 KV 长度，S 是规划份数；本代码的 `_MIN_BLOCK_KV` 为 32。`end > start` 的任务才计算。每个 split 内还按 `BLOCK_N` 读取 tile，后者是另一层访存/计算粒度。

举例：L=1025，目标 `split_tile_size=256`，包装函数给出 S=5。普通 stage 1 得到实际每段范围大小 `ceil_div(ceil_div(1025,5),32)*32=224`，边界为 `[0,224)`、`[224,448)`、`[448,672)`、`[672,896)`、`[896,1025)`。所以目标段长、实际 split 范围、KV page size 和内部 tile 都不是同一个变量。

普通非分组路径的 stage 1 launch grid 是 `(batch, head_num, MAX_KV_SPLITS)`，可能包含无有效 KV 范围的任务；不是只按各请求有效 split 数紧凑启动。stage 2 grid 为 `(batch, head_num)`，汇总局部输出与归一化信息。GQA 分组和其他实现的 grid 应分别核对，不能用普通路径公式替代它们。

## 7. attention 和 FFN 为什么不要求相同并行度

并行任务是各算子内部的实现单位，跨算子契约是输出张量及完成依赖。不存在“整个 forward 固定给一个请求分配若干核心，并一直持有”的要求。

以三个 decode token、hidden size H、FFN 中间维度 I 为例，忽略 TP 与图 padding：

```text
QKV 投影：输入 [3,H]
  ↓
Attention：沿 请求/head/KV split 组织局部任务
  ↓ 合并 split，恢复每个 query/head 的完整输出
Attention 输出投影：[3,H]
  ↓
FFN gate/up 投影：[3,H] × [H,2I] → [3,2I]
门控激活：[3,2I] → [3,I]
FFN down 投影：[3,I] × [I,H] → [3,H]
```

这是 Qwen2 普通数学形状示意，权重在 PyTorch 中可能以转置布局存储，实际实现也可能融合 gate/up 与激活等步骤。

FFN 不只有三个硬件任务：矩阵乘法还能沿输出通道分 tile。概念上 `[M,K] × [K,N]` 的输出 tile 网格可按 `ceil(M/BM) × ceil(N/BN)` 组织，具体 kernel 还可能采用分组、persistent 或 split-K 等策略。因此 M=3 不等于只使用三个核心，attention 的 split 数也无需与 FFN tile 数相等。

普通独立算子链通过 stream 顺序/事件等依赖保证后续读取的数据已就绪；不同 kernel 启动时各自调度任务。图模式或融合实现可能改变提交细节，但仍需满足张量依赖。split 归并不是为了让两种算子的任务数一样，而是为了恢复正确的 attention 输出。

attention 与 FFN 的设备利用率仍可能不同，split-KV 只改善 attention。若 FFN 成为瓶颈，应分析其 batch/token 数、矩阵形状、权重带宽、dtype 与 kernel，而不是为它保留无意义的 KV split 槽位。整体 forward 性能应按各算子实际依赖和代价组成，不按某个统一“并行度”比例推算。

关联：[分块与流水概念](attention-parallelism-and-batch-pipeline.md)、[请求与调度](../features/01-requests-and-scheduling.md)。
