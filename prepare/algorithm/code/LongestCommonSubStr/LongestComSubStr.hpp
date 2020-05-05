#ifndef __THIEFBACKPACK__H__
#define __THIEFBACKPACK__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


/* 动态规划-------最长公共子串问题
 *
 * 问题描述:
 * 假设原本想输入fish,结果误输入成hish,当然没有这个词了,请问系统该提示什么单词呢?
 *
 * 说明:
 * 其实也就是求和fish公共子串最长的那些单词作为提示了.这里以求fish和hish的最长公共子串为例
 *
 * 算法思想:
 * 求解最长公共子串问题,可以使用动态规划求得最优解.
 *
 * 时间复杂度
 * 1. 采用网格模式处理:O(N^2)
 *
 * 算法特点
 * 1. cell[i][j]为4行4列的网格,列为f i s h,行为h i s h的网格
 * 1. 本例问题采用网格计算有个公式:cell[i][j] = 0 or (cell[i-1][j-1]+1),
 *    即：当i和j字符不同时,取值为0;如果相同时,即为左上角的邻居值加1
 *
 * 思考:
 *
 * */


constexpr int COL=4;//行数
constexpr int ROW=4;//列数

void LongestComSunStr(){
    std::string a="hish";//示例字符串
    std::string b="fish";

    int cell[COL+1][ROW+1]={0};//多一行一列为了和索引相对应

    int max=0;//最大值
    int startCol=0;//最大公共子串起使行
    int maxCol=0;//最大公共子串结束所在行
    int maxRow=0;//最大值公共子串结束所在列
    bool isFirst=true;
    for(int col=1;col<=COL;col++){
        for(int row=1;row<=ROW;row++){
            max = cell[col][row];
            if(b[col-1]==a[row-1]){//因为不相同的已提前初始化为0了
                cell[col][row] = cell[col-1][row-1]+1;
                if(isFirst){
                    startCol = col;//因为maxCol和maxRow是对称的
                    isFirst=false;
                }
            }

            if(cell[col][row]>max){
                max = cell[col][row];
                maxCol=col;
                maxRow=row;
            }
            std::cout<<cell[col][row]<<" ";//debug
        }
        std::cout<<std::endl;
    }

    std::cout<<a<<"和"<<b<<"最大公共子串长度:"<<max<<std::endl;
    std::cout<<"最大公共子串为:";
    for(int i=startCol-1;i<=maxCol-1;i++){
        std::cout<<b[i];
    }
    std::cout<<std::endl;
}

//动态规划------最长公共子串问题
int TestLongestComSunStr(){
    auto start = std::chrono::steady_clock::now();

    LongestComSunStr();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__THIEFBACKPACK__H__