#ifndef __MAP1__H__
#define __MAP1__H__

#include <iostream>
#include <chrono>
using namespace std;

/*图遍历----深度优先搜索算法(DFS)-----无向图
 *
 * 问题描述:
 * 下面是一个由图(无向图)转换成的邻接矩阵存储的二维数组(邻接矩阵存储法)
 * 说明:
 * 1. 上面和左边1 2 3 4 5是图的顶点
 * 2. 下图二维数组中第i行第j列表示的就是顶点i到顶点j是否有边.1表示有边，-表示没有边,这里我们将自己到自己(即i等于j)设为0.
 *          1   2   3   4   5
 *
 *   1      0   1   1   -   1
 *   2      1   0   -   1   -
 *   3      1   -   0   -   1
 *   4      -   1   -   0   -
 *   5      1   -   1   -   0
 *
 *
 * 算法思想:
 * DFS主要思想就是:首先以一个未被访问过的顶点作为起始顶点,沿当前顶点的边走到未访问过的顶点;当没有未访问过的顶点时,则回到上一个顶点,继续试探访问别的顶点,
 * 直到所有的顶点都被访问过.显然,深度优先遍历是沿着图的某一条分支遍历直到末端,然后回溯,再沿着另一条进行同样的遍历,直到所有的顶点都被访问过为止.
 *
 * 思考:
 * 1. 图的遍历方法和迷宫问题(二维数组)遍历有不同,迷宫问题路线标记方法是将二维数组中的某一个点标记,而图遍历只需要标记某个顶点.
 *    同时尝试每一种可能时,不再是坐标点,而是图的每个顶点
 * 2. 由于图遍历采用DFS,不涉及路线问题,DFS回溯的时候不需要将顶点取消标记
 * 3. 图遍历DFS参数不再是坐标了,而是图中某个顶点的坐标
 * 4. 图遍历DFS结束条件是访问完所有的顶点了
 * 5. 无向图生成的邻接矩阵二维数组沿着主对角线对齐
 * */

//存储生成的二维数组 记录图的顶点从索引1开始
int a1[6][6]={
        {0,0,1,1,-1,1},
        {0,1,0,-1,1,-1},
        {0,1,-1,0,-1,1},
        {0,-1,1,-1,0,-1},
        {0,1,-1,1,-1,0}
};

int visit1[10]={0};//标记图中顶点是否被访问
int sum=0; //统计访问图中顶点的个数

void PrintMap1(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(a1[i][j]>=0){
                std::cout<<" "<<a1[i][j]<<" ";
            }else{
                std::cout<<a1[i][j]<<" ";
            }

        }
        std::cout<<std::endl;
    }
}

//cur顶点编号
void DFS1(int cur){
#if 0
    sum++;//只要访问过一个顶点就加1
    if(sum>5) {//大于顶点数量
        return;
    }
    std::cout<<cur<<" ";
#else
    std::cout<<cur<<" ";
    if(cur == 5){ //visit1表示了顶点是否被访问,访问过的顶点不会再次DFS1进入,所以cur等于5(等于图节点序号最大的)就表示已经遍历结束
        return;
    }
#endif


    //尝试每一种可能
    for(int k=1;k<=5;k++){
        if(a1[cur][k]==1 && visit1[k] == 0){//图中顶点可以通并且没有访问过
            visit1[k] = 1;
            DFS1(k);
            //不用取消标记
        }
    }
}

int TestDFS1(){
    auto start = std::chrono::steady_clock::now();

    PrintMap1();//打印地图

    visit1[1] = 1;//标记
    DFS1(1);//从顶点1开始遍历
    std::cout<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP1__H__