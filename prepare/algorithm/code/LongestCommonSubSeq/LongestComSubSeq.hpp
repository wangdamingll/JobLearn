#ifndef __LONGESTCOMSUBSEQ__H__
#define __LONGESTCOMSUBSEQ__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


/* 动态规划-------最长公共子序列问题
 *
 * 问题描述:
 * 假设不小心输入了fosh,当然没有这个词了,那么原本想输入fish还是fort呢?
 *
 * 说明:
 * fish fort和fosh的公共子串的长度都是为2,并不能区分,其实这里是求fish fort和和fosh的最长公共子序列了.
 *
 * 算法思想:
 * 求解最长公共子序列,可以使用动态规划求得最优解.
 *
 * 时间复杂度
 * 1. 采用网格模式处理:O(N^2)
 *
 * 算法特点
 * 1. cell[i][j]为4行4列的网格,行为f o s h,列为f i s h或者f o r t的网格
 * 1. 本例问题采用网格计算有个公式:cell[i][j] = (cell[i-1][j-1]+1) or std::max(cell[i-1][j],cell[i][j-1]),
 *    即：当i和j字符相同时,即为左上角的邻居值加1;如果不同时,为上方和左方中最大的那个
 *
 * 思考:
 *
 * */


constexpr int COL=4;//行数
constexpr int ROW=4;//列数

void SunSeq(std::string& colStr,std::string& rowStr){
    int cell[COL+1][ROW+1]={0};//多一行一列为了和索引相对应
    std::vector<char> cV;

    int max=0;
    for(int col=1;col<=COL;col++){
        for(int row=1;row<=ROW;row++){
            max = cell[col][row];
            if(rowStr[col-1]==colStr[row-1]){//相同,即为左上角邻居值加1
                cell[col][row] = cell[col-1][row-1]+1;
                cV.emplace_back(rowStr[col-1]);
            }else{//不相同,上方邻居和左方邻居选最大值
                cell[col][row] = std::max(cell[col-1][row],cell[col][row-1]);
            }
            if(cell[col][row]>max){
                max = cell[col][row];
            }
        }
    }

    std::cout<<"网格信息:"<<std::endl;
    std::cout<<"   ";
    for(auto it : rowStr){
        std::cout<<it<<"  ";
    }
    std::cout<<std::endl;
    for(int i=1;i<=COL;i++){
        std::cout<<colStr[i-1]<<"  ";
        for(int j=1;j<=ROW;j++){
            std::cout<<cell[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }

    std::cout<<colStr<<"和"<<rowStr<<"最大公共子序列:"<<max<<std::endl;
    std::cout<<"最大公共子序列为:";
    for(auto it :cV){
        std::cout<<it;
    }
    std::cout<<std::endl;
}


void LongestComSunSeq(){
    std::string a="fosh";//示例字符串
    std::string b="fort";
    std::string c="fish";
    SunSeq(b,a);
    std::cout<<"---------------"<<std::endl;
    SunSeq(c,a);

}

//动态规划------最长公共子串子序列问题
int TestLongestComSunSeq(){
    auto start = std::chrono::steady_clock::now();

    LongestComSunSeq();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__LONGESTCOMSUBSEQ__H__