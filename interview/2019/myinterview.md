# 面试
---
## 一.爱奇艺
### 爱奇艺面试第一轮
#### 1.你了解哪些设计模式
单例模式工厂模式  
追问：单例模式、简单工厂模式、工厂模式有什么特点？  
```C++
//单例模式懒汉式
#include <iostream>
#include <mutex>
using namespace std;
std::mutex mt;
class Singleton{
private:
    Singleton(){}
public:
    static Singleton* instance(){
        if(_instance == 0){
            mt.lock();
            if(_instance == 0)
                _instance = new Singleton();
            mt.unlock();
        }
        return _instance;
    }
private:
    static Singleton* _instance;
};
Singleton* Singleton::_instance = 0;
```
```C++
//单例模式饿汉式
#include <iostream>
#include <mutex>
using namespace std;
std::mutex mt;
class Singleton{
private:
    Singleton(){}
public:
    static Singleton* instance(){
        if(_instance == 0){
            return _instance;
        }
        return _instance;
    }
private:
    static Singleton* _instance;
};
Singleton* Singleton::_instance = new Singleton();
```
```C++
//单例模式C++11
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
std::once_flag flag;
class Singleton
{
public:
    static Singleton& getInstance(){
        std::call_once(flag, []() {instance_.reset(new Singleton()); });
        return *instance_;
    }

private:
    static std::unique_ptr<Singleton> instance_;

private:
    Singleton() = default;
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

std::unique_ptr<Singleton> Singleton::instance_;

void do_onceflag(){
    Singleton& s = Singleton::getInstance();
    cout << &s << endl;
}

int main(){
    std::thread t1(do_onceflag);
    std::thread t2(do_onceflag);
    t1.join();
    t2.join();
    return 0;
}
```
```C++
//简单工厂模式基本代码
#include <iostream>
using namespace std;

class AbstractProduct {
public:
    virtual ~AbstractProduct() {}
    virtual void Operation() = 0;
};

class ProductA : public AbstractProduct {
public:
    void Operation() { cout << "ProductA" << endl; }
};

class ProductB : public AbstractProduct {
public:
    void Operation() { cout << "ProductB" << endl; }
};

class Factory {
public:
    AbstractProduct* createProduct(char product) {
        AbstractProduct* ap = NULL;
        switch(product) {
            case 'A': ap = new ProductA(); break;
            case 'B': ap = new ProductB(); break;
        }
        return ap;
    }
};

int main() {
    Factory* f = new Factory();
    AbstractProduct* apa = f->createProduct('A');
    apa->Operation();  // ProductA

    AbstractProduct* apb = f->createProduct('B');
    apb->Operation();  // ProductB

    delete apa;
    delete apb;
    delete f;

    return 0;
}
```
```C++
//工厂模式基本代码
#include <iostream>
using namespace std;

class Product {
public:
    virtual ~Product(){}
    virtual void Operation() = 0;
};

class ConcreteProductA : public Product {
public:
    void Operation() { cout << "ConcreteProductA" << endl; }
};

class ConcreteProductB : public Product {
public:
    void Operation() { cout << "ConcreteProductB" << endl; }
};

class Creator{
public:
    virtual Product* FactoryMethod() = 0;
    virtual ~Creator(){}
};

class ConcreteCreatorA : public Creator {
public:
    Product* FactoryMethod() { return new ConcreteProductA(); }
};

class ConcreteCreatorB : public Creator {
public:
    Product* FactoryMethod() { return new ConcreteProductB(); }
};

int main() {
    Creator* ca = new ConcreteCreatorA();
    Product* pa = ca->FactoryMethod();
    pa->Operation(); // ConcreteProductA

    Creator* cb = new ConcreteCreatorB();
    Product* pb = cb->FactoryMethod();
    pb->Operation(); // ConcreteProductB

    delete ca;
    delete pa;
    delete cb;
    delete pb;

    return 0;
}

```
```C++
//抽象工厂基本代码
#include <iostream>
using namespace std;

class AbstractProductA {
public:
    virtual ~AbstractProductA(){}
    virtual void Operation() = 0;
};

class ProductA1 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA1" << endl;
    }
};

class ProductA2 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA2" << endl;
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB(){}
    virtual void Operation() = 0;
};

class ProductB1 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB1" << endl;
    }
};

class ProductB2 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB2" << endl;
    }
};


class AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;
    virtual ~AbstractFactory(){}
};

class ConcreteFactory1 : public AbstractFactory {
public:
    ProductA1* CreateProductA() {
        return new ProductA1();
    }
    ProductB1* CreateProductB() {
        return new ProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    ProductA2* CreateProductA() {
        return new ProductA2();
    }
    ProductB2* CreateProductB() {
        return new ProductB2();
    }
};

int main() {
    AbstractFactory* af1 = new ConcreteFactory1();
    // 具体工厂创建对应的具体产品
    AbstractProductA* apa1 = af1->CreateProductA();  // 工厂1创建产品A
    apa1->Operation();  // ProductA1

    AbstractProductB* apb1 = af1->CreateProductB();  // 工厂1创建产品B
    apb1->Operation();  // ProductB1

    AbstractFactory* af2 = new ConcreteFactory2();
    AbstractProductA* apa2 = af2->CreateProductA();  // 工厂2创建产品A
    apa2->Operation();  // ProductA2

    AbstractProductB* apb2 = af2->CreateProductB();  // 工厂2创建产品B
    apb2->Operation();  // ProductB2

    delete apa1;
    delete apa2;
    delete af1;
    delete apb1;
    delete apb2;
    delete af2;
    return 0;
}
```

#### 2.多态的虚函数表放在哪里？属于类还是对象
全局静态存储区，属于类

#### 3.线程间同步和互斥  
互斥是对共享资源进行加锁，具有排他性。同步是在互斥的基础上，通过其他机制实现访问者对共享资源的访问  
追问:哪些机制？  
比如说互斥锁、信号量、条件变量等  

#### 4.类与类之间的关系
* 组合:见下面
* 聚合:见下面
* 关联:包含其他类指针成员变量
* 依赖:一个类作为另外一个类方法参数的方式
* 继承:一个类继承另外一个类
* 实现:C++只不过面向接口的方式，通过纯虚函数实现
追问:组合和聚合之间有什么关系
* 聚合:整体和部分之间的关系，has-a pointer 一个类含有另外一个类的指针
* 组合:比聚合关系更强，也是整体和部分之间的关系，具有相同的生命周期，has-a，一个类包含另外一个类

#### 5.你项目中的日志是如何实现输出到同一个文件中的
通过生产消费者模型的方式

#### 6.给定一个数组，查找其中最大2个元数之前的差值
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
1. 插入、搜索时间复杂度:O(logN)  
追问:你说map是有序的，那它通过什么规则实现的？
对存入的元素重载了operator< 操作符
#### 2.map和unordered_map的区别
1. map底层是红黑树实现的，unordered_map底层是哈希表(散列表)实现的
2. map的有序的，unirdered_map是无序的
3. map插入、查询稳定O(logN),unordered_map查询效率O(1),但是有可能退化为O(N)
4. map消耗的内存低，unordered_map消耗的内存高
5. 要求有序且对内存占用敏感，用map;要求查询效率，对内存占用不敏感，用unordered_map
#### 3.构造函数和析构函数执行顺序(继承体系下)
***构造函数和析构函数中的虚函数会去虚拟化，将会总是被静态地当做本类型的函数解析***
1. 构造函数执行顺序是从上而下
2. 析构函数执行顺序是从下而上
追问:析构函数为什么是虚函数  
当delete基类指针指向派生类对象的时候，应该先调用派生类析构函数，在调用基类析构函数，不是虚函数的话，只会调用基类析构函数，这样就产生了内存泄漏
#### 4.C++是如何实现多态的
1. 多态的产生条件  
* 有继承关系
* 有虚函数重写
* 父类指针(引用)指向之类对象
2. 多态实现原理  
```C++
//基类
class base{
public:
    base(long m1 = 1, long m2 = 2):m1(m1),m2(m2){};
    virtual void virtualbase1() {
        std::cout<<"this is the base1 vitual funciton"<<endl;
    }
    virtual void virtualbase2() {
        std::cout<<"this is the base2 vitual funciton"<<endl;
    }
    virtual void virtualbase4() {
        std::cout<<"this is the base3 vitual funciton"<<endl;
    }
private:
    long m1;
    long m2;
};
//派生类
class base1 : public base{
    void virtualbase2() {
        std::cout<<"this is the base from subclass virtual function"<<endl;
    }
};
```
bAddress: 0x7ffeeb90f9f0  
     vtptr:0x1042f7528    
     vfunc1:0x1042f3a50  
     vfunc2:0x1042f3a90  
     vfunc3:0x1042f3ad0  
b1Address: 0x7ffeeb90f998  
     b1vtptr: 0x1042f7560  
     b1pfunc1: 0x1042f3a50  
     b1pfunc2: 0x1042f3b60  
     b1pfunc3: 0x1042f3ad0  
通过结果可以看出，当派生类重新定义了基类的函数后其虚函数表中的指针发生了覆盖，而没有重新定义的地方则维持了基类虚函数的地址

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
* 虚继承的影响  gcc 64位
```C++
class A {
    int a;
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
```
解释：A的大小为int大小加上虚表指针大小。B，C中由于是虚继承因此大小为int大小加指向虚基类的指针的大小。B,C虽然加入了自己的虚函数，但是虚表指针是和基类共享的，因此不会有自己的虚表指针，他们两个共用虚基类A的虚表指针。D由于B,C都是虚继承，因此D只包含一个A的副本，于是D大小就等于int变量的大小+B中的指向虚基类的指针+C中的指向虚基类的指针+一个虚表指针的大小,由于字节对齐，结果为8+8+8+8=32  

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
2. 户端获取/lock下的子节点列表，判断自己创建的子节点是否为当前子节点列表中序号最小的子节点，如果是则认为获得锁，否则监听/lock的子节点变更消息，获得子节点变更通知后重复此步骤直至获得锁；
3. 执行业务代码；
4. 完成业务流程后，删除对应的子节点释放锁。
* 集群中有 3 台服务器，其中一个节点宕机，这个时候 zookeeper 还可以使用吗？
可以继续使用，单数服务器只要没超过一半的服务器宕机就可以继续使用(过半机制)
* zookeeper脑裂
假死：由于心跳超时（网络原因导致的）认为leader死了，但其实leader还存活着。
脑裂：由于假死会发起新的leader选举，选举出一个新的leader，但旧的leader网络又通了，导致出现了两个leader ，有的客户端连接到老的leader，而有的客户端则连接到新的leader
总结:集群中的节点监听不到leader节点的心跳, 就会认为leader节点出了问题, 此时集群将分裂为不同的小集群, 这些小集群会各自选举出自己的leader节点, 导致原有的集群中出现多个leader节点.
* zookeeper集群数量配置原则
  可用节点数量 > 集群总结点数量/2 可保证正常选举leader，集群正常运行  
#### 2.网络编程中ET/LT特点  
* ET,边沿触发模式，事件只触发一次; LT,水平触发模式，只要满足事件触发条件，会一直触发
追问:哪种效率更高
* 边沿触发效率更高些.ET模式，只要epoll_wait函数检测到事件发生，通知应用程序立即进行处理，后续的epoll_wait函数将不再检测此事件。因此ET模式在很大程度上降低了同一个事件被epoll触发的次数，因此效率比LT模式高
#### 3.libevent特点
* Libevent 是一个高性能，跨平台的C语言网络库，是基于Reactor模式的网络库，even_base循环->注册event事件->处理事件回调  
#### 3.线程间通讯方式
1. 一个进程间2个线程间通讯
* 全局变量
* 通过堆内存共享资源的方式
2. 不同进程间线程间通讯(进程间通讯)
* 管道:使用最简单 pip()创建管道读写端
* 信号:开销最小 signal(int sigal,handler)
* 共享映射区
1)通过文件描述符进行进程间通信:fork()后，父子进程共享打开的文件描述符
2)存储映射I/O:mmap()创建映射区
* 本地套接字:最稳定,创建本地套接字完成通信
#### 4.多态如何实现的
1. 多态的产生条件  
* 有继承关系
* 有虚函数重写
* 父类指针(引用)指向之类对象
2. 多态实现原理  
虚函数表是一个函数指针数组，属于类，当派生类发生虚函数重写时，对应的虚函数在虚函数表中的指针发生了覆盖，而没有重新定义的地方则维持了基类虚函数的地址
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
1. 插入、搜索时间复杂度:O(logN)  
#### 2.谈谈vector
* vector是一种容器，底层是由动态数组实现的
* vector支持随机访问，查找效率O(1),尾部出入删除O(1),头部插入删除O(N)  
追问:vector扩容机制
STL采用2倍扩容机制
* 采用成倍扩容方式可以保证push_back常数时间的复杂度
* 扩容因子不能太大，否则会造成堆内存浪费，普遍扩容因子采用2或者1.5
1)以2倍的方式扩容，导致下一次申请的内存必然大于之前分配内存的总和，导致之前分配的内存不能再被使用,对缓存不是很友好
2)1.5倍的增长方式可以更好的实现对内存的重复利用
3)C++标准中并没有规定使用哪个扩容因子
* 参考地址:[C++ STL vector扩容机制](https://www.zhihu.com/question/36538542/answer/67929747)
#### 3.libuv主要有哪些接口
uv_default_lopp() uv_tcp_init() uv_tcp_bind() uv_listen() uv_run() uv_accept() uv_read_start() 等等
#### 4.如果让你设计一个游戏背包，你会如何设计数据结构
```C++
vector<GoodBaseClass*>
Weapon:public GoodBaseClass  HpClass:public GoodBaseClase
```

## 五.紫龙游戏
### 紫龙游戏一面
#### 1.线程同步和互斥
互斥是对共享资源进行加锁，具有排他性。同步是在互斥的基础上，通过其他机制实现访问者对共享资源的访问  
追问:哪些机制？  
比如说互斥锁、信号量、条件变量等  
#### 2.介绍map
* map存储key-value数据
* 有序(对存入的元素重载了operator<操作符),
* 插入、搜索时间复杂度:O(logN)
* map底层是由红黑树实现的
* 红黑树的特点
1. 它一种特殊的二叉查找树
2. 每个节点是红色的或者是黑色的
3. 根节点和叶子节点都是黑色的
4. 如果一个节点是红色的，那个它的子节点就是黑色的
5. 一个节点到它子孙节点具有相同数目的黑色节点  
#### 3.unordered_map
* 关联容器,无序,含有带唯一键的键-值pair
* 搜索、插入和元素移除拥有平均O(1)复杂度,有可能退化成O(N),
* 底层是用hash_table实现的
* 如果key是自定义对象
1. 提供哈希函数
2. 重载等号操作符
#### 4.map和unordered_map的区别
1. map底层是红黑树实现的，unordered_map底层是哈希表(散列表)实现的
2. map的有序的，unirdered_map是无序的
3. map插入、查询稳定O(logN),unordered_map查询效率O(1),但是有可能退化为O(N)
4. map消耗的内存低，unordered_map消耗的内存高
5. 要求有序且对内存占用敏感，用map;要求查询效率，对内存占用不敏感，用unordered_map
#### 5.hash_table冲突解决方法
* 开放地址法
1. 线性探查法:index index+1 index+2 ... 表首在进行
2. 平方探查法:index index+1^2 index+2^2 ...
* 拉链法:链表的数组
* 在哈希:hashcode1() hashcode2() ... 知道不在冲突
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
虚继承是解决C++多重继承问题的一种手段,从不同途径继承来的同一基类，会在子类中存在多份拷贝。这将存在两个问题：其一，浪费存储空间；第二，存在二义性问题
* 实现原理
vbptr指的是虚基类表指针(virtual base table pointer),该指针指向了一个虚基类表(virtual table)虚表中记录了虚基类与本类的偏移地址,通过偏移地址，这样就找到了虚基类成员,而虚继承也不用像普通多继承那样维持着公共基类(虚基类)的两份同样的拷贝，节省了存储空间
* 参考网址:[C++ 虚拟继承实现内存布局](https://blog.csdn.net/xiejingfa/article/details/48028491)
#### 11.寻路算法
* 稍后学习 [寻路算法](https://www.jianshu.com/p/74ca39e670ba)
#### 12.链表部分翻转
题目:1->2->...->m...->n->...,将m->...->n部分翻转
* 稍后统一做
### 紫龙游戏二面(CTO面试)
#### 1.静态局部变量的作用有哪些
* [C++ static关键字总结](https://zhuanlan.zhihu.com/p/37439983)
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
#### 3.树的广度优先遍历
* 利用队列先进先出的特性，现将根节点放入->队列不为空->弹出节点->访问数据->放入左孩子节点->放入右孩子节点->队列不为空->.......
* 代码稍后统一写

## 六.鼹鼠网络
#### 1.epoll相关
* 无
#### 2.将一个有序数组打乱算法
* [Fisher–Yates shuffle (洗牌算法)](https://en.wikipedia.org/wiki/Fisher–Yates_shuffle)
* [C++ 随机数](https://blog.csdn.net/luotuo44/article/details/33690179)
```c++
int main(){
    auto f = [](int* array,int size,std::default_random_engine& random){
        while (size) {
            std::uniform_int_distribution<int> dis(0,--size);
            int i = dis(random);
            int t = array[size];
            array[size] = array[i];
            array[i] = t;
        }
    };
    int arr[] = {1,2,3};
    std::default_random_engine random(time(nullptr));
    f(arr, sizeof(arr)/ sizeof(int),random);
    return 0;
}
```

## 七.京东(上海)面试
### 电话面试
#### 1.Http Websocket Tcp三者之前的区别
* [http1.0 1.1 2.0](https://juejin.im/entry/5981c5df518825359a2b9476)
* http1.0 http1.1 http2.0的区别
HTTP/1.* 一次请求-响应，建立一个连接，用完关闭；每一个请求都要建立一个连接。
HTTP/1.1 默认支持长连接和请求的流水线（Pipelining）处理,建立一次连接，可以多个request共用。  
注:Pipeling解决方式为，若干个请求排队串行化单线程处理，后面的请求等待前面请求的返回才能获得执行机会，一旦有某请求超时等，后续请求只能被阻塞，毫无办法，也就是人们常说的线头阻塞。
HTTP/2 支持多路复用。多个请求可同时在一个连接上并行执行。某个请求任务耗时严重，不会影响到其它连接的正常执行。
* http和websocket区别和联系  
相同点:  
1. 都是基于tcp的应用层协议
2. 都使用Request/Response模型进行连接的建立  
不同点:
1. WS连接建立之后,支持双向通信,而http需要客户端主动发起request请求，服务器response回复
* tcp和websocket的区别和联系
联系:  
1. websocket是基于tcp的应用层协议
2. 一旦websocket握手连接之后,采用tcp方式进行通信  
区别:tcp是传输层协议,websocket是应用层协议  
追问:有Http了,为什么还要用Websocket  
* 最主要的是由客户端主动轮询变为服务端推送，降低了轮询消耗,避免了request/response这种请求回应模式，且ws支持双向通信,更加灵活
### 二轮面试
#### 1.Libevent用过吗?有哪些坑?是采用什么模式?具体定义了哪些宏?  
1. 坑:
* Libevent默认底层是采用LT模式的，但是bufferevent_read()默认每次最大读取4096个字节,所以必须要判断底层数据有没有读完
* 如果给的ip不合法,调用befferconnect(),会先触发BEV_EVENT_ERROR,再触发BEV_EVENT_CONNECTED,所以要将这种情况区分开
2. 默认采取了LT模式  
追问:LT/ET有什么区别?哪种效率更高?
* LT:水平触发，如果事件满足条件，会一直触发
* ET:边沿触发，如果事件满足条件，只会触发一次
* 相比较来说，ET的效率会高一些  
追问:为什么ET的效率会高一些
* ET满足条件的事件只会触发一次.所以操作系统在LT模式下维护的就绪队列大小相对于ET模式肯定大，且LT轮询所有的fd总比ET轮询的fd大。自然在性能上LT不如ET
3. 相关宏  
* BEV_EVENT_CONNECTED BEV_EVENT_ERROR BEV_EVENT_EOF BEV_EVENT_READING BEV_EVENT_WRITING (Epoll中有 EPOLLERROR EPOLLIN EPOLLOUT)  
#### 2.Libevent timer有用过吗
* 使用过  
追问:如何使用的?  
* 创建一个event_timer事件，设置好时间间隔和回调，加入到loop中，在回调函数中处理逻辑发送网络包逻辑
补充:libevnet采用时间堆(最小堆)实现，最小堆是什么数据结构?  
* 基于时间堆的时间复杂度:插入O(logn)、删除O(1)、查找O(1),参考:[时间堆(最小堆) 定时器](https://blog.csdn.net/liushall/article/details/81331591)
* 基于时间轮的时间复杂度:插入O(1)、删除O(1)、查找O(1),参考:[时间轮 定时器](https://www.cnblogs.com/zhongwencool/p/timing_wheel.html)
* 基于升序链表的时间复杂度:插入O(n)、删除O(1)、查找O(1),参考上面网址
#### 3.Libevnet发送大量数据时,怎么办？
* 参考网址:[Libevent bufferevent工作流程](https://blog.csdn.net/luotuo44/article/details/39344743)
* 代码级别优化:send()->bufferevent_write()->write_cb->处理剩下的发送逻辑(?)  
* 系统级别优化:bufferevent_write()->res==-1,出现失败(考虑要不要缓存)->调整系统so_send_buff/so_recive_buff的大小->保证滑动窗口的大小>=带宽*延迟
#### 4.Libevent VS Libuv
* [Libevent和Libuv的对比](https://blog.csdn.net/lijinqi1987/article/details/71214974)
#### 5.你用过哪些设计模式?  
* 查看爱奇艺面试  
追问:单例如何写呢?  
* 查看爱奇艺面试 
#### 6.内存池有用过吗?实现原理是什么
* 参考网址:[C++ placement new 简单内存池使用](https://www.jianshu.com/p/b52a5df69c88)
* 参考网址:[SGI-STL内存池实现原理](https://blog.csdn.net/u012611878/article/details/79187348)
#### 7.智能指针有用过吗?有哪几种类型 区别是什么  
* 稍等  
#### 8.你遇到过内存泄漏吗?如何检测的
* 稍等  
#### 9.你读过其他开源项目吗?
* 稍等

## 八.美团点评
### 第一轮
#### 1.设计模式
* 单例
* 工厂
#### 2.你常用的加密算法是什么
* AES
* RSA  
追问:RSA你们是如何使用的
* 稍等
#### 3.TCP为什么是三次握手,为什么不是两次或者是四次呢
* 稍等
追问:如果中途有一次ACK没有收到，会发生什么
* 稍等
#### 4.TCP有超时吗  
* 稍等  
追问:tcp闪断该如何处理  
* 稍等  
#### 5.Epoll? Epoll和Select有什么区别?
* 稍等  
追问:Select文件描述符超过1024会如何
* 稍等  
追问:Epoll底层是如何实现的?为什么要用红黑树结构？数据结构大概是什么样子的
* 稍等  
#### 6.Libevent有什么特点?你是用过程中有哪些坑呢?
* 稍等   
坑:  
1. 底层默认是水平触发的,但是bufferevent_read()类似于边沿触发,每次最多读取4096个字节  
2. 当传入的IP有问题时,bufferevent_connect()遇到的问题,先ERROR,后触发CONNECTED  
#### 7.你用过智能指针吗?有哪些?各自有什么特点?
* 稍等  
#### 9.mongo索引
* 稍等  
#### 8.Zookeeper是什么?
* 稍等  
追问:zookeeper分布式锁的原理
* 稍等  
* zookeeper集群数量定义
* 稍等  
#### 9.ActiveMq消息会丢失吗
* 稍等  
#### 10.数据结构s实现(二选一)
* hash表简单编程实现
* std::share_ptr<T> 简单编程实现

## 九.蚂蚁金服电话面试  
#### 1.同步IO/异步IO?
* 稍等  
#### 2.常用的非对称加密有哪些?非对称加密的数学原理?根据数学上什么难题设计的?
* 稍等  
#### 3.静态局部变量和静态全局变量的有什么区别?生成顺序和释放顺序是什么
* 稍等  
#### 4.tcp三次握手和四次挥手过程？为什么是三次和四次(不是两次和五次)?
* 稍等  
#### 5.tcp的time_wait和close_wait的区别
* 稍等  
#### 6.2MSL的作用?服务器端出现了很多close_wait的原因?time_wait如何处理？
* 稍等  
#### 7.tcp拥塞控制?tcp如何保证数据安全有序?常用的拥塞控制算法有哪些?
* 稍等  
#### 8.tcp和udp的区别
* 稍等  
#### 9.Epoll和Select的区别?
* 稍等  
#### 10.ActiveMQ的重复消费你是怎么处理的?你用的应答模式是什么?
* 稍等  
#### 11.多态?  
* 稍等  
追问:基类指针是如何索引到子类的虚函数的?虚函表的结构是什么样子?  
* 稍等  
#### 12.智能指针?  
* 稍等  
#### 13.并发编程?
* 稍等  
#### 14.常用的Boost库，你用过哪些？
* 稍等

---
