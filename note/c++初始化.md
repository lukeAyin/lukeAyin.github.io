### c++使用列表初始化时不允许缩窄转换。

> ```c++
>  long plifs[]={25,92,3.0}; //not allowed,3.0是浮点数，浮点数转整形是缩窄转换
>  char slifs[4] {'h','i',1122011,'\0'}//not allowed.1122011超出char范围
>  char tlifs[4] {'h','i','112','\0'};//allowed
> ```

缩窄转换 

1. 较大的浮点数转为较小的浮点数
2. 浮点数转换为i整型
3. 较大的整型转换为较小的整型

### c++结构体初始化不允许缩窄转换

指针声明

```c++
int * p1,p2;//p1是指针，p2是int变量
```

**对每个指针变量名，都需要使用一个***。

### 动态联编和静态联编

数组声明创建数组时，采用静态联编，即数组的长度在编译时设置 

```c++
int tacos[10];
```

使用new[]运算符创建数组时，将采用动态联编，在运行时为数组分配空间

```c++
int * pz = new int [size];
```

#### C++将赋值表达式的值定义为左侧成员的值

```
x=20; //这个表达式的值为20；
```

#### c++中数组作为参数传递，会变成一个指针

```c++
int cookies[20];
int sum_arr(int arr[],int n){
    //data
    cout<<sizeof(arr)<<endl;
};
sum_arr(cookies,20);//sizeof(arr)是指针长度,sizeof(cookies)=20*4;
```

#### 对于形参为const引用的C++函数，如果实参不匹配，则其行为类似于按值传递，为确保原始数据不被修改，将使用临时变量来存储值。

```c++
void awapr(int &a,int &b){//不是const参数，
    int temp;
    a=b;
    tb=temp;
}
int sum(const int& a,const int& b){//是const参数
    return a+b;
}
long a=3,b=5;
awapr(a,b);//参数不匹配，编译不通过
sum(a,b);//将会生成两个临时int变量，值为3和5，传给sum函数。
```

#### 接受一个参数的构造函数允许使用赋值语法将对象初始化为一个值(implicit constructor)

```c++
Bozo(const int x);//constructor 
Bozo tubby=32;//special form for one-argument constructors
Bozo t='a';//char convert to int,using Bozo(int);
explicit S(double lbs);//可以通过explict关键字来关闭implicit constructor
S s=1.0;//invalid
```

如果构造函数只有一个参数，则将对象初始化为一个与参数的类型相同的值时，该构造函数将被调用。

### 对象数组初始化

```c++
const int STKS = 10;
Stock stocks[STKS] = {
    Stock("NanoSmart",12.5,20),
    Stock(),
    Stock("Monolithic Obelisks",130,3.25),
};//剩余的七个元素会使用默认构造函数进行初始化
```
