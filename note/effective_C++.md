### 4 Designs and Declarations

#### Item 18: Make interfaces easy to use correctly and hard to use incorrectly

1. 自己定义的类要尽量像built-in类型，比如int,当你不知道如何定义类的时候，do as the int do.比如a*b=c是非法的，你的类也尽量不要允许这种操作。
2. tr1::shared_ptr可以避免cross-dll problem(一个对像在dll中使用new创建，但是在另一个dll中被删除)
3. 好的接口应该容易正确使用，但是不容易错误使用

#### Item 19: Treat class design as type design

1. Remember,the copy constructor defines how pass-by-value is implemented for a type
2. It's important not to confuse initialization with assignment.

#### Item 20: Prefer pass-by-reference-to-const to pass-by-value

1. 传值传递会造成slicing,以基类对象为参数的函数，在被调用时传入了衍生类，在函数中会复制为基类，调用基类的成员方法。
2. **built-it type** 传值参数更快，尽量选择传值参数，STL中的**iterator and function objects** 也是如此。
3. 并不是小对象就一定适合传值，有的小对象的copy constructor have expensive,比如STL中的许多容器，因为其中包含许多指针另一方面是，有一些编译器对built-in type和user-defined type区别对待，即使user-defined非常小，只有一个double,也不会把他放进寄存器，而naked doubles 会进入。
4. 用户定义的types不传值是因为它们**大小可变**，即使现在很小，将来也会变大，甚至不同的实现也会导致区别，比如有的standard library's string type are **seven times** as big as others。

#### Item 21: Don's try to return a reference when you must return an object.

1. 返回reference时，在函数结束之后，假如local objects在stack中申请空间，local objects会被销毁，reference是被销毁的local objects的引用
2. 假如local objects在heap中申请空间，会出现内存泄露。

#### Item 22: Declare data members private

1. 可以让权限更加分离，通过get,set函数可以实现只读，只写，读写权限，避免都是读写权限。
2. From an encapsulation point of view,there are really only two access levels : private (which offers encapsulation) and everything else (which doesn't). 

#### Item 23: Prefer non-member non-friend functions to member functions.

1. non-member and non-friend functions 更应该放在类外而不是类内，这样不会破坏类的封装。
2. non-member and non-friend functions 可以被不同的头文件分开，可以让一个namespace分为不同的头文件，这样就可以根据需求include相应的.h文件。

#### Item 24: Declare non-member functions when type conversions should apply to all parameters.

1. If you need type conversions on all parameters to a function . (including the one that would otherwise be pointed to by the this pointer),the function must be a **non-member**.

#### Item 25: Consider support for a non-throwing swap//需要再重新看几种swap函数对应什么

1. have the member version of **swap** never throw exceptions.
2. Provide a swap member function when std: swap would be inefficient for your type. Make sure your swap doesn't throw exceptions.
3. If you offer a member swap. also offer a non-member swap that calls the member. For classes (not templates),specialize std : swap, too.
4. When calling swap,employ a using declaration for std: swap, then call swap without namespace qualification.
5. It's fine to totally specialize std templates for user-defined types, but never try to add something completely new to std.

### 5 Implementations

#### Item 26: Postpone variable definitions as long as possible.

1. Postpone variable definitions as long as possible. It increases program clarity and improves program efficiency.为了避免程序抛出exception，而导致多调用了constructor和destructor.
2. 在循环中，尽量在循环中define变量，因为在外面定义会导致这个变量暴露给了更大的范围。

//Approach A: define outside loop

Widget w;

for(int i=0;i<n;++i){

​    w=some value dependent on i;

}

//Approach B: define inside loop

for(int i=0;i<n;++i){

​    Widget w(some value dependent on)

}

- Approach A: 1 constructor + 1 destructor + n assignments.
- Approach B: n constructors + n destructors .

#### Item 27: Minimize casting

1. dynamic_casts可以用virtual function来代替
2. 尽量使用c++风格的cast,而不是function和c风格的
3. 必须使用cast的时候，要把cast安全的隔绝在接口之内，便于以后修改。

#### Item 28: Avoid returning "handles" to object internals

1. #### Item 29: Strive for exception-safe code

2. 使用copy and swap 来实现一次全改变或者一点不改变(all-or-nothing changes)

3. Exception-safe function分为三种basic guarantee、strong guarantee 、nothrow guarantee

4. 如果一个函数不能提供任何exception-safe,包括basic，那么任何调用这个函数都不能提供basic guarantee。

5. 使用**object**来管理资源可以防止resource leaks(Item 13)。

#### Item 30: Understand the ins and outs of inlining.

1. inline会导致修改inline函数要重新编译所有调用这个函数的部分，而不inline只需要重新链接。
2. Limit most inlining to small, frequently called functions. This facilitates debugging and binary upgradability, minimizes potential code bloat, and maximizes the chances of greater program spped.
3. Don't declare function templates inline just because they appear in header files.

#### Item 31: Minimize compilation dependencies between files.

1. Avoid using objects when object references and pointers will do.
2. Depend on class declarations instead of class definitions whenever you can
3. Provide separate header files for declarations and definitions.
4. The  general idea behind minimizing compilation dependencies is to depend on declarations instead of definitions. Two approaches based on this idea are Handle classes and Interface classes.

### 6 Inheritance and Object-Oriented Design

#### Item 32: Make sure public inheritance models "is-a".

#### Item 39: Use private inheritance judiciously.

1. Private inheritance means is-implemented-int-term-of. If D privately inherits from B, it means that D objects are implemented in terms of B objects, nothing more.
2. use composition whenever you can, and use private inheritance whenever you must.
3. 使用composition+public比private更加解耦合。
4. "free-standing" objects(class Empty{};)将会占用一些空间，一般是int, sizeof(Empty e)>0;
5. EBO(empty base optimization)可以让空间更少

#### Item 40: Use multiple inheritance judiciously.

1. 因为multiple inheritance导致函数ambiguity时，是调用函数时检查，假如不调用这个函数可以通过编译；而直接在一个class中重复定义时，编译时就会报错。
2. multiple inheritance 会更容易导致ambiguity.
3. Virtual inheritance imposes costs in size, speed, and complexity of initialization and assignment. It's most practical when virtual base classes have no data.
4. Multiple inheritance does have legitimate uses. One scenario involves combining public inheritance from an Interface  class with private inheritance from a class that helps with implementation.
5. 因为virtual inheritance的副作用，所以尽量不使用，因此在遇到"deadly MI diamond"时尽量转换结构.

### Chapters 7: Templates and Generic Programming.

### Item 43: Know how to access names in templatized base classes.

1. 在templatized base classes中，derived class无法直接访问base class的公共方法，因为base class可能会特化成不含这个方法的类，因此编译器refuse to look in templatized base classes for inherited names.

2. 有三种方法可以打破这种限制 
   
   > - 使用"**this->** function_name""来替代直接使用function_name来调用方法
   > - 使用"**using base_name::function_name**(using MsgSender<Company>::sendClear;)"来告诉编译期可以使用该方法
   > - 指明自己调用的是哪个类的函数"**base_name::function_name(MsgSender<Company>::sendClear(infor))**"//缺点是virtual function的动态绑定就失效了，因此最不推荐。

#### Item 44: Factor parameter-independent code out of templates.

1. Templates generate multiple classes and multiple functions,so any template code not dependent on a template parameter causes bloat.
2. Bloat due to non-type template parameters can often be eliminated by replacing template parameters with function parameters or class memebers.
3. Bloat due to type parameters can be reduced by sharing implementations for instantiation types with identical binary representations.//int和long在大部分平台有same binary representation,所以vector<int> 和 vector<long>不会导致code bloat,但是有些平台不是，就会导致code bloat.

> **C++ non-type parameters和type parameters的区别?**

#### Item 45: Use member function templates to accept "all compatible types".

1. Use member function templates to generate functions that accept all compatible types.

2. If you declare member templates for generalized copy construction or generalized assignment. you'll still need to declare the normal copy constructor and assignment operator,too.
   
   ```c++
   #include<iostream>
   #include<vector>
   using namespace std;
   class Top
   {
   
   };
   class Middle:public Top{};
   class Bottom:public Middle{};
   template<typename T>
   class SmartPtr
   {
       public:
       explicit SmartPtr(T *realPtr){
           cout<<"normal pointer constructor!\n";
       };
       template<typename U>
       SmartPtr(U *other){
           cout<<"generized pointer constructor\n";
       };
       SmartPtr(SmartPtr const& other){
           cout<<"normal copy constructor!\n";
       }
       template<typename U>//generized copy constructor;
       SmartPtr(const SmartPtr<U>& other){
           cout<<"generized copy constructor!\n";
       };
   
       SmartPtr& operator=(SmartPtr const& other){
           cout<<"normal copy assignment\n";
           return *this;
       };
   
       template<typename U>
       SmartPtr& operator=(SmartPtr<U> const& other){
           cout<<"generized copy assignment\n";
           return *this;
       };
   };
   int main(){
       SmartPtr<Top> pt1=SmartPtr<Middle>(new Top);//generized pointer constructor!generized copy constructor!
       SmartPtr<Top> pt2=SmartPtr<Middle>(new Top);//generized pointer constructor!generized copy constructor!;
       SmartPtr<Top> pt3=SmartPtr<Top>(new Top);//normal pointer constructor;
       pt3=pt2;//normal copy assignment!
       SmartPtr<Top> pt4(pt3);//normal copy constructor!
       SmartPtr<Top> pt5=SmartPtr<Top>(new Middle);//generized pointer constructor!
       SmartPtr<Middle> pt6(new Middle);//normal pointer constructor!
       SmartPtr<Middle> pt7=pt6;//normal copy constructor!;
       cout<<"success!\n";
   }
   ```

#### Item 46: Define non-member functions inside templates when type conversions are desired.

    1. When writing a class template that offers functions related to the template that support implicit type conversions on all parameters, define those functions as friends inside the class template.

#### Item 47: Use traits classes for information about types.

1. C++中五类iterators: istream_iterators, ostream_iterators, forward iterators, bidirectional iterators**(list,set,multiset,map,multimap)**, random access iterators(**vector,deque,string**).

2. c++STL的containers和functions是分离的，两者之间通过iterators联系，但是funcitons并不知道传进了的iterators是什么containers,因此使用traits(萃取)技术来解决.

3. ```c++
   typedef typename iterT::iterator_category iterator_category;//识别iterators对应的类型
   ```

4. Traits classes make information about types available during compilation. They're implemented using templates and template specializations.

5. In conjunction with overloading. traits classes make it possible to perform **compile-time**(not runtime) if...else tests on types.

#### Item 48: Be aware of template metaprogramming.

1. ```c++
   void advance(std::list<int>::iterator& iter,int d)
   {
       if(typeid(std::iterator_traits<std::list<int>::iterator)::iterator_category)==typeid(std::random_access_iterator_tag)){
           iter+=d; //error!won't compile,因为尽管这段代码不会执行，编译器仍要确保这段代码可以执行。通过TMP(Template metaprogramming)可以解决，Item 47中重载advance函数
       }
       else{
           if(d>=0){whiel(d--)++iter;}
           else{while(d++)--iter;}
       }
   }
   ```

2. Template metaprograming can shift work from runtime to compile-time. thus enabling earlier error detection and higher runtime performance.

3. TMP can be used to generate custom code based on combinations of policy choices. and it can be used to avoid generating code in appropriate for particular types.

### 8 Customizing new and delete

#### Item 49: Understand the behavior of the new-handler.

1. ```c++
   namespace std{
       typedef void(*new handler)();
       new_handle set_new_handler(new_handler p)throw();
   }
   ```

2. 通过传入一个null pointer给set_new_handler,可以卸载new-handler,因为会抛出异常。

3. new-handler函数不能return,通过调用abort和exit来退出

4. 可以给不同的类配备不同的new-handler,在类分配失败时使用各自的new-handler-function

5. set_new_handler allows you too specify a function to be called when memeory allocation requests cannot be satisfied.

6. Nothrow new is of limited utility, because it applies only to memory allocation; associated constructor calls may still throw exceptions.

#### Item 50: Understand when it makes sense to replace new and delete.

1. 可以看开源代码，看别人写的new和delete,比如the Pool library from Boost

#### Item 51: Adhere to convention when writing new and delete.

1. base classes没有virtual destructors可能会导致delete函数不正常工作,因为没有传递正确的类大小给delete
2. operator new should contain an infinite loop trying to allocate memory,should call the new-handler if it can't satisfy a memory request,and should handle requests for zero bytes. Class-specific versions should handle requests for larger blocks than expected.
3. operator **delete** 应该在删除空指针时什么都不做，Class-specific versions should handle blocks that are larger than expected.

#### Item 52: Write placement delete if you write placement new.

1. placement new 对应placement delete,如果使用placement new,那么在有异常的情况下需要撤销new操作时(undone)自动调用对应的placement delete,如果没有declare，就会do nothing.
2. 只有在异常抛出情况下调用placement delete，否则仍要调用normal delete;
3. base classes只定义了placement new,那么derived classes就无法使用normal new，因为member function names hide functions with the same names in outer scopes(Item 33);
4. when you declare placement versions of new and delete, be sure not to unintentionally hide the normal versions of those functions.

### 9 Miscellany

#### Item 53: Pay attention to compiler warnings.

1. 不要忽视编译器的警告信息，可以帮助你更早的找到错误。
2. 不同的编译器返回的warning也不一样，不要依赖warning。

#### Item 54: Familiarize yourself with the standard library, including TR1.

1. 
