关联容器通常使用树来实现

### set

1. set_union,set_itersection,set_difference

~~~
set_union(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<string,char> out(cout," "));//前四个迭代器定义了两个合并的集合区间，最后一个迭代器是输出迭代器，指出将结果集合复制到什么位置。
//假设要将结果放到集合C中，而不是显示它，不应该选择C.begin()，原因是关联集合将健看作常量，所以C.begin()返回的迭代器是常量迭代器，不能用作输出迭代器。第二个原因是与copy类似，set_union()将覆盖容器中已有的数据，容器需要有足够的空间，C是空的，不满足。
//insert_iterator可以解决问题
set_union(A.begin(),A.end(),B.begin(),B.end(),insert_iterator<set<string>> (C,C.begin()));
~~~

> set_itersection和set_difference分别搀着交集和差集，接口与set_union一样。

>lower_bound()和upper_bound()将键作为参数并返回一个迭代器，分别执行集合中第一个不小于键参数的成员与集合中第一个大于键参数的成员。

### multiset

### map

### multimap

> 成员函数equal_range()用键作为参数，返回两个迭代器，表示为与键匹配的区间

~~~c++
multimap<int,string> codes;
pair<const int, string> item(213,"Los Angeles");//通过pair来插入
codes.insert(item);
codes.insert(pair<const int, string>(213,"Los Angeles"));//匿名pair对象插入
pair<multimap<int, string>::iterator,multimap<int,string>::iterator> range = codes.equal_range(213);
//auto range = codes.equal_range(213);//等价于上句代码
for(auto it=range.first;it!=range.second;++it){//遍历与键匹配的区间.
    cout<<(*it).second<<endl;
}
~~~

>lower_bound()和upper_bound()将键作为参数，工作原理与处理set时相同。