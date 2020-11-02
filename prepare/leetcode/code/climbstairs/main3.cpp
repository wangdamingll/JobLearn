#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>
using namespace std;

/*
面试题 08.01. 三步问题
三步问题。有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。
实现一种方法，计算小孩有多少种上楼梯的方式。结果可能很大，你需要对结果模1000000007。

示例1:
输入：n = 3
输出：4
说明: 有四种走法

示例2:
输入：n = 5
输出：13

提示:
n范围在[1, 1000000]之间
*/

//回溯法(本题超时):基本是枚举所有情况
//时间复杂度:O(2^N)
//空间复杂度:O(N)
class Solution1 {
public:
    int waysToStep(int n) {
        if(n==0) return 0;
        int nums = 0;
        WaysToStep(n,nums);
        return nums;
    }

    int WaysToStep(int n,int& nums) {
        if(n==0){
            nums++ ;
        }
        for(int i=1;i<=3;i++){
            if(n-i>=0){
                WaysToStep(n-i,nums);
            }
        }
        return 0;
    }
};



//dp
//时间复杂度:O(N)
//空间复杂度:O(1)
//dp[0] = 0
//dp[1] = 1   i=1
//dp[2] = 2   i=2
//dp[3] = 4   i=3
//dp[i] = dp[i-1] + dp[i-2] + dp[i-3] (i>=3)

//dp[0] = 0
//dp[1] = 1
//dp[2] = 2
//dp[3] = 4
//dp[4] = 7
//dp[5] = 13
class Solution2 {
public:
    int waysToStep(int n) {
        if(n==1){
            return 1;
        }else if(n==2){
            return 2;
        }else if(n==3){
            return 4;
        }

        int first = 1;
        int second = 2;
        int third = 4;
        int cur = 0;
        for(int i=3;i<n;i++){
            cur = (first + second + third)%1000000007;
            first = second%1000000007;
            second = third%1000000007;
            third  = cur;
        }
        return cur;
    }
};

int main() {
    Solution1 s;
    int n = 5;
    int num = s.waysToStep(n);
    std::cout<<"num="<<num<<std::endl;
    return 0;
}