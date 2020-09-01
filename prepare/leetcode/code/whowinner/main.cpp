#include <iostream>
#include <vector>
using namespace std;

/*
leetcode:https://leetcode-cn.com/problems/predict-the-winner/
题解1:https://leetcode-cn.com/problems/predict-the-winner/solution/yu-ce-ying-jia-by-leetcode-solution/
题解2:https://leetcode-cn.com/problems/predict-the-winner/solution/shou-hua-tu-jie-san-chong-xie-fa-di-gui-ji-yi-hua-/

给定一个表示分数的非负整数数组。 玩家 1 从数组任意一端拿取一个分数，随后玩家 2 继续从剩余数组任意一端拿取分数，然后玩家 1 拿，…… 。
每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。

给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。

示例 1：
输入：[1, 5, 2]
输出：False
解释：一开始，玩家1可以从1和2中进行选择。
如果他选择 2（或者 1 ），那么玩家 2 可以从 1（或者 2 ）和 5 中进行选择。如果玩家 2 选择了 5 ，那么玩家 1 则只剩下 1（或者 2 ）可选。
所以，玩家 1 的最终分数为 1 + 2 = 3，而玩家 2 为 5 。
因此，玩家 1 永远不会成为赢家，返回 False 。

示例 2：
输入：[1, 5, 233, 7]
输出：True
解释：玩家 1 一开始选择 1 。然后玩家 2 必须从 5 和 7 中进行选择。无论玩家 2 选择了哪个，玩家 1 都可以选择 233 。
     最终，玩家 1（234 分）比玩家 2（12 分）获得更多的分数，所以返回 True，表示玩家 1 可以成为赢家。
 
提示：
1 <= 给定的数组长度 <= 20.
数组里所有分数都为非负数且不会大于 10000000 。
如果最终两个玩家的分数相等，那么玩家 1 仍为赢家。

 */

//方法
//博弈:极大极小策略
//先手得分为正，和取最大，后手得分为负，和取最小
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        return totalScore(nums,0,nums.size()-1,1)>=0;
    }

    int32_t totalScore(vector<int>& nums,int32_t start,int32_t end,int32_t turn){
        if(start == end){
            return nums[start] * turn;
        }

        int32_t totalStart =  nums[start] * turn +  totalScore(nums,start+1,end,-turn);
        int32_t totalEnd = nums[end]* turn + totalScore(nums,start,end-1,-turn);
        if(turn==1){
            return std::max(totalStart ,totalEnd );
        }else{
            return std::min(totalStart ,totalEnd );
        }
    }
};

//下面是三板斧
//1. 普通递归:是不是更简单。。。
class Solution1 {
public:
    bool PredictTheWinner(vector<int>& nums) {
        return totalScore(nums,0,nums.size()-1)>=0;
    }

    int32_t totalScore(vector<int>& nums,int32_t start,int32_t end){
        if(start == end){
            return nums[start] ;
        }

        int32_t totalStart =  nums[start] -  totalScore(nums,start+1,end);
        int32_t totalEnd = nums[end] - totalScore(nums,start,end-1);
        return std::max(totalStart ,totalEnd );
    }
};


//2. 记忆化递归:我们用数组或哈希表去存储计算过的子问题的解，下次遇到重复的子问题，就不用再次递归计算
class Solution2 {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int32_t arrM[20][20]={};
        return totalScore(nums,0,nums.size()-1,arrM)>=0;
    }

    int32_t totalScore(vector<int>& nums,int32_t start,int32_t end,int32_t (*arr)[20]){
        if(arr[start][end]!=0){
            return arr[start][end];
        }
        if(start == end){
            arr[start][start] = nums[start];
            return nums[start] ;
        }

        int32_t totalStart =  nums[start] -  totalScore(nums,start+1,end,arr);
        int32_t totalEnd = nums[end] - totalScore(nums,start,end-1,arr);
        arr[start][end] =  std::max(totalStart ,totalEnd );
        return arr[start][end];
    }
};

//3.dp
class Solution3 {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int32_t dpArr[3][3]={};
        int32_t size = nums.size();
        for(int32_t index=0;index<size;index++){
            dpArr[index][index] = nums[index];
        }

        //一定要注意迭代顺序,依据是动态转移方程的方向
        //      j-1     j
        //
        //  i   0  向左  0
        //
        //             向上
        //
        //  i+1         0
        for(int32_t i=size-2;i>=0;i--){
            for(int32_t j=i+1;j<size;j++){
                int32_t totalNumsStart = nums[i] - dpArr[i+1][j];
                int32_t totalNumsEnd = nums[j] - dpArr[i][j-1];
                dpArr[i][j] = std::max(totalNumsStart,totalNumsEnd);
            }
        }

        return dpArr[0][size-1]>=0;
    }

};
int main() {
    Solution sl;
    std::vector<int> vc{1,5,2};

    bool ret = sl.PredictTheWinner(vc);
    if(ret){
        std::cout<<"1"<<std::endl;
    }else{
        std::cout<<"2"<<std::endl;
    }

    return 0;
}
