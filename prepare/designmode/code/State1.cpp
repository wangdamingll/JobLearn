#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;

//由上下文统一进行状态维护

//投票上层接口
class VoteState
{
public:
    //user:投票人
    //VoteItem:投票项
    //voteInfo:本来这里应该传VoteManage对象,但是C++没有反射,只能暂时这样
    virtual void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo) = 0;
};

//正常投票
class NormalVote : public VoteState
{
public:
    void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo) override
    {
        voteInfo.emplace(user, voteItem);
        std::cout<<user<<":"<<voteItem<<":正常投票!"<<std::endl;
    }
};

//正常投票
class RepeatedVote : public VoteState
{
public:
    void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo) override
    {
        std::cout<<user<<":"<<voteItem<<":重复投票投票!"<<std::endl;
    }
};

//投票管理器
class VoteManage
{
public:
    void Vote(const std::string& user, const std::string& voteItem)
    {
        std::unique_ptr<VoteState> pState(nullptr);
        const auto& iter = voteInfo.find(user);
        if(iter != voteInfo.end())
        {
            //重复投票
            pState.reset(new RepeatedVote());
        } else
        {
            //正常投票
            pState.reset(new NormalVote());
        }
        if(pState != nullptr)
        {
            pState->Vote(user, voteItem, voteInfo);
        }
    }

private:
    std::map<std::string, std::string> voteInfo; //投票信息 <投票人,投票项>
};


int main()
{
    VoteManage voteManage;
    for(uint32_t i = 0; i < 2; i++)
    {
        voteManage.Vote("张三","班长");
    }
    return 0;
}