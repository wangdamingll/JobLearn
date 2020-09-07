#include <iostream>
#include <vector>
using namespace std;

/*
我们正在玩一个猜数游戏，游戏规则如下：
我从 1 到 n 之间选择一个数字，你来猜我选了哪个数字。
每次你猜错了，我都会告诉你，我选的数字比你的大了或者小了。
然而，当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。直到你猜到我选的数字，你才算赢得了这个游戏。
示例:
n = 10, 我选择了8.
第一轮: 你猜我选择的数字是5，我会告诉你，我的数字更大一些，然后你需要支付5块。
第二轮: 你猜是7，我告诉你，我的数字更大一些，你支付7块。
第三轮: 你猜是9，我告诉你，我的数字更小一些，你支付9块。

游戏结束。8 就是我选的数字。

你最终要支付 5 + 7 + 9 = 21 块钱。
给定 n ≥ 1，计算你至少需要拥有多少现金才能确保你能赢得这个游戏。
 */

//普通递归(暴力枚举)
class Solution1 {
public:
    int getMoneyAmount(int n) {
        return GetMoney(1,n);
    }

    int GetMoney(int low, int high){
        if(low>=high){
            return 0;
        }
        int minRes = std::numeric_limits<int>::max();
        for(int i=low;i<=high;i++){
            int res = i + std::max(GetMoney(low,i-1),GetMoney(i+1,high));
            minRes = std::min(res,minRes);
        }
        return minRes;
    }
};

//普通递归(优化:右边区间消耗比左边大)
class Solution2 {
public:
    int getMoneyAmount(int n) {
        return GetMoney(1,n);
    }

    int GetMoney(int low, int high){
        if(low>=high){
            return 0;
        }
        int minRes = std::numeric_limits<int>::max();
        for(int i=(low+high)/2;i<=high;i++){
            int res = i + std::max(GetMoney(low,i-1),GetMoney(i+1,high));
            minRes = std::min(res,minRes);
        }
        return minRes;
    }
};


//记忆化递归
class Solution3 {
public:
    int getMoneyAmount(int n) {
        std::vector<std::vector<int>> vec;
        vec.resize(n+1);
        for(int i=0;i<n+1;i++){
            vec[i].resize(n+1);
        }
        return GetMoney(1,n,vec);
    }

    int GetMoney(int low, int high,std::vector<std::vector<int>>& vec){
        if(low>=high){
            return 0;
        }

        if(vec[low][high]!=0){
            return vec[low][high];
        }

        int minRes = std::numeric_limits<int>::max();
        for(int i=(low+high)/2;i<=high;i++){
            int res = i + std::max(GetMoney(low,i-1,vec),GetMoney(i+1,high,vec));
            minRes = std::min(res,minRes);
        }
        vec[low][high] = minRes;
        return minRes;
    }
};

//dp(普通dp)
class Solution4 {
public:
    int getMoneyAmount(int n) {
        std::vector<std::vector<int>> dp;
        dp.resize(n+2);
        for(int i=0;i<n+2;i++){
            dp[i].resize(n+2);
        }

        for(int i=n-1;i>=1;i--){
            for(int j=i+1;j<=n;j++){
                int minRes = std::numeric_limits<int>::max();
                int res =0;
                for(int k=i ;k<=j;k++){
                    res = k + std::max(dp[i][k-1],dp[k+1][j]);
                    minRes = std::min(res,minRes);
                }
                dp[i][j] = minRes;
            }
        }
        return dp[1][n];
    }
};

//dp优化(右半边消耗大)
class Solution5 {
public:
    int getMoneyAmount(int n) {
        std::vector<std::vector<int>> dp;
        dp.resize(n+2);
        for(int i=0;i<n+2;i++){
            dp[i].resize(n+2);
        }

        for(int i=n-1;i>=1;i--){
            for(int j=i+1;j<=n;j++){
                int minRes = std::numeric_limits<int>::max();
                int res =0;
                for(int k=i + (j-i)/2;k<=j;k++){
                    res = k + std::max(dp[i][k-1],dp[k+1][j]);
                    minRes = std::min(res,minRes);
                }
                dp[i][j] = minRes;
            }
        }
        return dp[1][n];
    }
};

int main() {
    Solution5 s;
    int num = s.getMoneyAmount(10);
    std::cout<<"getMoneyAmount:num:"<<num<<std::endl;
    return 0;
}
