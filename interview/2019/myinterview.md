# 面试
---

## 爱奇艺面试
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

## 杭州字节跳动面试
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
1. 搜索时间复杂度:O(logN)  
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
2. 多态实现

---
