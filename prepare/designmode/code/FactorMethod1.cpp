#include <iostream>
using namespace std;

//客户端使用Creator对象

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
    //一些操作
    void Operator()
    {
        Product* p = this->FactoryMethod();
        if(p != nullptr)
        {
            p->Operation();
            delete p;
        }
    }

    virtual ~Creator(){}

protected:
    //工厂方法
    virtual Product* FactoryMethod() = 0;
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
    Creator* cA = new ConcreteCreatorA();
    if(cA != nullptr)
    {
        cA->Operator();
        delete cA;
    }

    Creator* cB = new ConcreteCreatorB();
    if(cB != nullptr)
    {
        cB->Operator(); // ConcreteProductB
        delete cB;
    }
    return 0;
}