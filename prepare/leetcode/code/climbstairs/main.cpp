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

int main() {
    //1134903170

    Solution1 s;
    int n = 4;
    int num = s.climbStairs(n);
    std::cout<<"num="<<num<<std::endl;
    return 0;
}