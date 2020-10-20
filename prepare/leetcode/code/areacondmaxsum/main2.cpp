/*
198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。


示例 2：
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
 

提示：
0 <= nums.length <= 100
0 <= nums[i] <= 400
*/

#include <iostream>
#include <vector>

using namespace std;

//普通递归(本题超时)
//时间复杂度:O(2^N)
//空间复杂度:O(N)
//dp[n] 偷到第n间房子偷到的最大值
//dp[0] = 0; n=0
//dp[1] = 1; n=1
//dp[n] = std::max(dp[n-1],dp[n-2] + nums[n]); n>=2
class Solution1 {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size==0) return 0;
        return Rob(nums,size-1);
    }

    int Rob(vector<int>& nums,int index) {
        if(index<0){
            return 0;
        }
        int dpPpre = Rob(nums,index-2);
        int dpPre = Rob(nums,index-1);
        return std::max(dpPre, dpPpre + nums[index]);;
    }
};

//记忆化递归
//时间复杂度:O(N)
//空间复杂度:O(N)
//dp[n] 偷到第n间房子偷到的最大值
//dp[0] = 0; n=0
//dp[1] = 1; n=1
//dp[n] = std::max(dp[n-1],dp[n-2] + nums[n]); n>=2
class Solution2 {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        std::vector<int> dpV;
        dpV.resize(size+2);
        for(auto& it:dpV){
            it = -1;
        }
        return Rob(nums,size-1,dpV);
    }

    int Rob(vector<int>& nums,int index,std::vector<int>& dpV) {
        if(index<0){
            return 0;
        }

        if(dpV[index]>=0){
            return dpV[index];
        }

        int dpPpre = Rob(nums,index-2,dpV);
        int dpPre = Rob(nums,index-1,dpV);
        int dp = std::max(dpPre, dpPpre + nums[index]);;
        dpV[index] = dp;
        return dp;
    }
};


//尾递归
//时间复杂度:O(N)
//空间复杂度:O(1)
//dp[n] 偷到第n间房子偷到的最大值
//dp[0] = 0; n=0
//dp[1] = 1; n=1
//dp[n] = std::max(dp[n-1],dp[n-2] + nums[n]); n>=2
class Solution3 {
public:
    int rob(vector<int>& nums) {
        int dpPpre = 0;
        int dpPre = 0;
        int dp = 0;
        Rob(nums,0,0,0,dp);
        return dp;
    }

    int Rob(vector<int>&nums,int index,int dpPpre, int dpPre, int& dp){
        if(index>=nums.size()){
            return 0;
        }
        dp = std::max(dpPre,dpPpre + nums[index]);
        return Rob(nums,index+1,dpPre,dp,dp);
    }
};


//dp:借用滚动数组思想
//时间复杂度:O(N)
//空间复杂度:O(1)
//dp[0] = 0;
//dp[1] = 1
//dp[2] = 2
//dp[n] 偷到第n间房子偷到的最大值
//dp[0] = 0; n=0
//dp[1] = 1; n=1
//dp[n] = std::max(dp[n-1],dp[n-2] + nums[n]); n>=2
class Solution4 {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        int dpPpre = 0;
        int dpPre = 0;
        int dp = 0;
        for(int i=0;i<size;i++){
            dp = std::max(dpPre, dpPpre + nums[i]);
            dpPpre = dpPre;
            dpPre = dp;
        }
        return dp;
    }
};

int main() {
    Solution2 s;
    std::vector<int> v{1,2,3,1};
    int num = s.rob(v);
    std::cout<<"num="<<num<<std::endl;
    return 0;
}