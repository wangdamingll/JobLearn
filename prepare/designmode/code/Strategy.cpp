#include <iostream>
#include <string>
#include <memory>

using namespace std;

//高层策略接口
class Strategy
{
public:
    virtual double CalcPrice(double  goodsPrice){return 0;}
};

//具体策略
//普通客户策略
class NormalCustomerStrategy : public Strategy
{
public:
    double CalcPrice(double  goodsPrice) override
    {
        //普通客户没有折扣
        std::cout<<"普通客户没有折扣"<<std::endl;
        return goodsPrice;
    }
};

//老客户策略
class OldCustomerStrategy : public Strategy
{
public:
    double CalcPrice(double  goodsPrice) override
    {
        //老客户 统一折扣5%
        std::cout<<"老客户折扣5%"<<std::endl;
        return goodsPrice * (1 - 0.05);
    }
};

//大客户策略
class LargeCustomerStrategy : public Strategy
{
    double CalcPrice(double  goodsPrice) override
    {
        //大客户 统一折扣10%
        std::cout<<"大客户折扣10%"<<std::endl;
        return goodsPrice * (1 - 0.1);
    }
};


//策略上下文
class Price
{
public:
    Price(Strategy* strategy) : pStrategy(strategy){}
    double Quote(double goodsPrice)
    {
        if(pStrategy != nullptr)
        {
            return pStrategy->CalcPrice(goodsPrice);
        }
        return 0;
    }
private:
    std::unique_ptr<Strategy> pStrategy {nullptr};
};
int main()
{
    {
        Price price(new NormalCustomerStrategy);
        double goodsPrice = price.Quote(100);
        std::cout<<"普通客户最终价:"<<goodsPrice<<std::endl;
    }

    {
        Price price(new OldCustomerStrategy);
        double goodsPrice = price.Quote(100);
        std::cout<<"老客户最终价:"<<goodsPrice<<std::endl;
    }

    {
        Price price(new LargeCustomerStrategy);
        double goodsPrice = price.Quote(100);
        std::cout<<"大客户最终价:"<<goodsPrice<<std::endl;
    }

    return 0;
}