/*
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。

示例 1：
输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶

示例 2：
输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶
*/

#include <iostream>
#include <vector>

//1. 递归回溯(本题超时)
// 时间复杂度:O(2^N)
// 空间复杂度:O(N)
class Solution1 {
public:
    int climbStairs(int n) {
        if(n==0) return 0;

        int num=0;
        ClimbStairs(n,num);
        return num;
    }

    void ClimbStairs(int n,int& num){
        if(n==0){
            num++;
        }

        for(int i=1;i<=2;i++){
            if(n-i>=0){
                ClimbStairs(n-i,num);
            }
        }
    }
};

//2. 递归(使用合适的递归方程)(本题超时)
// f(0)=0 f(1)=1 f(2)=2 f(3)=3 f(4)=5
// f(x) = f(x-1) + f(x-2)
// 也就是说n台阶的方案和是n-1的方案和 和 n-2的方案和 的加法和
// 时间复杂度:O(2^N)  T(N) = T(N-1) + T(N-2) + O(1)
// 空间复杂度:O(N)
class Solution2 {
public:
    int climbStairs(int n) {
        if(n==1){
            return 1;
        } else if(n==2){
            return 2;
        }
        return (climbStairs(n-1) + climbStairs(n-2));
    }
};

//3. 记忆化递归
// 时间复杂度:O(N) (每个节点只会被计算一次)
// 空间复杂度:O(N)
// 为什么会想到记忆化递归？
// 分析第二种解决方法:在递归过程中存在重复子问题的计算
// 递归树
//                           5
//
//                    4             3
//
//                3      2       2      1
//                       *       *
//             2   1
class Solution3 {
public:
    int climbStairs(int n) {
        std::vector<uint32_t> dp;
        dp.resize(n+1);
        return ClimbStairs(n,dp);
    }

    int ClimbStairs(int n,std::vector<uint32_t>& dp) {
        if(dp[n]!=0){
            return dp[n];
        }

        if(n==1){
            dp[n]=1;
        } else if(n==2){
            dp[n] = 2;
        }else{
            dp[n] = ClimbStairs(n-1,dp) + ClimbStairs(n-2,dp);
        }
        return dp[n];
    }
};

//4. dp
// 时间复杂度:O(N)
// 空间复杂度:O(N)
//dp[n] = dp[n-1] + dp[n-2]
class Solution4 {
public:
    int climbStairs(int n) {
        std::vector<uint32_t> dp;
        dp.resize(n+5);
        dp[1] = 1;
        dp[2] = 2;

        for(uint32_t i=3;i<=n;i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};

//5 dp 滚动数组
// 时间复杂度:O(N)
// 空间复杂度:O(1)
//dp[n] = dp[n-1] + dp[n-2]
//因为计算dp[n]只与dp[n-1]和dp[n-2]有关系
class Solution5 {
public:
    int climbStairs(int n) {
        uint32_t first = 0;
        uint32_t second = 0;
        uint32_t third = 1;

        for(uint32_t i=1;i<=n;i++){
            first = second;
            second = third;
            third = first + second;
        }
        return third;
    }
};

int main() {
    Solution5 s;
    int n = 4;
    int num = s.climbStairs(n);
    std::cout<<"num="<<num<<std::endl;
    return 0;
}