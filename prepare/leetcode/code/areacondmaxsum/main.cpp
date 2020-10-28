#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*面试题 17.16. 按摩师
一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。
给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。

注意：本题相对原题稍作改动

示例 1：
输入： [1,2,3,1]
输出： 4
解释： 选择 1 号预约和 3 号预约，总时长 = 1 + 3 = 4。

示例 2：
输入： [2,7,9,3,1]
输出： 12
解释： 选择 1 号预约、 3 号预约和 5 号预约，总时长 = 2 + 9 + 1 = 12。

示例 3：
输入： [2,1,4,5,3,1,1,3]
输出： 12
解释： 选择 1 号预约、 3 号预约、 5 号预约和 8 号预约，总时长 = 2 + 4 + 3 + 3 = 12。
*/


//动态规划:使用二维构建动态转移方程
//dp[i][0]:表示第i天不接受预约的最大时长
//dp[i][1]:表示第i天接受预约的最大时长
//dp[i][0] = std::max(dp[i-1][0],dp[i-1][1]) ->第i-1天可接受预约，也可以不接受预约
//dp[i][1] = dp[i-1][0] + nums[i]   -> 第i-1天只可以不接受预约
//return std::max(dp[n][0],dp[n][1]) ->返回第n天接受预约、不接受预约的最大值
//仔细看看动态转移方程:计算dp[i][0/1]时，只和dp[i-1][0/1]有关系. 参考滚动数组的思想，可以保存dp[i-1][0] 和dp[i-1][1]的值
class Solution1 {
public:
    int massage(vector<int>& nums) {
        int size = nums.size();
        if(size==0) return 0;
        int dp0 = 0;        //存储dp[0][0]
        int dp1 = nums[0];  //存储dp[0][1]

        int tdp0 = 0;
        int tdp1 = 0;
        for(int i=1;i<size;i++){
            tdp0 = std::max(dp0,dp1);   //计算dp[i][0]
            tdp1 = dp0 + nums[i];       //计算dp[i][1]
            dp0 = tdp0;
            dp1 = tdp1;
        }
        return std::max(dp0,dp1);
    }
};

//动态规划:使用一维数组构建动态转移方程
//dp[i]表示第[i]天最大预约时长
//orders[i]表示第i天的订单
//dp[i] = orders[1]  i=1
//dp[i] = std::max(orders[1],orders[2])  i=2
//dp[i] = std::max(dp[i-1],dp[i-2] + orders[i]) i>2
//dp[i]分为2中情况:
//第一种:第i天不接受订单，那么第i-1天是可以接受订单，也可以不接受订单，即dp[i-1]
//第二种:第i天接受订单，那么第i-1天则不能接受订单,即第i-2天的最大时长加上第i天的时长，即dp[i-2] + nums[i]
//计算dp[i]时，也只和dp[i-1] dp[i-2]有关系，因此可以保存它们用于计算

class Solution2 {
public:
    int massage(vector<int>& nums) {
        int size = nums.size();

        int dpPpre = 0; //dp[i-2]
        int dpPre = 0;  //dp[i-1]
        int dpCur = 0;  //dp[i]

        //3 <- 2  1
        //4 <- 3  2
        //5 <- 4  3
        for(int i=0;i<size;i++){
            dpPpre = dpPre;
            dpPre = dpCur;
            dpCur = std::max(dpPre,dpPpre + nums[i]);
        }
        return dpCur;
    }
};
int main() {
    //std::vector<int> vc{1,2,3,1};
    std::vector<int> vc{2,1,4,5,3,1,1,3};
    //std::vector<int> vc{1,3,1};

    Solution2 s;
    int num = s.massage(vc);
    std::cout<<"num="<<num<<std::endl;
}
