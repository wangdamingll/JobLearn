#include <iostream>
#include <vector>
using namespace std;

/*
剑指 Offer 42. 连续子数组的最大和
输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
要求时间复杂度为O(n)。


示例1:
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

提示：
1 <= arr.length <= 10^5
-100 <= arr[i] <= 100

注意：本题与主站 53 题相同：https://leetcode-cn.com/problems/maximum-subarray/
 */

//暴力枚举:双层for循环:虽然能解出来结果，但是不符合题目要求：O(N^2)

//递归
//时间复杂度:O(n):T(n) = T(n-1) + O(1)
//空间复杂度:O(1)
class Solution1 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int res = nums[0];
        MaxSubArray(nums,0,size,0,res);
        return res;
    }

    int MaxSubArray(vector<int>& nums,int index,int size,int thisSum,int& res){
        if(index>=size){
            return 0;
        }
        //先序处理(把本次计算的值传入下次递归)
        int sum = std::max(thisSum,0) + nums[index];
        if(sum>res){
            res = sum;
        }
        return MaxSubArray(nums,index+1,size,sum,res);
    }
};

//DP
//dp[i] = dp[i-1] + nums[i] (dp[i-1] >0)
//dp[i] = num[i] (dp[i-1]<=0)
//时间复杂度:O(n)
//空间复杂度:O(1)：使用原来数组
class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int res= nums[0];
        for(int i=1;i<size;i++){
            nums[i]  =  std::max(nums[i-1],0) + nums[i];
            res = std::max(res,nums[i]);
        }
        return res;
    }
};


//DP
//dp[i] = dp[i-1] + nums[i] (dp[i-1] >0)
//dp[i] = num[i] (dp[i-1]<=0)
//时间复杂度:O(n)
//空间复杂度:O(1)：不使用原来数组
class Solution3 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int res= nums[0];
        int former = 0; //dp[i-1]的值
        int cur =nums[0]; //记录dp[i]的值
        for(int i=0;i<size;i++){
            cur  =  std::max(former,0) + nums[i];
            res = std::max(res,cur);
            former = cur;
        }
        return res;
    }
};

//分治思想:利用线段树
//[l,r] <= [(l,m),(m+1,r)]
class Solution4 {
    struct Status{
        int lSum; //(l,r)区间以l为左端点的最大子段和
        int rSum; //(l,r)区间以r为右端点的最大子段和
        int mSum; //(l,r)区间的最大子段和
        int iSum; //(l,r)区间的和
    };
public:
    int maxSubArray(vector<int>& nums) {
        return MaxSubArray(nums,0,nums.size()-1).mSum;
    }

    Status MaxSubArray(vector<int>& nums,int l,int r){
        if(l>=r){
            return {nums[l],nums[l],nums[l],nums[l]};
        }
        int mid = l + ((r-l)>>1);

        Status ls = MaxSubArray(nums,l,mid);  //计算左子区间的状态
        Status rs = MaxSubArray(nums,mid+1,r);//计算右子区间的状态
        return PushUp(ls,rs); //合并计算父区间的状态
    }

    Status PushUp(Status l,Status r){
        int iSum = l.iSum + r.iSum;
        int lSum = std::max(l.lSum, l.iSum + r.lSum);
        int rSum = std::max(r.rSum, r.iSum + l.rSum);
        int mSum = std::max(std::max(l.mSum,r.mSum),l.rSum + r.lSum);//最大值:左子区间最大值或者右子区间最大值或者跨越中点区间的最大值
        return {lSum,rSum,mSum,iSum};
    }
};

int main() {
    std::vector<int> vc{-2,1,-3,4,-1,2,1,-5,4};
    Solution1 s;
    int ret = s.maxSubArray(vc);
    std::cout<<"sum:"<<ret<<std::endl;
}
