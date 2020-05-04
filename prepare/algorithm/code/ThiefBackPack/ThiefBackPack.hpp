#ifndef __THIEFBACKPACK__H__
#define __THIEFBACKPACK__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;


/* NPC问题-----背包问题:小偷偷东西
 *
 * 问题描述:
 * 假如你是一个小偷,背着一个可装4磅东西的背包,你可盗窃的商品有如下四件:
 * 音响,3000美元,4磅
 * 笔记本电脑,2000美元,3磅
 * 吉他,1500美元,1磅
 * 为了使盗窃的商品价值最高,你会选择哪些商品?
 *
 * 说明:
 *
 * 算法思想:
 * NPC问题----背包问题,可以使用动态规划求得最优解.
 *
 * 时间复杂度
 * 1. 采用网格模式处理:O(N^2)
 *
 * 算法特点
 * 1. 本例问题采用网格计算有个公式:cell[i][j] = std::max(cell[i-1][j],当前商品的价值+cell[i-1][j-当前商品的重量])
 *    即：第i行j列的网格值等于下面2个值中取最大值:
 *    上一个单元格的值;当前商品的价值加上剩余空间的最大价值
 *
 * 思考:
 *
 * */

void ThiefBackPack(){

}

//动态规划------背包问题:小偷偷东西
int TestThiefBackPack(){
    auto start = std::chrono::steady_clock::now();

    ThiefBackPack();//动态规划------背包问题:小偷偷东西

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__THIEFBACKPACK__H__