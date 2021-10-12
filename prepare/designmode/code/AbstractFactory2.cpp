//参数化抽象工厂代码
//这里用于扩展产品系列, 比如之前已经有了产品A和B,现在要在增加一个产品C
#include <iostream>
using namespace std;

//抽象产品
class AbstractProduct {
public:
    virtual ~AbstractProduct(){}
    virtual void Operation() = 0;
};

//抽象产品A
class AbstractProductA : public AbstractProduct  {
public:
    virtual ~AbstractProductA(){}
    virtual void Operation() = 0;
};

//具体产品A1
class ProductA1 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA1" << endl;
    }
};

//具体产品A2
class ProductA2 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA2" << endl;
    }
};

//抽象产品B
class AbstractProductB : public AbstractProduct {
public:
    virtual ~AbstractProductB(){}
    virtual void Operation() = 0;
};

//具体产品B1
class ProductB1 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB1" << endl;
    }
};

//具体产品B2
class ProductB2 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB2" << endl;
    }
};

//新增抽象产品C
class AbstractProductC : public AbstractProduct{
public:
    virtual ~AbstractProductC(){}
    virtual void Operation() = 0;
};

//新增具体产品C1
class ProductC1 : public AbstractProductC {
public:
    void Operation() {
        cout << "ProductC1" << endl;
    }
};

//抽象工厂
class AbstractFactory {
public:
    virtual AbstractProduct* CreateProduct(int type) = 0;
    virtual ~AbstractFactory(){}
};

//具体工厂1:生产产品A1和B1
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProduct * CreateProduct(int type) {
        if(type == 1) //创建A
        {
            return new ProductA1();
        }else if(type == 2) //创建B
        {
            return new ProductB1();
        }
        return nullptr;
    }
};

//具体工厂2:生产产品A2和B2
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProduct * CreateProduct(int type) {
        if(type == 1) //创建A
        {
            return new ProductA2();
        }else if(type == 2) //创建B
        {
            return new ProductB2();
        }
        return nullptr;
    }
};

//新增具体工厂3:生产产品A1和B1 和新增生产C1
class ConcreteFactory3 : public AbstractFactory {
public:
    AbstractProduct * CreateProduct(int type) {
        if(type == 1) //创建A
        {
            return new ProductA2();
        }else if(type == 2) //创建B
        {
            return new ProductB2();
        }else if(type == 3) //创建C
        {
            return new ProductC1();
        }
        return nullptr;
    }
};

int main() {
    //示例代码就不判空了 和 释放 资源了
    AbstractFactory* af1 = new ConcreteFactory1();
    // 具体工厂创建对应的具体产品
    AbstractProduct* apa1 = af1->CreateProduct(1);  // 工厂1创建产品A
    AbstractProduct* apb1 = af1->CreateProduct(2);  // 工厂1创建产品B
    AbstractProduct* apc1 = af1->CreateProduct(3);  // 工厂1创建产品C
    apa1->Operation();  // ProductA1
    apb1->Operation();  // ProductB1
    if(apc1)
    {
        apc1->Operation();
    }

    AbstractFactory* af2 = new ConcreteFactory2();
    AbstractProduct* apa2 = af2->CreateProduct(1);  // 工厂2创建产品A
    AbstractProduct* apb2 = af2->CreateProduct(2);  // 工厂2创建产品B
    AbstractProduct* apc2 = af2->CreateProduct(3);  // 工厂2创建产品C
    apa2->Operation();  // ProductA2
    apb2->Operation();  // ProductB2
    if(apc2)
    {
        apc2->Operation();
    }

    AbstractFactory* af3 = new ConcreteFactory3();
    AbstractProduct* apa3 = af3->CreateProduct(1);  // 工厂3创建产品A
    AbstractProduct* apb3 = af3->CreateProduct(2);  // 工厂3创建产品B
    AbstractProduct* apc3 = af3->CreateProduct(3);  // 工厂3创建产品C
    apa3->Operation();  // ProductA2
    apb3->Operation();  // ProductB2
    if(apc3)
    {
        apc3->Operation();
    }

    return 0;
}