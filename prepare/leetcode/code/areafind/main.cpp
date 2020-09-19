#include <iostream>
#include <vector>
using namespace std;

/*
303. 区域和检索 - 数组不可变
给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

示例：
给定 nums = [-2, 0, 3, -5, 2, -1]，求和函数为 sumRange()

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

说明:
你可以假设数组不可变。
会多次调用 sumRange 方法。
 */

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
*/

//普通解法(暴力枚举)
class NumArray1 {
    std::vector<int> v;
public:
    NumArray1(vector<int>& nums) {
        v = std::move(nums);
    }

    int sumRange(int i, int j) {
        int sum = 0;
        for(int index=i;index<=j;index++){
            sum+=v[index];
        }
        return sum;
    }
};

//普通递归
class NumArray2 {
    std::vector<int> v;
public:
    NumArray2(vector<int>& nums) {
        v = std::move(nums);
    }

    int sumRange(int i, int j) {
        return SumRange(i,j);
    }

    int SumRange(int i,int j){
        if(i==j){
            return v[i];
        }
        return v[j] + SumRange(i,j-1);
    }
};

//记忆化递归
class NumArray3 {
    std::vector<int> v;
    std::vector<std::vector<int>> dp;
public:
    NumArray3(vector<int>& nums) {
        v = std::move(nums);

        int size = v.size();
        dp.resize(size);
        for(int index=0;index<size;index++){
            dp[index].resize(size);
        }
    }

    int sumRange(int i, int j) {
        return SumRange(i,j,dp);
    }

    int SumRange(int i,int j,std::vector<std::vector<int>>& dp){
        if(i==j){
            dp[i][i]=v[i];
            return v[i];
        }
        if(dp[i][j]!=0){
            return dp[i][j];
        }

        dp[i][j] =  v[j] + SumRange(i,j-1,dp);
        return dp[i][j];
    }
};

//dp
//dp[i][j]=v[j] + dp[i][j-1]
//dp[i][i]= v[i];

//dp[0][2] = v[2] + dp[0][1]
//dp[0][1] = v[1] + dp[0][0]
//dp[0][0] = v[0]
class NumArray4 {
    std::vector<int>* v;
    std::vector<std::vector<int>> dp;
public:
    explicit NumArray4(vector<int>& nums) {
        v = &nums;
        int size = v->size();
        dp.resize(size);
        for(int index=0;index<size;index++){
            dp[index].resize(size);
        }

        for(int k=0;k<size;k++){
            dp[k][k] = (*v)[k];
        }
    }

    int sumRange(int i, int j) {
        if(i==j){
            return dp[i][i];
        }
        for(int k=i+1;k<=j;k++){
            if(dp[i][k]!=0) continue;
            dp[i][k] = (*v)[k] + dp[i][k-1];
        }

        return dp[i][j];
    }
};

//提前缓存
class NumArray5 {
    std::vector<int> sum;
public:
    explicit NumArray5(vector<int>& nums) {
        int size = nums.size();
        sum.resize(size+1);
        for(int index=0;index<size;index++){
            sum[index+1] = nums[index] + sum[index];
        }
    }

    int sumRange(int i, int j) {
        return sum[j+1] - sum[i];
    }
};


int main() {
    std::vector<int> vc{-2, 0, 3, -5, 2, -1};

    NumArray5 s(vc);
    int ret = s.sumRange(2, 5);
    std::cout<<"sum:"<<ret<<std::endl;

}
