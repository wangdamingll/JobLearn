#ifndef __THIEFBACKPACK__H__
#define __THIEFBACKPACK__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
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
 * 1. cell[i][j]为3行4列的网格,行为吉他 音响 笔记本电脑,列为1磅 2磅 3磅 4磅的网格
 * 1. 本例问题采用网格计算有个公式:cell[i][j] = std::max(cell[i-1][j],当前商品的价值+cell[i-1][j-当前商品的重量])
 *    即：第i行j列的网格值等于下面2个值中取最大值:
 *    上一个单元格的值;当前商品的价值加上剩余空间的最大价值
 *
 * 思考:
 *
 * */

//商品编号
enum class Goods{
    None=0,
    Jita,//吉他
    Sound,//音响
    Laptop//笔记本电脑
};

//网格对象
struct CellGrid{
    CellGrid() = default;
    CellGrid(Goods goodIndex1,int weight1,int value1):goodIndex(goodIndex1),weight(weight1),value(value1){}
    Goods goodIndex {Goods::None} ;//商品编号
    int weight {0};//重量
    int value {0};//价值
};

constexpr int COL=3;//行数
constexpr int ROW=4;//列数

void ThiefBackPack(){
    int cell[COL+1][ROW+1]={0};//多一行一列为了和索引相对应

    //初始化商品信息
    std::unordered_map<int,CellGrid> uMap;
    uMap[1]={Goods::Jita,1,1500};
    uMap[2]={Goods::Sound,4,3000};
    uMap[3]={Goods::Laptop,3,2000};

    //记录每个格子对应的商品组合
    std::vector<std::vector<Goods>> idV;
    idV.resize((COL+1)*(ROW+1));

    int max=0;//最大商品价值
    int maxCol=0;//最大值所在行
    int maxRow=0;//最大值所在列
    for(int col=1;col<=COL;col++){
        for(int row=1;row<=ROW;row++){
            max = cell[col][row];
            if(uMap[col].weight>row){//如果该商品的重量大于背包的重量的限制,则当前的值为上一行对应列对应列的值(上一行最大值)
                cell[col][row]=cell[col-1][row];
                idV[col*COL+row] = idV[(col-1)*COL+row];
            }else{//如果满足当前商品重量满足背包的限制
                int value = uMap[col].value + cell[col-1][row-uMap[col].weight];//当前商品的价值 + 背包剩余空间的最大价值
                cell[col][row]=std::max(cell[col-1][row],value);//上一行最大值和(当前商品的价值 + 背包剩余空间的最大价值)两个中取最大值
                if(cell[col-1][row]>value){//记录对应的商品组合
                    idV[col*COL+row] = idV[(col-1)*COL+row];
                }else{
                    idV[col*COL+row] = idV[(col-1)*COL+row];
                    idV[col*COL+row].emplace_back(static_cast<Goods>(col));
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

    std::cout<<"最大的商品价值:"<<max<<std::endl;
    std::cout<<"商品id为:";
    for(auto it:idV[maxCol*COL+maxRow]){
        std::cout<< static_cast<int>(it)<<" ";
    }
    std::cout<<std::endl;
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