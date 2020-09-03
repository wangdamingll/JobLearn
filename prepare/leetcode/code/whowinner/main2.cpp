#include <iostream>
#include <vector>
using namespace std;

/*
leetcode:https://leetcode-cn.com/problems/stone-game/

877. 石子游戏
亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。
游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。
亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。


示例：
输入：[5,3,4,5]
输出：true
解释：
亚历克斯先开始，只能拿前 5 颗或后 5 颗石子 。
假设他取了前 5 颗，这一行就变成了 [3,4,5] 。
如果李拿走前 3 颗，那么剩下的是 [4,5]，亚历克斯拿走后 5 颗赢得 10 分。
如果李拿走后 5 颗，那么剩下的是 [3,4]，亚历克斯拿走后 4 颗赢得 9 分。
这表明，取前 5 颗石子对亚历克斯来说是一个胜利的举动，所以我们返回 true 。


提示：
2 <= piles.length <= 500
piles.length 是偶数。
1 <= piles[i] <= 500
sum(piles) 是奇数。

 */

//普通递归
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return stoneGame(piles,0,piles.size()-1)>=0 ;
    }
    int stoneGame(vector<int>& piles,int start, int end){
        if(start>=end){
            return piles[start];
        }

        int totalStart = piles[start] - stoneGame(piles,start+1,end);
        int totalEnd = piles[end] - stoneGame(piles,start,end-1);
        return std::max(totalStart,totalEnd);
    }
};

//记忆递归
class Solution1 {
public:
    bool stoneGame(vector<int>& piles) {
        int dp[500][500]={0};
        return stoneGame(piles,0,piles.size()-1,dp)>=0 ;
    }
    int stoneGame(vector<int>& piles,int start, int end,int(*dp)[500]){
        if(dp[start][end]!=0){
            return dp[start][end];
        }

        if(start>=end){
            dp[start][start] = piles[start];
            return piles[start];
        }

        int totalStart = piles[start] - stoneGame(piles,start+1,end,dp);
        int totalEnd = piles[end] - stoneGame(piles,start,end-1,dp);
        dp[start][end] = std::max(totalStart,totalEnd);
        return dp[start][end] ;
    }
};

//dp
class Solution2 {
public:
    bool stoneGame(vector<int>& piles) {
        int dp[500][500]={0};
        int size = piles.size();
        for(int index=0;index<size;index++){
            dp[index][index] = piles[index];
        }

        //dp[i][j] =std::max( (piles[i]-dp[i+1][j],piles[j]-dp[i][j-1]) );
        for(int i=size-2;i>=0;i--){
            for(int j=i+1;j<size;j++){
                dp[i][j] = std::max(piles[i]-dp[i+1][j],piles[j]-dp[i][j-1]);
            }
        }
        return dp[0][size-1]>=0;
    }

};

//dp空间优化
class Solution3 {
public:
    bool stoneGame(vector<int>& piles) {
        int dp[500]={0};
        int size = piles.size();
        for(int index=0;index<size;index++){
            dp[index] = piles[index];
        }

        //dp[j] =std::max( (piles[i]-dp[j],piles[j]-dp[j-1]) );
        for(int i=size-2;i>=0;i--){
            for(int j=i+1;j<size;j++){
                dp[j] = std::max(piles[i]-dp[j],piles[j]-dp[j-1]);
            }
        }
        return dp[size-1]>=0;
    }
};

//piles.szie()为偶数且总和为奇数，先手必胜
//作为先手的 Alex 可以在第一次取走石子时就决定取走哪一组的石子，并全程取走同一组的石子。既然如此，Alex 是否有必胜策略？
//答案是肯定的。将石子分成两组之后，可以计算出每一组的石子数量，同时知道哪一组的石子数量更多。Alex 只要选择取走数量更多的一组石子即可。因此，Alex 总是可以赢得比赛。


class Solution4 {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

int main() {
    Solution4 s;
    std::vector<int> vc{5,3,4,5,6,10};

    bool ret = s.stoneGame(vc);
    if(ret){
        std::cout<<"Alex"<<std::endl;
    }else{
        std::cout<<"Lee"<<std::endl;
    }

    return 0;
}
