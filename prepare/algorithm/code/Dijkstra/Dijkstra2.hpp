#ifndef __DIJKSTRA2__H__
#define __DIJKSTRA2__H__

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;


/* 图最短路径-----Dijkstra(待完善)
 *
 * 问题描述:
 * 下面是一个由图(有向图)转换成的邻接矩阵存储的二维数组(邻接矩阵存储法),求任意两点之前的最短路径(多源最短路问题)
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 上面和左边1 2 3 4 5是图的顶点
 * 3. 下图二维数组中第i行第j列表示的就是顶点i到顶点j是否有边.1表示有边，-表示没有边(下面用99999999表示),这里我们将自己到自己(即i等于j)设为0.
 *          1   2   3   4
 *
 *   1      0   2   6   4
 *   2      -   0   3   -
 *   3      7   -   0   1
 *   4      5   -   12  0
 *
 *
 * 算法思想:
 *
 * 思考:
 *
 * */

//存储生成的二维数组 记录图的顶点从索引1开始 用于多源最短路
int a1[5][5]={
        {0,0,0,0,0},
        {0,0,2,6,4},
        {0,99999999,0,3,99999999},
        {0,7,99999999,0,1},
        {0,5,99999999,12,0},
};

void PrintMap2(){




}

//未优化O(N^2)
void Dijkstra21(){


}

//部分优化,使用堆
void Dijkstra22(){


}

//单源最短路
int TestDijkstra2(){
    auto start = std::chrono::steady_clock::now();


    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__DIJKSTRA2__H__