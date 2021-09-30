#include <iostream>
using namespace std;

//抽象产品
class AbstractProduct {
public:
    virtual ~AbstractProduct() {}
    virtual void Operation() = 0;
};

//具体产品A
class ProductA : public AbstractProduct {
public:
    void Operation() { cout << "ProductA" << endl; }
};

//具体产品B
class ProductB : public AbstractProduct {
public:
    void Operation() { cout << "ProductB" << endl; }
};

//简单工厂
class Factory {
public:
    static AbstractProduct* CreateProduct(char product) {
        AbstractProduct* ap = nullptr;
        switch(product)
        {
            case 'A':
            {
                ap = new ProductA();
                break;
            }
            case 'B':
            {
                ap = new ProductB();
                break;
            }
            default:
                break;
        }
        return ap;
    }
};

int main() {
    AbstractProduct* aPa = Factory::CreateProduct('A');
    if(aPa != nullptr)
    {
        aPa->Operation();  // ProductA
        delete aPa;
    }

    AbstractProduct* aPb = Factory::CreateProduct('B');
    if(aPb != nullptr)
    {
        aPb->Operation();  // ProductB
        delete aPb;
    }
    
    return 0;
}