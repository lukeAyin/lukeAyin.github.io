重复delete(释放已经释放的内存)会导致不确定的结果。

不要用delete释放不是new分配的内存

对空指针使用delete是安全的

