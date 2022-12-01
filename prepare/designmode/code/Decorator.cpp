#include <iostream>
#include <string>
#include <memory>

using namespace std;

//高层组件
class Component
{
public:
    //计算奖金
    virtual uint32_t CalcPrize(std::string user){return 0;}
};

//计算奖金组件
class ConcreteComponent : public Component
{
public:
    //基础计算奖金
    uint32_t CalcPrize(std::string user) override
    {
        return 0;//默认返回0
    };
};

//抽象装饰器
class Decorator : public Component
{
public:
    uint32_t CalcPrize(std::string user){return 0;}
};

//各种装饰器
//团队计算奖金
class GroupPrizeDecorator : public Decorator
{
public:
    GroupPrizeDecorator(){}
    GroupPrizeDecorator(Decorator* pDecorator) : pComponent (pDecorator){}
public:
    //计算团队奖金
    uint32_t CalcPrize(std::string user) override
    {
        uint32_t prize = 0;
        uint32_t groupPrize = 1000;
        if(pComponent != nullptr)
        {
            prize = pComponent->CalcPrize(user);
        }

        if(user == "张三")
        {
            prize += groupPrize;
            std::cout<<user<<":团队奖金为:1000元"<<std::endl;
        }
        return prize;
    }

private:
    std::unique_ptr<Decorator> pComponent;
};

//个人累计奖金
class SumPrizeDecorator : public Decorator
{
public:
    SumPrizeDecorator(){}
    SumPrizeDecorator(Decorator* pDecorator) : pComponent (pDecorator){}
public:
    //个人累计奖金
    uint32_t CalcPrize(std::string user) override
    {
        uint32_t prize = 500;
        if(pComponent != nullptr)
        {
            prize += pComponent->CalcPrize(user);
        }
        std::cout<<user<<":累计奖金为:500元"<<std::endl;
        return prize;
    }

private:
    std::unique_ptr<Decorator> pComponent;
};

//个人月度奖金
class MonthPrizeDecorator : public Decorator
{
public:
    MonthPrizeDecorator(){}
    MonthPrizeDecorator(Decorator* pDecorator) : pComponent (pDecorator){}
public:
    //计算个人月度奖金
    uint32_t CalcPrize(std::string user) override
    {
        uint32_t prize = 200;
        if(pComponent != nullptr)
        {
            prize += pComponent->CalcPrize(user);
        }
        std::cout<<user<<":月度奖金为:200元"<<std::endl;
        return prize;
    }

private:
    std::unique_ptr<Decorator> pComponent;
};

int main()
{
    //张三为项目经理 只有张三才有团队奖金
    {
        //计算个人奖金
        Component* pComponent = new GroupPrizeDecorator(new SumPrizeDecorator(new MonthPrizeDecorator()));
        uint32_t prize = pComponent->CalcPrize("张三");
        std::cout<<"张三:总奖金为:"<<prize<<std::endl;
        prize = pComponent->CalcPrize("李四");
        std::cout<<"李四:总奖金为:"<<prize<<std::endl;
    }


    std::cout<<"------------------调换一下装饰器顺序------------------------"<<std::endl;

    {
        Component* pComponent = new SumPrizeDecorator(new MonthPrizeDecorator(new GroupPrizeDecorator()));
        uint32_t prize = pComponent->CalcPrize("张三");
        std::cout<<"张三:总奖金为:"<<prize<<std::endl;
        prize = pComponent->CalcPrize("李四");
        std::cout<<"李四:总奖金为:"<<prize<<std::endl;
    }

    return 0;
}