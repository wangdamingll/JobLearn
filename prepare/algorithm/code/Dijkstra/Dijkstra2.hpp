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
 * 最开始只允许经过1号顶点进行中转，接下来只允许经过1和2号顶点进行中转……允许经过1~n号所有顶点进行中转,求任意两点之间的最短路程,
 * 用一句话概括就是:从i号顶点到j号顶点只经过前k号点的最短路程,其实这是一种"动态规划"的思想.
 * 也就是求i和j之间的最短路程,就是把所有的顶点都引入,求i->k1->k2->..->kn->j的最短路程
 *
 * 思考:
 * 1. 时间复杂度:O(n^3)
 * 2. 边权允许负值,但是不能有负权回路
 * 3. 如果对时间不敏感,用这个算法更简单,更容易实现
 * 4. 事前需评估一下2个城市之间的最大距离,不要出现溢出的现象
 * */

//存储生成的二维数组 记录图的顶点从索引1开始 用于多源最短路
int a1[5][5]={
        {0,0,0,0,0},
        {0,0,2,6,4},
        {0,99999999,0,3,99999999},
        {0,7,99999999,0,1},
        {0,5,99999999,12,0},
};

void PrintMap1(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(a1[i][j]!=99999999){
                std::cout<<"       "<<a1[i][j]<<" ";
            }else{
                std::cout<<a1[i][j]<<" ";
            }

        }
        std::cout<<std::endl;
    }
}

//多源最短路
int TestFWS1(){
    auto start = std::chrono::steady_clock::now();
    PrintMap1();//打印原始地图
    std::cout<<"----------------------------------------"<<std::endl;

    //在i和j中间引入所有图的顶点
    for(int k=1;k<=4;k++){ //中间节点
        for(int i=1;i<=4;i++){//起点
            for(int j=1;j<=4;j++){//终点
                if(a1[i][j]>a1[i][k]+a1[k][j]){
                    a1[i][j] = a1[i][k]+a1[k][j];//直接在原图中更新最短路程
                }
            }
        }
    }

    PrintMap1();//打印更新后最短路径的地图

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

//单源最短路
int TestFWS2(){
    auto start = std::chrono::steady_clock::now();
    std::cout<<"----------------------------------------"<<std::endl;

    std::cout<<"请输入图源点编号,求出此源点能到达城市的最短路程:";
    int n = 0;
    std::cin>>n;

    int min1=999999;//最短路径
    int index1=0;   //能到达的最短路程的城市编号
    for(int i=1;i<=4;i++){//终点
        if(a1[n][i]!=0 && a1[n][i]<min1){
            min1 = a1[n][i];
            index1 = i;
        }
    }

    std::cout<<"源点"<<n<<"能到达的最短路程的城市是:"<<index1<<",最短路程是:"<<min1<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__DIJKSTRA2__H__