#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
464. 我能赢吗
在 "100 game" 这个游戏中，两名玩家轮流选择从 1 到 10 的任意整数，累计整数和，先使得累计整数和达到或超过 100 的玩家，即为胜者。
如果我们将游戏规则改为 “玩家不能重复使用整数” 呢？

例如，两个玩家可以轮流从公共整数池中抽取从 1 到 15 的整数（不放回），直到累计整数和 >= 100。
给定一个整数 maxChoosableInteger （整数池中可选择的最大数）和另一个整数 desiredTotal（累计和），判断先出手的玩家是否能稳赢（假设两位玩家游戏时都表现最佳）？
你可以假设 maxChoosableInteger 不会大于 20， desiredTotal 不会大于 300。

示例：
输入：
maxChoosableInteger = 10
desiredTotal = 11

输出：
false

解释：
无论第一个玩家选择哪个整数，他都会失败。
第一个玩家可以选择从 1 到 10 的整数。
如果第一个玩家选择 1，那么第二个玩家只能选择从 2 到 10 的整数。
第二个玩家可以通过选择整数 10（那么累积和为 11 >= desiredTotal），从而取得胜利.
同样地，第一个玩家选择任意其他整数，第二个玩家都会赢。
 */

//普通递归(超时)
class Solution1 {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(maxChoosableInteger>=desiredTotal) return true;
        if((maxChoosableInteger+1)*maxChoosableInteger/2 < desiredTotal) return false;

        int * book = new int[maxChoosableInteger+1];
        std::memset(book,0,(maxChoosableInteger+1)* sizeof(int));
        return CanWin(maxChoosableInteger,desiredTotal,book);
    }

    bool CanWin(int maxChooseableInteger,int desiredTotal,int* book){
        for(int i=1;i<=maxChooseableInteger;i++){
            if(book[i]==0){
                book[i] =1;
                if(desiredTotal-i<=0||!CanWin(maxChooseableInteger,desiredTotal-i,book)){
                    book[i] =0;
                    return true;
                }
                book[i] =0;
            }
        }
        return false;
    }
};


//记忆递归
class Solution2 {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(maxChoosableInteger>=desiredTotal) return true;
        if((maxChoosableInteger+1)*maxChoosableInteger/2 < desiredTotal) return false;

        int* dp = new int[(1<<maxChoosableInteger)-1];
        std::memset(dp,0, ((1<<maxChoosableInteger)-1) * sizeof(int));

        return CanWin(maxChoosableInteger,desiredTotal,0,dp);
    }

    bool CanWin(int maxChooseableInteger,int desiredTotal,int book,int* dp){
        if(dp[book]!=0){
            return (dp[book]==1);
        }
        for(int i=1;i<=maxChooseableInteger;i++){
            int tmp = 1<<(i-1);
            if(0== (tmp & book)){
                if(desiredTotal-i<=0||!CanWin(maxChooseableInteger,desiredTotal-i,tmp|book,dp)){
                    dp[book] = 1;
                    return true;
                }
            }
        }
        dp[book] = 2;
        return false;
    }
};

int main() {
    Solution2 s;
    bool ret = s.canIWin(4,6);
    if(ret){
        std::cout<<"true"<<std::endl;
    }else{
        std::cout<<"false"<<std::endl;
    }

    return 0;
}
