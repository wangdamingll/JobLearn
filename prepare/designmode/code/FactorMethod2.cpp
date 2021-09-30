#include <iostream>
using namespace std;

//客户端使用Creator创建出来的对象

//抽象产品
class Product {
public:
    virtual ~Product(){}
    virtual void Operation() = 0;
};

//具体产品A
class ConcreteProductA : public Product {
public:
    void Operation() override { cout << "ConcreteProductA" << endl; }
};

//具体产品B
class ConcreteProductB : public Product {
public:
    void Operation() override { cout << "ConcreteProductB" << endl; }
};

//抽象工厂
class Creator{
public:
    virtual Product* FactoryMethod() = 0;
    virtual ~Creator(){}
};

class ConcreteCreatorA : public Creator {
protected:
    Product* FactoryMethod() override { return new ConcreteProductA(); }
};

class ConcreteCreatorB : public Creator {
protected:
    Product* FactoryMethod() override { return new ConcreteProductB(); }
};

int main() {
    //示例程序不判空了
    Creator* cA = new ConcreteCreatorA();
    Product* pA = cA->FactoryMethod();
    pA->Operation();
    delete cA;
    delete pA;

    Creator* cB = new ConcreteCreatorB();
    Product* pB = cB->FactoryMethod();
    pB->Operation();
    delete cB;
    delete pB;
    return 0;
}