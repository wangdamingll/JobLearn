#include <iostream>
#include <string>
#include <memory>

using namespace std;

//策略模式扩展方式
//1.扩展上下文:通过继承上下文方式,然后在子类中添加相关数据
//2.扩展策略算法:在具体策略算法中添加相关数据

//高层策略接口
class PayStrategy
{
public:
    //virtual void Pay(PayContext* pPayContext){} //c++ 没有反射 不能直接传入context 然后获取上下文相关数据 适用于扩展方式1
    virtual void Pay(const std::string& user, double money){}
};

//具体策略
//人民币现金支付
class RMBCashStrategy : public PayStrategy
{
public:
    void Pay(const std::string& user, double money) override
    {
        std::cout<<user<<"人民币现金支付:"<<money<<std::endl;
    }
};

//美元支付
class DollarCashStrategy : public PayStrategy
{
public:
    void Pay(const std::string& user, double money) override
    {
        std::cout<<user<<"美元现金支付:"<<money<<std::endl;
    }
};

//RMB账户支付 扩展方式2
class RMBAccountStrategy : public PayStrategy
{
private:
    std::string account;
public:
    RMBAccountStrategy(std::string account) : account(account){}
public:
    void Pay(const std::string& user, double money) override
    {
        std::cout<<user<<"RMB账户"<<account<<"支付:"<<money<<std::endl;
    }
};

//策略上下文
class PayContext
{
private:
    std::string user;
    double money;

public:
    PayContext(std::string user, double money, PayStrategy* payStrategy) : user(user), money(money), pPayStrategy(payStrategy){}

public:
    void PayNow()
    {
        if(pPayStrategy != nullptr)
        {
            return pPayStrategy->Pay(this->user, this->money);
        }
    }

private:
    std::unique_ptr<PayStrategy> pPayStrategy {nullptr};
};


int main()
{
    {
        PayContext* payContext = new PayContext("张三", 100.0, new RMBCashStrategy());
        payContext->PayNow();
    }

    {
        PayContext* payContext = new PayContext("petter", 200.0, new DollarCashStrategy());
        payContext->PayNow();
    }

    {
        PayContext* payContext = new PayContext("李四", 300.0, new RMBAccountStrategy("123456789"));
        payContext->PayNow();
    }
    return 0;
}