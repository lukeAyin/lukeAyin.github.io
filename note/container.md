### vector

vector的resize函数只会在新插入的数中赋值新的值，原来数组中存在的不会更改

```cpp
      void
      resize(size_type __new_size, const value_type& __x)
      {
	if (__new_size > size())
	  _M_fill_insert(end(), __new_size - size(), __x);
	else if (__new_size < size())
	  _M_erase_at_end(this->_M_impl._M_start + __new_size);
      }
```

### lower_bound

lower_bound对set、map这样以红黑树为底层结构的数据结构，并不会利用红黑树本身的排序特性，set、map的iterator是**forward_iterator**，不是random_iterator，时间复杂度为o(n)?.

推荐使用set.lower_bound,使用set本身的成员函数，对二分查找进行了优化。
