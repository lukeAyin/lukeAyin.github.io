### next_permutation()

next_permutation()算法将区间内容转换为下一种排列方式。对于字符串，排列按照字母递增的顺序进行。如果成功，该算法返回true,如果区间已经处于最后的序列中，则算法返回false,要得到区间内容的所有排列组合，应从最初的顺序开始，可以使用sort();

### valarray

对数组进行操作，类似与numpy

```c++
valarray<double> vad1(10),val2(10),vad3(10);
vad3=vad1+vad2;//数组中每个元素来+
vad3=vad1*vad2;//
vad3=2*vad2;//
vad3=log(vad1);//log() overloaded
vad3[slice(1,4,3)]=10;//set selected elements to 10;
```

slice类对象可用于数组索引，它表示的不是一个值而是一组值。

可以方便的将一个长度为12的一维数组按照4*3的二维数组来操作。
