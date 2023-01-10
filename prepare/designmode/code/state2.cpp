#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;

//由状态对象来维护和转换状态

//投票上层接口
class VoteState
{
public:
    //user:投票人
    //VoteItem:投票项
    //voteInfo:本来这里应该传VoteManage对象,但是C++没有反射,只能暂时这样
    //voteState:同上
    virtual void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo, std::map<std::string, std::shared_ptr<VoteState>>& voteState) = 0;
};

//重复投票
class RepeatedVote : public VoteState
{
public:
    void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo,  std::map<std::string, std::shared_ptr<VoteState>>& voteState) override
    {
        std::cout<<user<<":"<<voteItem<<":重复投票投票!"<<std::endl;
    }
};

//正常投票
class NormalVote : public VoteState
{
public:
    void Vote(const std::string& user, const std::string& voteItem, std::map<std::string, std::string>& voteInfo, std::map<std::string, std::shared_ptr<VoteState>>& voteState) override
    {
        voteInfo.emplace(user, voteItem);
        voteState[user].reset(new RepeatedVote());
        std::cout<<user<<":"<<voteItem<<":正常投票!"<<std::endl;
    }
};

//投票管理器
class VoteManage
{
public:
    void Vote(const std::string& user, const std::string& voteItem)
    {
        std::shared_ptr<VoteState> pState(nullptr);
        const auto& iter = voteState.find(user);
        if(iter == voteState.end())
        {
            auto ret = voteState.emplace(user, new NormalVote());
            if(ret.second)
            {
                pState = ret.first->second;
            }
        } else
        {
            pState = iter->second;
        }

        if(pState != nullptr)
        {
            pState->Vote(user, voteItem, voteInfo, voteState);
        }
    }

private:
    std::map<std::string, std::string> voteInfo; //投票信息 <投票人,投票项>
    std::map<std::string, std::shared_ptr<VoteState>> voteState; //投票状态 <投票人, 投票状态>
};


int main()
{
    VoteManage voteManage;
    for(uint32_t i = 0; i < 3; i++)
    {
        voteManage.Vote("张三","班长");
    }
    return 0;
}