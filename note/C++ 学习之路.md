# C++ 学习之路

****

### memset(void *s,int c,unsigned long n);

初始化内存，速度更快，一个字节一个字节初始化

 ~~~c++
 #include<cstring>
 int nums[10]
 memset(nums,0,sizeof(nums));//将nums全部初始化为0；
 ~~~

~~~c++
#include<cstring>
int nums[10]
memset(nums,1,sizeof(nums));//nums初始化有误；
for(auto num:nums){
    printf("%x\n",num);//以十六进制输出
}
//输出结果为0x1010101，可以看出因为int为四个字节，而memset给每个字节都初始化为0x01；
~~~

~~~c++
#include<cstring>
char str[100];
memset(str,'1',sizeof(str));//可以随意给char数组复制，因为char的长度正好为一个字节，不会出现错误
memset(str,'a',sizeof(str));//输出结果均正确
~~~

#### int类型常用memset初始化数字

**0**

**0x3f3f3f3f**(常表示正无穷，因为其十进制为10^9级别足够大，且两个INF相加不会溢出)

**0xffffffff(-1)**

**0xcfcfcfcf**(负无穷)

****

### set 使用红黑树作为底层架构，查找和插入概率为log$_2$n



### 康托展开

![image-20210527122227612](../../.config/Typora/typora-user-images/image-20210527122227612.png)

> 可以求全排列的大小顺序

### C++内存管理

Node node;//在栈上声明空间，如果是局部变量会随着循环条件语句退出而释放空间，空间虽然释放但不会被立即覆盖，会在下次同类型在栈上申请变量空间时被覆盖。

Node *node=new Node();//在堆上申请空间，会随着程序结束而释放空间

~~~c++
struct Node{
    int val;
};

int main(){
    queue<Node*> q;
    if(true){
        Node n1;//申请空间0x7fffffffdb0c
        Node *n2=new Node();
        n1.val=2;
        q.push(&n1);
    }
    Node *tmp=q.front();
    q.pop();
    cout<<tmp->val<<endl;
    if(true){//再次申请Node类型变量，分配地址与n1一样0x7fffffffdb0c
        Node n3;
        n3.val=4;
        q.push(&n3);
    }
    Node *tmp1=q.front();
    q.pop();
    cout<<tmp1->val<<endl;
    cout<<tmp->val<<endl;
    if(true){//申请int类型，没有覆盖n1空间0x7fffffffdb10
        int x;
    }
    cout<<tmp1->val<<endl;
    cout<<tmp->val<<endl;
    if(true){//再次申请同类型空间，覆盖n1空间0x7fffffffdb0c
        Node n3;
        n3.val=5;
        q.push(&n3);
    }
    cout<<tmp1->val<<endl;
    cout<<tmp->val<<endl;
    return 0;
}
~~~

output:

>2
>4
>4
>4
>4
>5
>5

****

#### const extern 全局变量

~~~c++
//file1
extern const int states = 50;
int s=50;
//file2
extern const int states;
extern const s;
~~~

在这种情况下，必须在所有使用该常量的文件中使用extern关键字来声明它。这与常规外部变量不同，定义常规外部变量时，不必使用extern关键字，但在使用该变量的其他文件中必须使用extern.然而，请记住，鉴于单个const在多个文件之间共享，因此只有一个文件可对其进行初始化。

#### 函数与链接性

函数的链接性默认为外部的，即可以在文件中共享。

可以使用关键字static将函数的链接性设置成内部的，使只能在一个文件中使用。**必须同时在原型和函数定义中使用该关键字**

~~~c++
static int private(double x);
static int private(double x)
{
	...
}
~~~

#### inline function

定义位于类声明中的函数都将自动成为内联函数。

### 函数对象functor

函数指针函数名重定义operator()()的类对象都是functor.

重定义了operator()()的类可以使用对象名+()来类似函数调用

~~~c++
class Linear{
	private:
		double slpoer;
		double y0;
	public:
		Linear(double sl_=1,double y_=0):slope(sl_),y0(y_){}
		double operator()(double x){
			return y0+slope*x;
		}
}
Linear f1;
Linear f2(2.5,10.0);
double y1=f1(12.5);//y1=0+1*12.5;
double y2=f2(0.4);//y2=10.0+2.5*0.4
~~~

