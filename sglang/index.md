---
layout: toc
title: SGLang 博客系列
description: 无 NPU 性能预测的源码学习与架构笔记
---

# SGLang 博客系列

这个系列记录我为实现**无 NPU 性能预测**而学习 SGLang 源码的过程：沿着请求与调度、模型执行、KV Cache、异步 overlap、平台初始化与性能指标的路径，逐段核对真实实现，并把功能行为、模块关系和时间语义整理成文档。

## 学习笔记

- [学习与架构笔记总览](README.md)：文档入口、已确认约束与记录方式
- [学习路线与进度](roadmap.md)：七阶段学习顺序、源码入口与完成标准
- [功能文档](features/README.md)：职责、输入输出、行为与具体例子
- [架构文档](architecture/README.md)：模块关系、调用链、数据流与仿真边界

## 系列文章

{% assign articles = site.pages | where: "dir", "/sglang/" | where_exp: "p", "p.series_article" | sort: "order" %}
{% if articles.size > 0 %}
{% for article in articles %}
- [{{ article.title }}]({{ article.url | relative_url }}){% if article.description %}：{{ article.description }}{% endif %}
{% endfor %}
{% else %}
系列文章正在整理中；当前以学习笔记为主，后续文章会出现在这里。
{% endif %}

## 关于本系列

笔记会随学习进度持续更新。源码定位一般记录到具体提交和符号名，并区分已核对的生产实现、仿真原型与拟议设计；基于源码阅读和手工推演的内容会明确标注“未运行验证”。
