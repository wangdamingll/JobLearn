#include <iostream>
#include <string>
#include <vector>

using namespace std;

//子系统高层接口
class AModuleApi
{
public:
    virtual void TestA(){};
};

class BModuleApi
{
public:
    virtual void TestB(){};
};

class CModuleApi
{
public:
    virtual void TestC(){};
};

//各模块子系统
//子系统A
class AModuleImpl : public AModuleApi
{
public:
    void TestA() override { std::cout<<"AModuleImpl::TestA"<<std::endl;}
};

//子系统B
class BModuleImpl : public BModuleApi
{
public:
    void TestB() override { std::cout<<"BModuleImpl::TestB"<<std::endl;}
};

//子系统C
class CModuleImpl : public CModuleApi
{
public:
    void TestC() override { std::cout<<"CModuleImpl::TestC"<<std::endl;}
};

//外观类
class Facade
{
public:
    //封装交互 简化调用
    void Test()
    {
        AModuleApi* pAApi = new AModuleImpl();
        BModuleApi* pBApi = new BModuleImpl();
        CModuleApi* pCApi = new CModuleImpl();

        pAApi->TestA();
        pBApi->TestB();
        pCApi->TestC();

        delete pAApi;
        delete pBApi;
        delete pCApi;
    }
};

//位于其他系统侧
//------------------------------------------------------
//位于客户端侧

int main()
{
    Facade facade;
    facade.Test();
    return 0;
}