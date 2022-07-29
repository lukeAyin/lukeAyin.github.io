### copy

copy()的前两个迭代器参数表示要复制的范围，最后一个迭代器参数表示要将第一个元素复制到什么位置。前两个参数必须是（或最好是）输入迭代器，最后一个参数必须是（或最好是输出迭代器。Copy()函数将覆盖目标容器中已有的数据，同时容器必须足够大，以便能够容纳被复制的元素。

ostream iterator是输出迭代器的一个模型。可以通过#include<iterator>来使用

```c++
#include <iterator>
int casts[10]={1,2,4,6,3,7,43,8,3,9};
vector<int> dice(10);
copy(casts,casts+10,dice.begin());//copy array to vector;
ostream_iterator<int,char> out_iter(cout," ");
//*out_iter++ =15;//works like cout<<15<<" ";
copy(dice.begin(),dice.end(),out_iter);//copy vector to output stream;
copy(istream_iterator<int,char>(cin),istream_iterator<int,char>(),dice.begin());
```

istream_iterator也使用两个模板参数，第一个参数指出要读取的数据类型。第二个参数指出输入流使用的字符类型。istream_iterator<int,char>(cin)表示使用由cin管理的输入流，istream_iterator<int,char>省略了构造函数参数表示输入失败，因此copy(istream_iterator<int,char>(cin),istream_iterator<int,char>(),dice.begin());表示从输入流读取，直至文件结尾、类型不匹配或出现其他输入错误为止。

### ostream_iterator,istream_iterator

### reverse_iterator

reverser_iterator执行递增会导致其向后移动,与iterator相反。

vector中rbegin(),rend()返回reverse_iterator指针。

因此

```
ostream_iterator<int,char> out_iter(cout," ");
copy(dice.begin(),dice.end(),out_iter);//display in forward order;
copy(dice.rbegin(),dice.rend(),out_iter);//display in reverse order.
```

### front_insert_iterator , back_insert_iterator , insert_iterator

```c++
copy(casts,casts+10,dice.begin());
//该函数dice必须有足够的空间来容纳复制的元素，copy不能呢该自动根据发送值调整目标容器的长度
```

这三种插入迭代器通过将复制转换为插入解决了问题，插入将添加新的元素，不会覆盖已有的元素。

back_insert_iterator将元素插入到容器尾部，front_insert_iterator将元素插入到容器前端，insert_iterator将元素插入到insert_iterator构造函数参数指定的位置前面。

back_insert_iterator只能用于允许在尾部快速插入的容器，如vector

front_insert_iterator只能用于允许在起始位置做时间固定插入的容器类型。如queue

insert_iterator没有这些限制，因此可以用作插入vector前端，但是front_insert_iterator在支持它的容器中会更快。

```
vector<int> dice;
back_insert_iterator<vector<int>> back_iter(dice);
queue<int> q;
front_insert_iterator<queue<int>> front_iter(q);
insert_iterator<vector<int>> insert_iter(dice,dice.begin());
```
