#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*121. 买卖股票的最佳时机
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。

示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/

//暴力枚举
//超出时间限制
//时间复杂度：O(N^2)
//空间复杂度：O(1)
class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        int max = 0;
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                if(prices[j]-prices[i]>max){
                    max = prices[j]-prices[i];
                }
            }
        }
        return max;
    }
};

//递归
//时间复杂度: T(N) = T(N-1) + O(1) -> O(N)
//空间复杂度:O(1)
class Solution2 {
    int min {1<<30};
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        int max = 0;
        MaxProfit(prices,0,size,max);
        return max;
    }

    void MaxProfit(vector<int>& prices,int index,int size,int& max){
        if(index>=size) {
            return;
        }
        max = std::max(prices[index]-min,max);
        min = std::min(min,prices[index]);

        MaxProfit(prices,index+1,size,max);
    }
};

//dp
//时间复杂度: O(N)
//空间复杂度: O(1)
//min[i] = std::min([prices[k]])  (0<k<i)
//dp[i+1] = std::max(dp[i], prices[i] - min[i])
class Solution3 {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        int max = 0;
        int min = 1<<30;
        for(int i=0;i<size;i++){
            max = std::max(max,prices[i]-min);
            min = std::min(min,prices[i]);
        }
        return max;
    }
};

//线段树
//时间复杂度:T(N) = 2T(N/2) + O(1) -> O(N)
//空间复杂度:O(1)
class Solution4 {
    struct Status{
        int max ; //区间(l,r)中最大值
        int min ; //区间(l,r)中最小值
        int maxProfit; //区间(l,r)中差值最大值
    };
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size==0){
            return 0;
        }
        return MaxProfit(prices,0,size-1).maxProfit;
    }
    Status MaxProfit(vector<int>& prices,int lowIndex,int highIndex){
        if(lowIndex>=highIndex){
            return {prices[lowIndex],prices[lowIndex],0};
        }
        int mid = lowIndex + ((highIndex-lowIndex)>>1);
        Status l =  MaxProfit(prices,lowIndex,mid);
        Status r = MaxProfit(prices,mid+1,highIndex);
        return PushTop(l,r);
    }

    Status PushTop(Status& l,Status& r){
        int max = std::max(l.max,r.max);
        int min = std::min(l.min,r.min);
        int maxProfit = std::max(std::max(l.maxProfit,r.maxProfit),(r.max-l.min));
        return {max,min,maxProfit};
    }
};

int main() {
    std::vector<int> vc{7,1,5,3,6,4};

    Solution4 s;
    int num = s.maxProfit(vc);
    std::cout<<"num="<<num<<std::endl;
}
