# 面试
---
## 一.爱奇艺
### 爱奇艺面试第一轮
#### 1.你了解哪些设计模式
答:单例模式工厂模式  
追问:单例模式、简单工厂模式、工厂模式有什么特点？  
答:单例模式的本质:控制类的实例数量,当然这里是一个.  
简单工厂的本质: 选择合适的实现对象  
工厂模式的本质: 延迟到子类来选择实现  

==后期补充==  
* [单例模式介绍](https://blog.csdn.net/wangdamingll/article/details/120555777)        
* [简单工厂介绍](https://blog.csdn.net/wangdamingll/article/details/120564417)    
* [工厂方法介绍](https://blog.csdn.net/wangdamingll/article/details/120568256)      
* [抽象工厂介绍](https://blog.csdn.net/wangdamingll/article/details/120568303)    

#### 2.多态的虚函数表放在哪里？属于类还是对象
常量区(.rodata)，属于类  
![C内存布局](./picture/c内存布局.png "C内存布局")


#### 3.线程间同步和互斥  
互斥是对共享资源进行加锁，具有排他性。同步是在互斥的基础上，通过其他机制实现访问者对共享资源的访问  
追问:哪些机制？  
比如说互斥锁、信号量、条件变量(需要和互斥锁配合)、 原子操作等  

#### 4.类与类之间的关系   
##### [UML类图关系](https://segmentfault.com/a/1190000021317534)   
* 依赖:一个类作为另外一个类方法参数的方式    
* 关联:包含其他类指针成员变量  
* 聚合:见下面  
* 组合:见下面  
* 继承(泛化):一个类继承另外一个类  
* 实现:C++只不过面向接口的方式，通过纯虚函数实现  
追问:组合和聚合之间有什么关系
* 聚合:整体和部分之间的关系，部分可以独立整体而存在  
* 组合:比聚合关系更强，也是整体和部分之间的关系，具有相同的生命周期，部分不能独立整体而存在    

追问:各种关系耦合程度？
* 继承>组合>聚合>关联>依赖  
  
#### 5.你项目中的日志是如何实现输出到同一个文件中的？  
逻辑线程把需要记录的内容push到队列中,日志线程从队列中pop写入文件,也就是通过生产消费者模型的方式  

#### 6.给定一个数组，查找其中2个元数之前最大的差值
思路:循环一次，分别记录最大和最小值，最后相减即可，时间复杂度0(N)
```C++
int arr[3]={0,1,2};
int min =0;
int max =0;
for(int index=0;index<3;index++){
    if(arr[index]<arr[min]){
        min=index;
    }
    if(arr[index]>arr[max]){
        max = index;
    }
}
int maxNum = arr[max] - arr[min];
```

## 二.杭州字节跳动
### 节跳动面试第一轮(视频)
#### 1.map底层是由什么实现的 那set呢
map底层是由红黑树实现的，set底层也是由红黑树实现的  
追问:红黑树的特点及它的时间复杂度是多少？
* 红黑树的特点
1. 它一种特殊的二叉查找树
2. 每个节点是红色的或者是黑色的
3. 根节点和叶子节点都是黑色的
4. 如果一个节点是红色的，那个它的子节点就是黑色的
5. 一个节点到它子孙节点具有相同数目的黑色节点  
* 红黑树的时间复杂度(N为红黑树的元素个数)
1. 插入、搜索、删除时间复杂度:O(logN),创建时间复杂度O(NlogN)    

追问:你说map是有序的，那它通过什么规则实现的？  
对存入的元素重载了operator< 操作符   
#### 2.map和unordered_map的区别
1. map底层是红黑树实现的，unordered_map底层是哈希表(散列表)实现的
2. map的有序的，unirdered_map是无序的
3. map插入、查询稳定O(logN),unordered_map查询效率O(1),但是有可能退化为O(N)
4. map消耗的内存低，unordered_map消耗的内存高
5. 要求有序且对内存占用敏感，用map;要求查询效率，对内存占用不敏感，用unordered_map  

==后期补充==  
* 红黑树的特点?  
爱奇艺面试已经有了  
* 哈希表解决冲突方式?  
拉链法:类似于数组 + 链表的结构,冲突的元素放在链表中(新加入的放到开头)   
开放地址法:一个比较大的数组，有线性探测法和平方探测法解决冲突,平方探测法比较快  
线性探测法:地址增量:di = 1, 2, ... , m-1，其中，i为探测次数  地址 = now + di  
平方探测法:地址增量:di = (1)^2, -(1)^2, (2)^2, -(2)^2，… ，(q)2, -(q)^2 (q <= m/2), 地址 = now + di   
* 哈希表扩容规则?  
装载因子= 填入表中的元素个数 / 散列表的长度, 超过装载因子进行扩容  
装载因子一般是0.75,是时间和空间的折中选择    
* 哈希表扩容时size选择?  
选择不小于2n(最接近)的质数,也就是每次扩容翻倍,选择质数的原因是尽量将元素均匀散列      

#### 3.构造函数和析构函数执行顺序(继承体系下)
***构造函数和析构函数中的虚函数会去虚拟化，将会总是被静态地当做本类型的函数解析***
1. 构造函数执行顺序是从上而下
2. 析构函数执行顺序是从下而上
追问:析构函数为什么是虚函数  
当delete基类指针指向派生类对象的时候，应该先调用派生类析构函数，在调用基类析构函数，不是虚函数的话，只会调用基类析构函数，这样就产生了内存泄漏      

==后期补充==  
构造函数和析构函数执行顺序举例详细说明:    
```C++
#include <iostream>
using namespace std;
/*
构造函数执行顺序:
1. 在derived class constructor中,所有"virtual base classes"会被调用,从左到右,从最深到最浅
2. 在derived class constructor中,所有"上层base class"的constructors会被调用,以base class的声明顺序
3. 上述完成之后,对象的vptr(s)被初始化,指向相关的virtual table(s)
4. 如果有member initialization list的话,将在constructor体内扩展开来(以声明的顺序初始化).这必须在vptr被设定之后オ进行,以免有一个virtual member function被调用.
5. 程序员自身写的代码
*/

class ABase
{
public:
    ABase(){std::cout<<"ABase()"<<std::endl;}
    virtual void TestA(){}
};

class BBase
{
public:
    BBase(){std::cout<<"BBase()"<<std::endl;}
    virtual void TestB(){}
};

class CBase
{
public:
    CBase(){std::cout<<"CBase()"<<std::endl;}
    virtual void TestC(){}
};

class DBase
{
public:
    DBase(){std::cout<<"DBase()"<<std::endl;}
    virtual void TestD(){}
};

class E : public virtual ABase , public BBase
{
public:
    E() : c(){
        // 1 ABase  (含有自身vptr初始化)
        // 2 BBase  (含有自身vptr初始化)
        // 3 E 自身vptr初始化
        // 4 CBase  (含有自身vptr初始化)
        // 5 DBase  (含有自身vptr初始化)
        // 6 E
        std::cout<<"E()"<<std::endl;
        e = 0;
    }
    virtual void TestC(){}

public:
    int e;
    CBase c;
    DBase d;
};

int main()
{
    E c;
}
```

#### 4.C++是如何实现多态的
1. 多态的产生条件  
* 有继承关系
* 有虚函数重写
* 父类指针(引用)指向子类对象
2. 多态实现原理  
```C++
//CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(test main.cpp)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(test PUBLIC "IS_64_BIT_ARCH")
    message(STATUS "Target is 64 bits")
else()
    target_compile_definitions(test PUBLIC "IS_32_BIT_ARCH")
    message(STATUS "Target is 32 bits")
endif()

//main.cpp
#include <iostream>
using namespace std;

class Base{
public:
    Base(int m1 = 1):m1(m1){};
    virtual void VirtualBase1() {
        std::cout<<"this is the base vitual funciton 1"<<endl;
    }
    virtual void VirtualBase2() {
        std::cout<<"this is the base vitual funciton 2"<<endl;
    }
    virtual void VirtualBase3() {
        std::cout<<"this is the base vitual funciton 3"<<endl;
    }

public:
    int m1;
};
//派生类
class Base1 : public Base{
public:
    void VirtualBase2() override {
        std::cout<<"this is the base from subclass virtual function 2"<<endl;
    }
};
int main()
{
    void (Base::* VirtualBase1)() =&Base::VirtualBase1;
    void (Base::* VirtualBase2)() =&Base::VirtualBase2;
    void (Base::* VirtualBase3)() =&Base::VirtualBase3;
    void (Base1::* Base1VirtualBase1)() =&Base1::VirtualBase1;
    void (Base1::* Base1VirtualBase2)() =&Base1::VirtualBase2;
    void (Base1::* Base1VirtualBase3)() =&Base1::VirtualBase3;

    Base base;
    (base.*VirtualBase2)();
    Base1 base1;
    (base1.*Base1VirtualBase2)();

    std::cout<<"-------------------"<<std::endl;

    using Fun = void(*)();
#ifdef IS_32_BIT_ARCH
    void* baseVptr = (void*)*(int*)&base;
    Fun baseF1 = (Fun)*((int*)baseVptr + 0);
    (*baseF1)();
    Fun baseF2 = (Fun)*((int*)baseVptr + 1);
    (*baseF2)();
    Fun baseF3 = (Fun)*((int*)baseVptr + 2);
    (*baseF3)();

    void* base1Vptr = (void*)*(int*)&base1;
    Fun base1F1 = (Fun)*((int*)base1Vptr + 0);
    (*base1F1)();
    Fun base1F2 = (Fun)*((int*)base1Vptr + 1);
    (*base1F2)();
    Fun base1F3 = (Fun)*((int*)base1Vptr + 2);
    (*base1F3)();
#elif IS_64_BIT_ARCH
    long* baseVptr = (long*)*(long*)&base;
    Fun baseF1 = (Fun)*(baseVptr + 0);
    (*baseF1)();
    Fun baseF2 = (Fun)*((long*)baseVptr + 1);
    (*baseF2)();
    Fun baseF3 = (Fun)*((long*)baseVptr + 2);
    (*baseF3)();

    long* base1Vptr = (long*)*(long*)&base1;
    Fun base1F1 = (Fun)*((long*)base1Vptr + 0);
    (*base1F1)();
    Fun base1F2 = (Fun)*((long*)base1Vptr + 1);
    (*base1F2)();
    Fun base1F3 = (Fun)*((long*)base1Vptr + 2);
    (*base1F3)();
#else
#endif
    return 0;
}

通过结果可以看出，当派生类重新定义了基类的函数后其虚函数表中的指针发生了覆盖，而没有重新定义的地方则维持了基类虚函数的地址
```


#### 5.类的大小
***类大小的计算遵循结构体的对齐原则***  
1. 基本计算规则
* 类的大小与普通数据成员有关，与成员函数和静态成员无关。即普通成员函数，静态成员函数，静态数据成员，静态常量数据成员均对类的大小无影响
* 虚函数对类的大小有影响，是因为虚函数表指针带来的影响
* 虚继承对类的大小有影响，是因为虚基表指针带来的影响
* 空类的大小是一个特殊情况,空类的大小为1  
2. 特殊情况  
* 空类的继承  
当派生类继承空类后，派生类如果有自己的数据成员，而空基类的一个字节并不会加到派生类中去  
继承空类的派生类，如果派生类也为空类，大小也都为1。
* 一个类包含一个空类对象数据成员  
```C++
class Empty {};
class HoldsAnInt {
    int x;
    Empty e;
};
```
空类的1字节是会被计算进去的。而又由于字节对齐的原则，所以结果为4+4=8
* 虚继承的影响  Linux g++ 64位
```C++
//CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(testa test.cpp)

list(APPEND flags "-fdump-class-hierarchy")

target_compile_options(testa
  PRIVATE
    ${flags}
  )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)  
    target_compile_definitions(testa PUBLIC "IS_64_BIT_ARCH")  
    message(STATUS "Target is 64 bits")
else()  
    target_compile_definitions(testa PUBLIC "IS_32_BIT_ARCH")  
    message(STATUS "Target is 32 bits")
endif()

message(STATUS "flags:${flags}")

//test.cpp
#include <iostream>
using namespace std;

class A {
    public:
    int a = 0;;
};
class B:virtual public A{
    virtual void myfunB(){}
};
class C:virtual public A{
    virtual void myfunC(){}
};
class D:public B,public C{
    virtual void myfunD(){}
};

int main()
{
    std::cout<<"A::size:"<<sizeof(A)<<std::endl; // 4
    std::cout<<"B::size:"<<sizeof(B)<<std::endl; // 8 + 8
    std::cout<<"C::size:"<<sizeof(C)<<std::endl; // 8 + 8
    std::cout<<"D::size:"<<sizeof(D)<<std::endl; // 8 + 8 + 8
    return 0;
}

解释：A为int大小,  B和C含有一个vptr指针和int,含有对齐一共16,D含有int和B的vptr、C的vtpr指针,对齐一共24
注意:虚拟继承的虚基类的地址的offset被放到了相当于vptr[-1]的位置  

//打开CMakeFiles/testa.dir/test.cpp.002t.class
Class A
    size=4 align=4
    base size=4 base align=4
A (0x0x7fb646579d20) 0

Vtable for B
B::_ZTV1B: 4 entries
0     8
8     (int (*)(...))0
16    (int (*)(...))(& _ZTI1B)
24    (int (*)(...))B::myfunB

VTT for B
B::_ZTT1B: 1 entries 
0     ((& B::_ZTV1B) + 24)

Class B
    size=16 align=8
    base size=8 base align=8
B (0x0x7fb646586d00) 0 nearly-empty
    vptridx=0 vptr=((& B::_ZTV1B) + 24)
A (0x0x7fb646579d80) 8 virtual
    vbaseoffset=-24

Vtable for C
C::_ZTV1C: 4 entries
0     8
8     (int (*)(...))0
16    (int (*)(...))(& _ZTI1C)
24    (int (*)(...))C::myfunC

VTT for C
C::_ZTT1C: 1 entries 
0     ((& C::_ZTV1C) + 24)

Class C
    size=16 align=8
    base size=8 base align=8
C (0x0x7fb646586dd0) 0 nearly-empty
    vptridx=0 vptr=((& C::_ZTV1C) + 24)
A (0x0x7fb646579e40) 8 virtual
    vbaseoffset=-24

Vtable for D
D::_ZTV1D: 9 entries
0     16
8     (int (*)(...))0
16    (int (*)(...))(& _ZTI1D)
24    (int (*)(...))B::myfunB
    vptridx=0 vptr=((& C::_ZTV1C) + 24)
A (0x0x7fb646579e40) 8 virtual
    vbaseoffset=-24

Vtable for D
D::_ZTV1D: 9 entries
0     16
8     (int (*)(...))0
16    (int (*)(...))(& _ZTI1D)
24    (int (*)(...))B::myfunB
32    (int (*)(...))D::myfunD
40    8
48    (int (*)(...))-8
56    (int (*)(...))(& _ZTI1D)
64    (int (*)(...))C::myfunC

Class D
    size=24 align=8
    base size=16 base align=8
D (0x0x7fb64659c930) 0
    vptridx=0 vptr=((& D::_ZTV1D) + 24)
B (0x0x7fb646586ea0) 0 nearly-empty
    primary-for D (0x0x7fb64659c930)
    subvttidx=8
    A (0x0x7fb646579f00) 16 virtual
        vbaseoffset=-24
C (0x0x7fb646586f08) 8 nearly-empty
    subvttidx=16 vptridx=24 vptr=((& D::_ZTV1D) + 64)
    A (0x0x7fb646579f00) alternative-path
```
## 三.游族网络
#### 1.介绍一下zookeeper  
* ZooKeeper是一个分布式的，开放源码的分布式应用程序协调服务
* zookeeper单台机角色:leader/follower/observer
* zookeeper是怎样保证主从节点的状态同步
1. 当整个服务框架在启动过程中，或是当Leader服务器出现网络中断崩溃退出与重启等异常情况时，ZAB就会进入恢复模式并选举产生新的Leader服务器。
2. 当选举产生了新的Leader服务器，同时集群中已经有过半的机器与该Leader服务器完成了状态同步之后，ZAB协议就会退出崩溃恢复模式，进入消息广播模式。
3. 当有新的服务器加入到集群中去，如果此时集群中已经存在一个Leader服务器在负责进行消息广播，那么新加入的服务器会自动进入数据恢复模式，找到Leader服务器，并与其进行数据同步，然后一起参与到消息广播流程中去
* zookeeper分布式锁算法流程
1. 客户端连接zookeeper，并在/lock下创建临时的且有序的子节点，第一个客户端对应的子节点为/lock/lock-0000000000，第二个为/lock/lock-0000000001，以此类推。
2. 客户端获取/lock下的子节点列表，判断自己创建的子节点是否为当前子节点列表中序号最小的子节点，如果是则认为获得锁，否则监听/lock的子节点变更消息，获得子节点变更通知后重复此步骤直至获得锁；
3. 执行业务代码；
4. 完成业务流程后，删除对应的子节点释放锁。
* 集群中有 3 台服务器，其中一个节点宕机，这个时候 zookeeper 还可以使用吗？
可以继续使用，单数服务器只要没超过一半的服务器宕机就可以继续使用(过半机制)
* zookeeper脑裂
假死：由于心跳超时（网络原因导致的）认为leader死了，但其实leader还存活着。
脑裂：由于假死会发起新的leader选举，选举出一个新的leader，但旧的leader网络又通了，导致出现了两个leader ，有的客户端连接到老的leader，而有的客户端则连接到新的leader
总结:集群中的节点监听不到leader节点的心跳, 就会认为leader节点出了问题, 此时集群将分裂为不同的小集群, 这些小集群会各自选举出自己的leader节点, 导致原有的集群中出现多个leader节点.
* zookeeper集群数量配置原则(可以防止脑裂)   
  可用节点数量 > 集群总结点数量/2 可保证正常选举leader，集群正常运行  
* zookeeper集群为什么要部署成奇数?  
  这样是为了以最大容错服务器个数的条件下,能节省资源. 比如,最大容错为2的情况下,对应的ZooKeeper服务数,奇数为5,而偶数为6,也就是6个ZooKeeper服务的情况下最多能宕掉2个服务,所以从节约资源的角度看,没必要部署6(偶数)个ZooKeeper服务节点.   
#### 2.网络编程中ET/LT特点  
* ET,边沿触发模式，事件只触发一次; LT,水平触发模式，只要满足事件触发条件，会一直触发  
追问:哪种效率更高
* 边沿触发效率更高些.ET模式，只要epoll_wait函数检测到事件发生，通知应用程序立即进行处理，后续的epoll_wait函数将不再检测此事件。因此ET模式在很大程度上降低了同一个事件被epoll触发的次数，因此效率比LT模式高
#### 3.libevent特点
* Libevent 是一个高性能、轻量级、跨平台的C语言网络库，是基于Reactor模式的网络库，even_base循环->注册event事件->处理事件回调  
#### 4.线程间通讯方式
1. 同一个进程间2个线程间通讯
* 全局变量
* 通过堆内存共享资源的方式  
2. 不同进程间线程间通讯(进程间通讯)
* 管道(无名管道):使用最简单,使用在父子进程间,半双工(单向流动),pip()创建管道读写端  
* fifo(有名管道):是一种文件类型,可以在无关进程间使用     
* 信号:开销最小 signal(int sigal,handler)    
* 信号量:是一个计数器,可以用来控制多个进程对共享资源的访问  
* 共享映射区:存储映射I/O:mmap()创建映射区  
* 本地套接字:最稳定,创建本地套接字完成通信,可用于不同主机间   
#### 5.多态如何实现的
1. 多态的产生条件  
* 有继承关系
* 有虚函数重写
* 父类指针(引用)指向之类对象
2. 多态实现原理    
利用了C++ RTTI(运行时绑定机制),虚函数表是一个函数指针数组，属于类，当派生类发生虚函数重写时，对应的虚函数在虚函数表中的指针发生了覆盖，而没有重新定义的地方则维持了基类虚函数的地址
这样通过vptr指针和偏移地址就能调用到正确的虚函数

## 四.塔人网络
#### 1.谈谈map
map是key-value形式的数据结构，具有自动排序的功能，底层是由红黑树实现的  
追问:红黑树的特点及它的时间复杂度是多少？
* 红黑树的特点
1. 它一种特殊的二叉查找树
2. 每个节点是红色的或者是黑色的
3. 根节点和叶子节点都是黑色的
4. 如果一个节点是红色的，那个它的子节点就是黑色的
5. 一个节点到它子孙节点具有相同数目的黑色节点  
* 红黑树的时间复杂度(N为红黑树的元素个数)
1. 插入、搜索、删除时间复杂度:O(logN)  
2. 创建时间复杂度:O(NlogN)  
#### 2.谈谈vector
* vector是一种容器，底层是由动态数组实现的
* vector支持随机访问、动态扩容的特点，查找效率O(1),尾部出入删除O(1),头部插入删除O(N)  
追问:vector扩容机制  
STL采用2倍扩容机制
* 采用成倍扩容方式可以保证push_back常数时间的复杂度
* 扩容因子不能太大，否则会造成堆内存浪费，普遍扩容因子采用2或者1.5  
1)以2倍的方式扩容，导致下一次申请的内存必然大于之前分配内存的总和，导致之前分配的内存不能再被使用,对缓存不是很友好  
2)1.5倍的增长方式可以更好的实现对内存的重复利用  
3)C++标准中并没有规定使用哪个扩容因子
* 参考地址:[C++ STL vector扩容机制](https://www.zhihu.com/question/36538542/answer/67929747)
#### 3.libuv主要有哪些接口
uv_default_loop() uv_tcp_init() uv_tcp_bind() uv_listen() uv_run() uv_accept() uv_read_start() 等等
#### 4.如果让你设计一个游戏背包，你会如何设计数据结构
```C++
vector<GoodBaseClass*>
Weapon:public GoodBaseClass  HpClass:public GoodBaseClase
```
==*后期补充*==  
```C++
//背包管理器(包含背包的每一个页签)    
class BoxManage
{
    std::array<BoxBase* /*页签类*/, MAX/*页签id*/> boxs;
};

//每一个背包页签的类
class BoxBase
{
    std::map<pos/*背包格子位置*/, Item* /*道具基类*/> items;
};
```



## 五.紫龙游戏
### 紫龙游戏一面
#### 1.线程同步和互斥
互斥是对共享资源进行加锁，具有排他性。同步是在互斥的基础上，通过其他机制实现访问者对共享资源的访问  
追问:哪些机制？  
比如说互斥锁、信号量、条件变量(需要配合互斥锁),原子操作等  
#### 2.介绍map
* 描述:map存储key-value数据   
* 特点:有序(对存入的元素重载了operator<操作符)      
* 底层实现:map底层是由红黑树实现的   
* 时间复杂度:插入、搜索时间复杂度:O(logN)       
* 红黑树的特点
1. 它一种特殊的二叉查找树
2. 每个节点是红色的或者是黑色的
3. 根节点和叶子节点都是黑色的
4. 如果一个节点是红色的，那个它的子节点就是黑色的
5. 一个节点到它子孙节点具有相同数目的黑色节点  
#### 3.unordered_map
* 描述:是具有key-value形式的关联容器   
* 特点:无序   
* 底层实现:底层是用hash_table实现的   
* 时间复杂度:搜索、插入和删除拥有平均O(1)复杂度,有可能退化成O(N),
* 如果key是自定义对象
1. 提供哈希函数
2. 重载等号操作符
#### 4.map和unordered_map的区别  
1. 特点:map的有序的，unirdered_map是无序的,map重载了<实现有序, unordered_map重载了==
2. 底层实现:map底层是红黑树实现的，unordered_map底层是哈希表(散列表)实现的  
3. 时间复杂度:map插入,查询和删除稳定O(logN),unordered_map查询效率O(1),但是有可能退化为O(N)
4. 使用场景:map消耗的内存低，unordered_map消耗的内存高,所以要求有序且对内存占用敏感，用map;要求查询效率，对内存占用不敏感且无序，用unordered_map
#### 5.hash_table冲突解决方法
* 开放地址法(常用)  
1. 线性探查法:index index+1 index+2 ... 大于表大小取模  
2. 平方探查法:index index+1^2 index-1^2 index+2^2 index-2^2 index+q^2 index-q^2 (q < size/2)...  大于表大小取模  
* 拉链法(常用):链表的数组, 指针数组,里面每个元素都是链表的首元素指针  
* 在哈希:hashcode1() hashcode2() ... 直到不在冲突  
* 建立公共溢出区:如果溢出--->放入公共溢出区里面  
#### 6.int* const 和 const int *
int* const p:指针的指向不可修改,可以修改*p的值
const int *P:指针的指向可以修改,但是不可修改*p的值 
#### 7.多维数组和数组的数组区别
多维数组的内存是连续的，数组的数组(指针数组)的内存可以是不连续的
#### 8.C++ RTTI
* C++ RTTI,运行时类型识别,C++引入这个机制是为了让程序在运行时能根据基类的指针或引用来获得该指针或引用所指的对象的实际类型
* C++ 通过以下2中方式提供RTTI
1. typeid运算符，该运算符返回其表达式或类型名的实际类型
2. dynamic_cast运算符，该运算符将基类的指针或引用安全地转换为派生类类型的指针或引用
* typeid和dynamic_cast运算符底层原理  
参考地址:[C++ RTTI机制](https://blog.csdn.net/ljianhui/article/details/46487951)
#### 9.C++ 的四种转换类型
* static_cast:内置的基本类型、有相互关系的类型
* const_cast:去掉const属性
* reinterpret_cast:操作指针，改变指针(引用)类型  指针->整数  整数->指针
* dynamic_cast:基类<->派生类转换

#### 10.为什么C++要引入虚继承
* 原因
虚继承是解决C++多重继承问题(典型的是菱形继承问题)的一种手段,从不同途径继承来的同一基类，会在子类中存在多份拷贝。这将存在两个问题：其一，浪费存储空间；第二，存在二义性问题
* 实现原理
vbptr指的是虚基类表指针(virtual base table pointer),该指针指向了一个虚基类表(virtual table)虚表中记录了虚基类与本类的偏移地址,通过偏移地址，这样就找到了虚基类成员,而虚继承也不用像普通多继承那样维持着公共基类(虚基类)的两份同样的拷贝，节省了存储空间
* 参考网址:[C++ 虚拟继承实现内存布局](https://blog.csdn.net/xiejingfa/article/details/48028491)
#### 11.寻路算法
* [寻路算法介绍](https://www.jianshu.com/p/74ca39e670ba)  
* [A*寻路算法示例代码](https://blog.csdn.net/wangdamingll/article/details/105793918)  
#### 12.链表部分翻转
题目:1->2->...->m...->n->...,将m->...->n部分翻转  
* [单向链表:头插法](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/ZiLongLianBiao1.cpp)    
* [单向链表:容器法](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/ZiLongLianBiao2.cpp)       
* [单向链表:三指针法](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/ZiLongLianBiao3.cpp)     
* [双向链表:双指针法](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/ZiLongLianBiao4.cpp)   

### 紫龙游戏二面(CTO面试)
#### 1.静态局部变量的作用有哪些
* [C++ static关键字总结](https://zhuanlan.zhihu.com/p/37439983)  

==*后期补充*==   
补充一下特别需要注意的    

* 仅本模块可以使用变量,其他模块都不可以,即使extern修饰也不行,即使#include包含文件,也是另外一个名字相同的变量  
* 防止名称重复污染,在其他模块static修饰的变量,本模块也可以声明名字相同的变量  
#### 2.以下这段代码主要实现哪些功能
```C++
{
    static int i = 0;
    i++;
    return i;
}
```
* 输出 1 2 3 4 5 6等一系列数字  
追问:一定是这样吗？  
* 当数字超出4个字节存储的极限会产生溢出问题  
追问:不考虑溢出  
* 没回答出来  
追问:如果是多线程情况下呢?  
* 会产生资源竞争现象  
追问:避免资源竞争的机制有哪些?从粒度范围来说
* 1.std::call_once std::once_flag 多个线程执行只初始化一次 [C++ std::call_once](https://zh.cppreference.com/w/cpp/thread/call_once)
* 2.std::future 期物(可作为屏障) [C++ std::future](https://zh.cppreference.com/w/cpp/thread/future)
* 3.std::condition_variable 条件变量(需要配合互斥量使用) [C++ std::condition_variable](https://zh.cppreference.com/w/cpp/thread/condition_variable)
* 4.std::mutex 互斥量 [C++ std::mutex](https://zh.cppreference.com/w/cpp/thread/mutex)
* 5.std::atomic模板 原子操作  [C++ atomic](https://zh.cppreference.com/w/cpp/atomic/atomic)  
追问:原子操作有哪些原语?
* std::atomic<T>::is_lock_free
* fetch_add
* fetch_sub
* 重载+ - 操作
* store
* load 
* exchage  

==*后期补充*==  
硬是要从粒度范围来说避免资源竞争的机制有哪些的话,  
操作系统级别,代表有std::mutex,特点是由于操作系统调度,没有获取到锁的线程sleep,但是其他没有相关逻辑的线程不受影响,继续运行  
cpu级别,代表有std::atomic,特点是一旦一个线程获取了权限,其他线程都会被阻塞在这个cpu上      

#### 3.树的广度优先遍历
* 利用队列先进先出的特性，现将根节点放入->队列不为空->弹出节点->访问数据->放入左孩子节点->放入右孩子节点->队列不为空->.......
* 参考:[二叉树广度优先搜索示例](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/TreeBreadthFirstSearch.cpp)
```C++
//广度优先搜索
void BreathFirstSearch(BinaryTreeNode* root) {
	queue<BinaryTreeNode*> binaryTreeQueue;
	binaryTreeQueue.push(root);
	while (!binaryTreeQueue.empty()) {
		BinaryTreeNode* root = binaryTreeQueue.front();
		binaryTreeQueue.pop();
		cout << root->ch << " ";
		if(root->lchild!=NULL) binaryTreeQueue.push(root->lchild);
		if(root->rchild!=NULL) binaryTreeQueue.push(root->rchild);
	}
	return;
}
```

## 六.鼹鼠网络
#### 1.epoll底层实现原理图解
* ![epoll底层实现原理](./picture/epoll底层实现原理.jpg "epoll底层实现原理")  

==*后期补充*==  
[参考网址](https://www.cnblogs.com/lojunren/p/3856290.html)  
[参考网址](http://blog.chinaunix.net/uid/28541347/sid-193117-list-2.html)  
1. epoll的工作流程是如何的？
* epoll_create创建epoll句柄  
* epoll_ctrl控制监听事件,增加、改变或者删除fd  
* epoll_wait处理相应的读写事件    
2. epoll有哪两种工作模式?各自有啥特点?  
* LT:水平模式:只要满足条件,事件就会一直被触发,效率低    
* ET:边沿模式:事件满足条件,只会触发一次,效率高    
3. epoll的底层原理是什么?  
* epoll底层用红黑树存储epollItem节点,并用rdlist双向链表存储满足事件条件的epitem  
* 先调用epoll_ctrl将需要监听的事件注册,与网卡驱动建立回调关系        
* 当事件满足条件时,调用这个回调函数(ep_poll_callback)将会把fd对应的epollItem放入到rdlist双向链表中  
* epoll_wait调用发现rdlist不为空,调用相应的函数(ep_events_transfer)将rdlist拷贝到txlist中，并将rdlist清空    
* ep_send_events扫描txlist中的每个epollitem,并调用fd对应的poll,获取事件的最新状态,并将事件封装到struct epoll_event中,返回给上层      
4. epoll 如何发送大量数据?  
* 前提条件:可以适当调大系统写缓冲区的大小    
* 第一种:当需要写数据的时候,监听可写事件,在可写事件回调中,写完所有数据后,移除可写事件,这种效率偏低,即使要写的数据很少,也需要产生对应的系统调用       
* 第二种:当有需要写数据的时候,直接调用write写数据,直到返回-1且errno=EAGAIN的时候,监听可写事件,在可写事件的回调中继续写完所有数据后,移除可写事件.这种方式可以有效减少写的数据量较少的时候触发相应的系统调用,效率比较高    


#### 2.将一个有序数组打乱算法
* [Fisher–Yates shuffle (洗牌算法)](https://en.wikipedia.org/wiki/Fisher–Yates_shuffle)
* [C++ 随机数](https://zh.cppreference.com/w/cpp/numeric/random)
```c++
#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
using namespace std;

int main()
{
    const int num =10;
    std::array<int, num> array{10,9,8,7,6,5,4,3,2,1};

    srand(time(nullptr));
    for(int index =num-1 ; index > 0; index--)
    {
        std::swap(array[index], array[rand()%index]);
    }

    std::for_each(std::begin(array),std::end(array),[](const int& item){
       std::cout<<item<<" ";
    });
    std::cout<<std::endl;
    return 0;
}
```

## 七.京东(上海)面试
### 电话面试
#### 1.Http Websocket Tcp三者之前的区别
* [http1.0 1.1 2.0](https://juejin.im/entry/5981c5df518825359a2b9476)
* http1.0 http1.1 http2.0的区别  
HTTP/1.* 一次请求-响应，建立一个连接，用完关闭；每一个请求都要建立一个连接。  
HTTP/1.1 默认支持长连接(keep-alive)和请求的流水线（Pipelining）处理,建立一次连接，可以多个request共用。  
注:Pipeling解决方式为，若干个请求排队串行化单线程处理，后面的请求等待前面请求的返回才能获得执行机会，一旦有某请求超时等，后续请求只能被阻塞，毫无办法，也就是人们常说的线头阻塞  
HTTP/2 支持多路复用。多个请求可同时在一个连接上并行执行。某个请求任务耗时严重，不会影响到其它连接的正常执行。  

* http和websocket区别和联系   

相同点:  
1. 都是基于tcp的应用层协议    
2. 都可以作为web浏览器和服务通讯的协议使用     
    
不同点:  
1. WS连接建立之后,支持双向通信,而http是req-res的模式,不支持双向通信  
2. ws需要首先经过http握手建立连接之后才能通信,而http是tcp三次握手之后,能够通信   
3. websocket要比http更为高效(websocket能保持连接状态,全双工)       

备注:websocket握手过程?  
1. 客户端向服务器发起WebSocket握手请求，请求中包含一些头部信息，如Upgrade、Connection、Sec-WebSocket-Key   
2. 服务器收到客户端的WebSocket握手请求，需要进行一些验证和响应。服务器首先需要验证客户端的请求是否符合WebSocket协议的规范，验证通过，服务器会返回一个HTTP响应，其中，101 Switching Protocols表示协议切换成功，Upgrade和Connection字段与客户端请求中的相同，Sec-WebSocket-Accept字段是一个加密字符串，用于告诉客户端WebSocket握手成功   
3. 客户端收到服务器的响应后，会进行一些验证，如果验证通过，客户端和服务器之间的WebSocket连接就建立成功了，此后客户端和服务器之间就可以进行实时通信    
说明:  
1). Sec-WebSocket-Key:是一个Base64编码的16字节随机字符串   
2). Sec-Websocket-Accept:   
首先将一个固定的字符串258EAFA5-E914-47DA-95CA-C5AB0DC85B11拼接到Sec-WebSocket-Key对应值的后面  
对拼接后的字符串进行一次SHA-1计算  
将计算结果进行Base-64编码  

* tcp和websocket的区别和联系    

联系:  
1. websocket是基于tcp的应用层协议    
2. websocket握手成功建立连接之后,具有全双工特点,tcp也具有全双工特点  
         
区别:tcp是传输层协议,websocket是应用层协议  
追问:有Http了,为什么还要用Websocket  
* 由客户端主动轮询变为服务端推送，避免了轮询消耗         
* 避免了request/response这种请求回应模式,降低了延迟,降低了网络流量(请求会有http header, 获取静态资源等操作)   
* ws支持双向通信,更加通用灵活    
### 二轮面试
#### 1.Libevent用过吗?有哪些坑?是采用什么模式?具体定义了哪些宏?  
1. 坑:
* Libevent处理用户read_cb的机制是边沿触发的机制(只有evbuffer的长度大于低水位才会触发用户的读回调)并且bufferevent_read()默认每次最大读取4096个字节,所以必须要判断底层数据有没有读完,没有读取完要一直读取    
* libevent发送大量数据也是要非常注意的  
* 如果给的ip不合法,调用befferconnect(),会先触发BEV_EVENT_ERROR回调,再触发BEV_EVENT_CONNECTED回调,所以要将这种情况区分开,所以需要额外的socket管理逻辑  
2. 对于scoket fd的操作默认采用了LT模式       
[Libevent bufferevent工作流程](https://blog.csdn.net/luotuo44/article/details/39344743)    
通过上面文章的流程,可以推断出evbuffer操作的fd应该采用的是LT  
依据如下:
一开始fd作为读事件注册,fd有数据时,libevent为了提高效率,必然是有多少数据读多少,如果此时超过了设置的读高水位,libevent会挂起读事件,防止出现死循环,那么是如何挂起读事件的呢?是直接移除了fd的读事件，据此推断出,这个fd对应的操作应该采用的是LT,因为ET不会一直触发      

追问:LT/ET有什么区别?哪种效率更高?
* LT:水平触发，如果事件满足条件，会一直触发
* ET:边沿触发，如果事件满足条件，只会触发一次
* 相比较来说，ET的效率会高一些  
追问:为什么ET的效率会高一些
* ET满足条件的事件只会触发一次. 而LT只要满足条件,会一直触发,所以LT的系统调用更多  
* 因为LT要一直触发, 所以LT模式下维护的就绪队列(rdlist)大小相对于ET模式肯定大,故LT轮询所有的fd总比ET轮询的fd大
1. 相关宏  
* BEV_EVENT_CONNECTED BEV_EVENT_ERROR BEV_EVENT_EOF BEV_EVENT_TIMEOUT BEV_EVENT_READING BEV_EVENT_WRITING (Epoll中有 EPOLLERROR EPOLLIN EPOLLOUT)  
#### 2.Libevent timer有用过吗
* 使用过  
追问:如何使用的?  
* 创建一个event_timer事件，设置好时间间隔和回调，加入到loop中，在回调函数中处理逻辑发送网络包逻辑  
补充:libevnet采用时间堆(最小堆)实现，最小堆是什么数据结构?    
* [堆介绍](https://blog.csdn.net/wangdamingll/article/details/106146519)   
* 基于时间堆的时间复杂度:插入O(logn)、删除O(1)、查找O(1),参考:[时间堆(最小堆) 定时器](https://blog.csdn.net/liushall/article/details/81331591)
* 基于时间轮的时间复杂度:插入O(1)、删除O(1)、查找O(1),参考:[时间轮 定时器](https://blog.csdn.net/wangdamingll/article/details/121407531)      

#### 3.Libevnet发送大量数据时,怎么办？
* 参考网址:[Libevent bufferevent工作流程](https://blog.csdn.net/luotuo44/article/details/39344743)    
* 适当调整系统so_send_buff/so_recive_buff的大小,调整依据:保证滑动窗口的大小>=带宽*延迟        
* 尽量使用大缓存buffer,一次调用bufferevent_write()能够写入更多数据,一直循环直到要发送的数据被写完(其实是被添加到了evbuffer中了)   
原理:bufferevent_write()内部实现是将数据添加到evbuffer中,并且在evbuffer的回调中开始监听fd的可写事件,一旦fd可写,bufferevent_cb()将会被调用,它的实现是一直往socket的输出缓冲区里面写,由于是大量数据,socket的输出缓冲区被填满,但是此时并没有移除fd的可写事件,等待下次继续执行,直到evbuffer的被写完,然后移除fd的可写事件        
* 由于是大量数据,循环bufferevent_write()可能会失败,有可能是内部evbuffer填满了,sleep一下,稍后再试  
* 另外也可以考虑,先执行一次bufferevent_write(),然后在写回调函数中继续发送数据  
原理:当evbuffer中的数据低于低水位的时候就会调用用户设置的写事件回调函数继续往evbuffer中添加数据,这种方式有比较少的系统调用次数  
#### 4.Libevent VS Libuv
* [Libevent和Libuv的对比](https://blog.csdn.net/lijinqi1987/article/details/71214974)   
* libevent:
1. c语言写的跨平台事件库
2. 采用异步事件机制的反应堆模型    
3. linux下采用epoll,windows下采用iocp(支持不够友好)   
4. 同步io模型  
5. [参考网址](https://libevent.org/)    
* lbuv  
1. c语言写的跨平台事件库
2. 采用异步事件机制,内部采用一定顺序访问各类事件  
3. linux采用libev(epoll),windows下采用iocp     
4. 采用异步io模型    
5. [参考网址](https://juejin.cn/post/6844903826353455111)    
6. [参考网址](http://libuv.org/)    
#### 5.你用过哪些设计模式?  
* 查看爱奇艺面试  
追问:单例如何写呢?  
* 查看爱奇艺面试 
#### 6.内存池有用过吗?实现原理是什么
1). 采用同类型array,元素是指针,使用malloc、free来实现  
如果发现内存池中没有,先mallc,如果有,直接返回地址  
不用的时候,将地址放回去  
2). 采用同类型的array,里面元素是指针,placement new来实现  
如果发现内存池中没有,先分配一块内存,然后调用placement new,返回地址,如果有内存,直接调用placement new,然后返回地址    
不用的时候,手动调用析构函数,然后将地址放回去    
* 参考网址:[C++ placement new 简单内存池使用](https://www.jianshu.com/p/b52a5df69c88)
* 参考网址:[SGI-STL内存池实现原理](https://blog.csdn.net/u012611878/article/details/79187348)    
* [示例代码](https://github.com/wangdamingll/Cplusplus-Common-Tools/tree/master/MemoryPool)    

==*后期补充*==  
* [C/C++内存对齐规则](https://zhuanlan.zhihu.com/p/30007037)      
* [C/C++内存对齐规则](http://light3moon.com/2015/01/19/[%E8%BD%AC]%20%E5%86%85%E5%AD%98%E5%AF%B9%E9%BD%90/)     
     
自己总结一下:    
1. 不使用伪指令#pragma pack(n):C编译器将按照n字节对齐   
* 为每一个变量或数据单元按其自然对界条件分配空间     
* 结构体的首地址要能被所有的成员中最大的对齐值整除   
* 结构体的大小要能被所有的成员中最大的对齐值整除  
```C++
#include <iostream>
using namespace std;

struct Test
{
    char x1;
    short x2;
    float x3;
    char x4;
};

int main()
{
    //Test的每个成员的对齐值按照自己的自然对界条件,即对齐值为sizeof(成员类型)
    //Test的所有成员中最大的对齐值是float 4字节,所以结果体的首地址和大小要能被4整除  
    std::cout<<sizeof(Test)<<std::endl;
    return 0;
}
```   

2. 使用伪指令#pragma pack(n)   
补充:有效对其值:是给定值#pragma pack(n)和结构体中最长数据类型长度中较小的那个。有效对齐值也叫对齐单位. 即 有效对齐值 = min(n, max(结构体成员自然对齐))   
* 每个成员的对齐值都是该成员大小与有效对齐值中较小那个,即 成员对齐值 = min(sizeof(成员), 有效对齐值)   
* 结构体的首地址要能被有效对齐值整除    
* 结构体的大小要能被有效对齐值整除  
举例稍等   
```c++
#include <iostream>
using namespace std;

#pragma pack(2)
struct{
    char c1;    //对齐值1
    int i;      //对齐值2
    char c2;    //对齐值1
}Test;

int main()
{
    std::cout<<sizeof(Test)<<std::endl;// 8个字节
    return 0;
}
```

#### 7.智能指针有用过吗?有哪几种类型 区别是什么  
* 参考网址:[C++ 智能指针](https://www.jianshu.com/p/e4919f1c3a28)
* 1. 为什么使用智能指针?   
1). 忘记delete   
2). 当出现异常返回的时候，即使写了delete，也有可能执行不到      
* 2. C++11为什么舍弃auto_ptr? 或者说auto_ptr有什么缺陷，与unique_ptr有什么区别?  
1). auto_ptr的缺陷: (1) auto_ptr相互赋值采用的是copy语义,可能带来指针double delete. (2) auto_ptr不能处理对象数组,默认析构行为是delete,不支持delete[]  
2). 与unique_ptr的区别: (1). auto_ptr相互赋值是copy语义,unique_ptr是move语义. (2). auto_ptr不支持delete[]操作,而unique_ptr支持    
* 3. auto_ptr unique_ptr share_ptr weak_ptr 各有什么特点  
1). auto_ptr: 满足基本需求,但是是copy语义,不能支持delete[]  
2). unique_ptr: move语义,独占资源, 支持自定义析构逻辑  
3). share_ptr: 引用计数实现,共享资源,支持自定义析构逻辑,但是可能会有循环引用的缺陷    
4). weak_ptr: 与share_ptr配合使用,能够避免share_ptr的循环引用缺点,弱引用计数,不能操作资源          
* 4. 指针相互赋值?  
1). share_ptr(auto_ptr) share_ptr(unique_ptr) share_ptr(share_ptr)  
2). share_ptr = weak_ptr.lock()  weak_ptr = share_ptr   
3). unique_ptr(auto_ptr)  
#### 8.你遇到过内存泄漏吗?
* 遇到过  
追问:如何避免和检测?
* 细心,new 记得delete
* 可以考虑使用智能指针
* 检测的话:[Valgrind的使用请见手册](http://valgrind.org/docs/manual/manual.html)    
* [代码示例](https://github.com/wangdamingll/Cplusplus-Common-Tools/blob/master/timer/READEME.txt)        

#### 9.你读过其他开源项目吗?
* uWebsockets,项目可能需要，采用C++17标准写的(C++17 head_only)，网络部分采用libuv，属于跨平台库
* 用vs2017写demo遇到的问题:{ }赋值问题  
* 浅读过部分libevent的实现:bufferevent的读和写     
* 浅读过部分epoll的底层实现:epoll事件触发的流程    

## 八.美团点评
### 第一轮
#### 1.设计模式
* 单例:特点:只有一个实例        
* 简单工厂(不是设计模式 但是太常用了):特点:选择合适的实例          
* 工厂模式:将选择实例的实现推迟到子类        
* 抽象工厂:生产一系列具有约束条件的产品簇      
* 观察者模式:触发联动        
* 具体参考爱奇艺面试    
#### 2.你常用的加密算法是什么
* AES:对称加密方式,分组加密,数据分组长度必须为128bits,使用的秘钥长度可以为128、192、256bits.     
  参考网址:[AES算法介绍](https://blog.csdn.net/lisonglisonglisong/article/details/41909813)
* RSA:非对称加密方式. RSA算法的核心,在于大整数的质因数分解是一件非常困难的事情   
* RSA算法参考网址:[RSA算法原理一](http://www.ruanyifeng.com/blog/2013/06/rsa_algorithm_part_one.html) [RSA 算法原理二](http://www.ruanyifeng.com/blog/2013/07/rsa_algorithm_part_two.html)  
追问:RSA你们是如何使用的
* 1. 加密数据  
1). 先用对方的RSA公钥加密AES秘钥   
2). 再用AES秘钥加密明文数据    
* 2. 验证签名  
1). 对方用自己的私钥签名, 我这边用对方的公钥验证签名    

补充:  
对称加密算法:加密和解密使用同样规则(简称"密钥")  
非对称加密算法:加密和解密可以使用不同的规则  
#### 3.TCP为什么是三次握手,为什么不是两次或者是四次呢
* 是为了在不可靠的信道上建立可靠的数据通道最少的交互方式,本质上是两端交换seqnumber  
* [TCP为什么设置三次握手,而不是二次或者四次](https://www.zhihu.com/question/24853633)  
追问:如果中途有一次ACK没有收到，会发生什么  
这里需要参考tcp状态转换图,这里分3种情况:       
1). 第一个包，即A发给B的SYN中途被丢，没有到达B   
A会周期性超时重传，直到收到B的确认  
2). 第二个包，即B发给A的SYN+ACK中途被丢，没有到达A   
B会周期性超时重传，直到收到A的确认      
3). 第三个包，即A发给B的ACK中途被丢，没有到达B  
A发完ACK,单方面认为TCP为Established状态，而B显然认为TCP为SYN_RCVD状态：  
a.假定此时双方都没有数据发送，B会周期性超时重传，直到收到A的确认，收到之后B的TCP连接
也为Established状态，双向可以发包。   
b.假定此时A有数据发送，B收到A的Data + ACK,自然会切换为established状态，并接受A的Data.   
c.假定B有数据发送，数据发送不了，会一直周期性超时重传SYN + ACK,直到收到A的确认才可以发送数据。   

追问:那Tcp为什么要四次挥手呢？3次不行吗?  
* 不行,因为tcp是全双工通讯,主动关闭的一方数据可能已经发送完了，但是被动关闭的一方数据可能还没有发送完，四次挥手能够保证被动方把数据发送完在通过FIN ACK 关闭连接 
* 补充:其实这里说的四次挥手,是说的一种通用机制,指的是双方的FIN ACK的接收情况,如果被动方刚好没有数据要发送,那么也可以直接FIN,ACK一起发送,那么就是3次交互了    

==*后期补充*==  
1. 为什么主动断开的一方要等待2MSL?  
1). TIME_WAIT状态产生  
由主动关闭socket的一方产生,主动关闭的一方自己的ACK接收到后(同时关闭)或者对端的ACK发送之后进入TIME_WAIT状态  
2). 假设客户端主动断开,等2MSL是为了等待在2MSL这段时间中可能出现的服务端FIN超时重传(服务器端最后一个ACK可能没有收到)或者自己端FIN超时重传(可能自己端的ACK没有收到:同时关闭的情况下)，如果服务端真的需要超时重传，那么一定会在这段时间里进行，反之，若过了这段时间还没有重传，则可以确认ACK被服务端收到了.
服务端一收到ACK,就会转换到CLOSED状态,客户端也可以放心的释放资源,此时网络中不会在存活本次的tcp数据包,对客户端下次重用这个端口不会在产生任何影响    
1. 2MSL由来     
去向ACK消息最大存活时间（MSL) + 来向FIN消息的最大存活时间(MSL),这恰恰就是2MSL( Maximum Segment Life),大约4分钟      
1. tcp状态转换图  
![tcp状态转换图](./picture/tcp状态转换图.png)   
#### 4.TCP连接中有出现异常的超时吗  
* 有的，Keepalive Timer,通过设置TCP socket的SO_KEEPALIVE option，主要适用于这种场景：连接的双方一般情况下没有数据要发送，仅仅就想尝试确认对方是否依然在线,但是默认的探测周期比较长,以Linux为例子,默认的是探测周期7200秒(也就是2小时),每个周期内探测9次      
追问:tcp闪断该如何处理    
* 首先声明一下tcp的闪断是很难检测到的,比如拔网线再插入等等,只能进可能采用适当的方案减少体验上的损失         
* 首先如何保证tcp连接是存活的，利用心跳包机制,规定多长时间内没有收到多少个心跳包算是出现异常    
* tcp闪断后处理  
1. 每创建一个连接，都会绑定一个类似session的会话，通过心跳包机制更新session会话状态  
2. 检测到tcp不可用后(闪断),保存该session存货时间5分钟(设置),客户端重连，如果5分钟没有重连上来，则销毁session  
#### 5.Epoll? Epoll和Select有什么区别?
* [select poll epoll总结](https://www.cnblogs.com/anker/p/3265058.html)
* select是跨平台的,多路复用I/O模型,默认的支持的文件描述符是1024个  
* epoll是linux多路复用I/O模型，支持的问件描述符数量比较大，默认是65536,可以配置    
* select是遍历所有的fd找到可读写事件，epoll是直接返回可读写的事件(最大区别)  
追问:Select文件描述符超过1024会如何
* select的fd超过1024将会非常危险------linux下是以fd的值作为数组的下标,一旦超过1024,将会导致未定义行为,甚至导致core dump,参考man select  
* 修改对应的宏，重新编译内核源码,但是效率会降低   
追问:Epoll底层是如何实现的?为什么要用红黑树结构？数据结构大概是什么样子的  
[epoll底层原理](https://www.cnblogs.com/lojunren/p/3856290.html)         
* 红黑树效率为logn(n为树的高度)   

==*后期补充*==
1. 什么是I/O多路复用？  
IO多路复用,又被称为事件驱动,IO多路复用是指内核一旦发现进程指定的一个或者多个IO可读写时，它就通知该进程进行处理.    
#### 6.Libevent有什么特点?你是用过程中有哪些坑呢?
1). 特点  
Libevent 是一个高性能，跨平台的C语言网络库，是基于Reactor模式的网络库,本质使用同步I/O模型，even_base循环->注册event事件->处理事件回调   
2). 坑:  
* Libevent处理用户read_cb的机制是边沿触发的机制(只有evbuffer的长度大于低水位才会触发用户的读回调)并且bufferevent_read()默认每次最大读取4096个字节,所以必须要判断底层数据有没有读完,没有读取完要一直读取    
* libevent发送大量数据也是要非常注意的  
* 如果给的ip不合法,调用befferconnect(),会先触发BEV_EVENT_ERROR回调,再触发BEV_EVENT_CONNECTED回调,所以要将这种情况区分开,所以需要额外的socket管理逻辑  
#### 7.你用过智能指针吗?有哪些?各自有什么特点?
* 参考网址:[C++ 智能指针](https://www.jianshu.com/p/e4919f1c3a28)
* 1. 为什么使用智能指针?   
1). 忘记delete   
2). 当出现异常返回的时候，即使写了delete，也有可能执行不到      
* 2. C++11为什么舍弃auto_ptr? 或者说auto_ptr有什么缺陷，与unique_ptr有什么区别?  
1). auto_ptr的缺陷: (1) auto_ptr相互赋值采用的是copy语义,可能带来指针double delete. (2) auto_ptr不能处理对象数组,默认析构行为是delete,不支持delete[]  
2). 与unique_ptr的区别: (1). auto_ptr相互赋值是copy语义,unique_ptr是move语义. (2). auto_ptr不支持delete[]操作,而unique_ptr支持    
* 3. auto_ptr unique_ptr share_ptr weak_ptr 各有什么特点  
1). auto_ptr: 满足基本需求,但是是copy语义,不能支持delete[]  
2). unique_ptr: move语义,独占资源, 支持自定义析构逻辑  
3). share_ptr: 引用计数实现,共享资源,支持自定义析构逻辑,但是可能会有循环引用的缺陷    
4). weak_ptr: 与share_ptr配合使用,能够避免share_ptr的循环引用缺点,弱引用计数,不能操作资源          
* 4. 指针相互赋值?  
1). share_ptr(auto_ptr) share_ptr(unique_ptr) share_ptr(share_ptr)  
2). share_ptr = weak_ptr.lock()  weak_ptr = share_ptr   
3). unique_ptr(auto_ptr)  
#### 9.mongo索引
* 参考网址:[B/B+Tree图示参考](https://www.cnblogs.com/nullzx/p/8729425.html)
* [MongoDB 索引](http://www.mongoing.com/archives/2797)
* 问:mongodb索引是采用哪个数据结构实现的?    
最准确的说法是MongoDB在V3.2之后索引采用B+Tree,因为使用了WiredTiger引擎,之前使用的是BTree  
[mongodb wiredtiger](https://docs.mongodb.com/manual/core/wiredtiger/)      
[wiredtiger doc](https://source.wiredtiger.com/3.0.0/tune_page_size_and_comp.html)      
补充:为什么采用B+Tree(为什么不用AVL,BTree or Hash table)  
* MongoDB注重单个文档的查询，范围查询也要支持  
1. 单个数据查询效率:AVL(O(logn)<B+Tree(O(logn))<BTree(O(1)<x<O(logn))<Hash table(O(1))
2. 范围查询:B+Tree>Btree>Hash table   
补充:其实就是B+树为什么适合作为外部存储设备的索引?  
1). B+树能降低树的高度和减少磁盘IO的次数   
2). B+树叶子节点是有双向链表的,更好的支持范围查询   
#### 8.Zookeeper是什么?    
* [zookeeper官网](https://zookeeper.apache.org/)    
* 请查看三游族网络面试  
追问:zookeeper分布式锁的原理
* 请查看三游族网络面试   
* zookeeper集群数量定义
* 请查看三游族网络面试   
#### 9.ActiveMq消息会丢失吗
* 如果消息没有持久化,消息可能会丢失的，消息可以持久化处理      
1. 生产者发送消息给MQ服务器，MQ服务器接收到消息后，MQ宕机消息会不会丢失?   
2. TOPIC的消息模式下，MQ接收到消息，这时候订阅者宕机了或者重启了，那消息会丢失，有什么解决方案？
* 第一个问题，ActiveMq支持消息的持久化，所以MQ服务器宕机了，重启后消息也不会丢失。
* 第二个问题，关于发布-订阅的消息模式，即TOPIC，生产者跟消费者之间的时间严格依赖性，JMS提供了解决方案，订阅模式分持久订阅者与非持久订阅者，这样声明成持久订阅者即使宕机了，消息在broker也就是MQ服务器的磁盘里面不会丢失，订阅者重启后仍然可以消费消息
#### 10.数据结构实现(二选一)
* [std::share_ptr<T> 简单原理编程实现](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/share_ptr.cpp)   
* hash table简单编程实现set or map
1. 参考网址:[hashMap 拉链法](https://blog.csdn.net/stpeace/article/details/81274233) 
2. 参考网址:[hashMap 开放地址法(线性探查法)](https://blog.csdn.net/qq_36221862/article/details/73488162)(比拉链法效率高)
3. 参考网址:[hashMap 开放地址法(二次探查法)](https://blog.csdn.net/xyzbaihaiping/article/details/51607770)
4. [基于Hash Table简单实现的HashMap(拉链法解决冲突)](https://github.com/wangdamingll/JobLearn/blob/master/prepare/datastruct/code/HashTable/HashMap1.hpp)
5. [基于Hash Table简单实现的HashMap(开放地址法解决冲突)](https://github.com/wangdamingll/JobLearn/blob/master/prepare/datastruct/code/HashTable/HashMap2.hpp)

## 九.蚂蚁金服电话面试  
#### 1.同步IO/异步IO?
* 参考网址:[block no-block 同步IO 异步IO](https://blog.csdn.net/historyasamirror/article/details/5778378?utm_source=blogxgwz0)
* 同步I/O:当事件来临时，需要用户自己进行系统调用将数据copy到用户进程:example:select poll epoll
* 异步I/O:当事件来临时，内核负责将数据copy到用户进程，同时发送信号告诉用户进程copy完毕，用户进程直接使用即可,example:asio  
#### 2.常用的非对称加密有哪些?非对称加密的数学原理?根据数学上什么难题设计的?
* 常用非对称加密算法:RSA [Elgamal](https://www.jianshu.com/p/cd36ae7dca47) [ECC(椭圆曲线加密算法)](https://juejin.im/post/5a67f3836fb9a01c9b661bd3)
* RSA:RSA算法的核心,在于大整数的质因数分解是一件非常困难的事情
* RSA算法参考网址:[RSA算法原理一](http://www.ruanyifeng.com/blog/2013/06/rsa_algorithm_part_one.html) [RSA 算法原理二](http://www.ruanyifeng.com/blog/2013/07/rsa_algorithm_part_two.html)
#### 3.静态局部变量和静态全局变量的有什么区别?生成顺序和释放顺序是什么
* 参考网址:[静态全局变量 静态局部变量](https://blog.csdn.net/lanzhihui_10086/article/details/39395059)  
* 生成顺序:静态全局变量:程序开始运行的时候(main函数调用之前)初始化 静态局部变量:程序运行到该代码段的时候首次初始化
* 释放顺序:先声明的后释放
#### 4.tcp三次握手和四次挥手过程？为什么是三次和四次(不是两次和五次)?
* 是为了在不可靠的信道上建立可靠的数据通道最少的交互方式,本质上是两端交换seqnumber  
* [TCP为什么设置三次握手,而不是二次或者四次](https://www.zhihu.com/question/24853633)  
追问:那Tcp为什么要四次挥手呢？3次不行吗?  
* 不行,因为tcp是全双工通讯,主动关闭的一方数据可能已经发送完了，但是被动关闭的一方数据可能还没有发送完，四次挥手能够保证被动方把数据发送完在通过FIN ACK 关闭连接.   
补充:其实这里说的四次挥手,是说的一种通用机制,指的是双方的FIN ACK的接收情况,如果被动方刚好没有数据要发送,那么也可以直接FIN,ACK一起发送,那么就是3次交互了   
#### 5.TCP的TIME_WAIT和CLOSE_WAIT的区别
* 参考网址:[TCP状态](https://blog.csdn.net/kobejayandy/article/details/17655739)
* TIME_WAIT:主动关闭的一方发送最后一个ACK(对端的)或者接收到自己的ACK(可能是同时关闭)之后进入该状态 
* CLOSE_WAIT:被动关闭的一方回应主动关闭一方ACK之后进入该状态
#### 6.2MSL的作用?服务器端出现了很多CLOST_WAIT的原因?TIME_WAIT如何处理？
* 参考网址:[TCP状态](https://blog.csdn.net/kobejayandy/article/details/17655739)  
* 2MSL作用:
1. 可靠的关闭TCP全双工连接。在主动关闭方发送的最后一个ACK(对端的),有可能丢失,这时被动方会重新发FIN,如果这时主动方处于CLOSED状态,就会响应RST而不是ACK,被动方就会认为发生错误,所以TCP必需要支持可靠的关闭两个方向的连接.所以主动方要处于TIME_WAIT状态,而不能是CLOSED   
2. 防止上一次连接中的包，迷路后重新出现，影响新连接（经过2MSL，上一次连接中所有的重复包都会消失）
* 服务端出现很多CLOSE_WAIT:被动方回应主动关闭的一方ACK之后，没有正确的进行close操作，会处于CLOST_WAIT状态   
* TIME_WAIT过多如何处理
* 参考网址:[TIME_WAIT处理](https://www.cnblogs.com/dadonggg/p/8778318.html)
1. 单台机器修改内核文件:/etc/sysctl.conf
2. 在1的基础上进行集群操作
#### 7.tcp如何保证数据安全有序?tcp拥塞控制?常用的拥塞控制算法有哪些?    
* [tcp拥塞控制及算法](https://zhuanlan.zhihu.com/p/37379780)    
1. 慢启动:cwnd=1,2,4,8,....(加法增大)             
2. 拥塞避免:cwnd>=ssthresh -> cwnd=ssthresh+1, ssthresh+2,..... -> 一旦拥塞,ssthresh=拥塞是发送窗口/2(乘法减小), cwnd = 1 -> 慢启动        
3. 快重传:发送方只要一连收到三个重复确认就应当立即重传对方尚未收到的报文段，而不必继续等待设置的重传计时器时间到期       
4. 快恢复:发生拥塞时,ssthresh=拥塞是发送窗口/2(乘法减小), cwnd = ssthresh -> 拥塞避免(现在tcp采用的版本)            
* [tcp如何保证数据安全有序](https://blog.csdn.net/jhh_move_on/article/details/45770087)  
如何保证安全?    
1. 建立可靠信道(三次握手 四次挥手)    
2. 数据进行合理分段(tcp分段)        
3. 数据安全校验(tcp首部校验 tcp数据校验)    
4. ack应答机制(数据包序列号)      
5. 丢包重传 超时重传机制   
6. 流量控制(滑动窗口机制)      
如何保证有序?  
1. tcp重复包丢弃 数据包排序等  
#### 8.tcp和udp的区别
* 参考网址:[TCP和UDP区别](https://zhuanlan.zhihu.com/p/24860273)
1. 基于连接(流模式)与无连接(数据报模式)    
2. TCP保证数据正确性和有序，UDP可能丢包和无序    
3. 对系统资源的要求(TCP较多，UDP少)    
4. TCP传输慢,UDP传输快    
#### 9.Epoll和Select的区别?
* [select poll epoll总结](https://www.cnblogs.com/anker/p/3265058.html)
* select是跨平台的,多路复用I/O模型,默认的支持的文件描述符是1024个  
* epoll是linux多路复用I/O模型，支持的问件描述符数量比较大，默认是65536,可以配置    
* select是遍历所有的fd找到可读写事件，epoll是直接返回可读写的事件(最大区别)      
#### 10.ActiveMQ的重复消费你是怎么处理的?你用的应答模式是什么?
* 参考网址:[关于MQ,你必须知道的](https://zhuanlan.zhihu.com/p/73987596)    
* 如何解决重复消费?
* ACK应答机制
```
AUTO_ACKNOWLEDGE = 1    自动确认
CLIENT_ACKNOWLEDGE = 2    客户端手动确认   
DUPS_OK_ACKNOWLEDGE = 3    自动批量确认
SESSION_TRANSACTED = 0    事务提交并确认
INDIVIDUAL_ACKNOWLEDGE = 4    单条消息确认 activemq 独有
```
1. 一条消息是否已经消费是通过ack确认机制来保证的,如果是通过异步回调的方式接收消息的话,在onMessage回调函数返回之后会立即进行ack确认提交，那么只要保证onMessage函数内部不抛出异常，及需要内部捕获异常，那么消息就不会被重复多次消费
2. (手动提交ACK，如果因为网络问题无法到达broker)可以考虑收到消息后会首先存入db中进行持久化，而且每条消息在存入数据库的时候都做了唯一性约束，那么即使有重复的消息也不会被正常处理     

==*后期补充*==  
1. 如何解决mq的高可用问题?    
mq自身采用集群,在配合zookeeper    
2. 如何解决消息的重复消费?
* 1. 重复消费的原因?  
大多由于网络原因,消费者消费了消息之后,传递ack给消息队列,但是消息队列并没有收到,会重新在发送消息给消费者,这就产生了重复消费的问题  
* 2. 如何解决?    
1)消费者端可以采用捕获异常然后收到ack消息的方式,减少风险   
2)可以消费者接收到消息之后立马存入数据库或者redis,每次收到消息查一下,判断有没有重复消费   
3. 如何解决消息丢失(可靠性传输)?  
* 1. 消息丢失的原因?   
1). 发送者端可能消息丢失:可以启用发送消息确认等机制     
2). mq可能丢失:开启消息持久化功能    
3). 消费者端可能丢失:启用消费者手动提交确认,保证不发生重复消费,可以避免这种情况   
1. 如何保证消息的传输和消费有序?   
某一业务按照某种算法放入到某个队列中,单个消息队列,单个消费者  
1. push和pull模式优缺点?   
push:将消息主动推送给消费者,消息实时度高,但是mq实现逻辑复杂,不适合大量消费者       
pull:由消费者主动拉取消息,消息实时度取决于轮询频率,mq实现较为简单,适合大量消费者           

#### 11.多态?  
* 请参考二.杭州字节跳动C++多态  
追问:基类指针是如何索引到子类的虚函数的?虚函表的结构是什么样子?  
* 基类指针->子类对象内存区域->vptr指针->虚函数表(函数指针数组)->根据子类重写的虚函数偏移地址(子类虚函数重写覆盖了父类的函数指针值)->调用子类虚函数
* 请参考二.杭州字节跳动C++多态   
#### 12.智能指针?  
* 参考网址:[C++ 智能指针](https://www.jianshu.com/p/e4919f1c3a28)
* 1. 为什么使用智能指针?   
1). 忘记delete   
2). 当出现异常返回的时候，即使写了delete，也有可能执行不到      
* 2. C++11为什么舍弃auto_ptr? 或者说auto_ptr有什么缺陷，与unique_ptr有什么区别?  
1). auto_ptr的缺陷: (1) auto_ptr相互赋值采用的是copy语义,可能带来指针double delete. (2) auto_ptr不能处理对象数组,默认析构行为是delete,不支持delete[]  
2). 与unique_ptr的区别: (1). auto_ptr相互赋值是copy语义,unique_ptr是move语义. (2). auto_ptr不支持delete[]操作,而unique_ptr支持    
* 3. auto_ptr unique_ptr share_ptr weak_ptr 各有什么特点  
1). auto_ptr: 满足基本需求,但是是copy语义,不能支持delete[]  
2). unique_ptr: move语义,独占资源, 支持自定义析构逻辑  
3). share_ptr: 引用计数实现,共享资源,支持自定义析构逻辑,但是可能会有循环引用的缺陷    
4). weak_ptr: 与share_ptr配合使用,能够避免share_ptr的循环引用缺点,弱引用计数,不能操作资源          
* 4. 指针相互赋值?  
1). share_ptr(auto_ptr) share_ptr(unique_ptr) share_ptr(share_ptr)  
2). share_ptr = weak_ptr.lock()  weak_ptr = share_ptr   
3). unique_ptr(auto_ptr)  
#### 13.并发编程?
* 需要学习C++并发编程  
#### 14.常用的Boost库，你用过哪些？
* Boost::Asio:异步IO网络库  
* Boost::Filesystem:文件系统
* Boost::Property Tree:解析配置文件 

---
