#ifndef __MAP2__H__
#define __MAP2__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;


/*图遍历----广度游戏搜索算法(BFS)-----无向图
 *
 * 问题描述:
 * 下面是一个由图(无向图)转换成的邻接矩阵存储的二维数组(邻接矩阵存储法)
 * 说明:
 * 1. 无向图的概念
 * 边没有方向的图称为无向图
 * 2. 上面和左边1 2 3 4 5是图的顶点
 * 3. 下图二维数组中第i行第j列表示的就是顶点i到顶点j是否有边.1表示有边，-表示没有边,这里我们将自己到自己(即i等于j)设为0.
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
 * BFS的主要思想就是:首先以一个未被访问过的顶点作为起始顶点,访问其所有相邻的顶点,然后对每个相邻的顶点,再访问它们相邻的未被访问过的顶点,直到所有顶
 * 点都被访问过,遍历结束.
 *
 * 算法特点
 * 1. 相同操作数,广搜时间复杂度小
 * 2. 广搜更加适合所有边的权值相同的情况
 *
 * 思考:
 * 1. 图的遍历方法和迷宫问题(二维数组)遍历有不同,迷宫问题路线标记方法是将二维数组中的某一个点标记,而图遍历只需要标记某个顶点.
 *    同时尝试每一种可能时,不再是坐标点,而是图的每个顶点
 * 2. 由于图遍历采用BFS,BFS标记点只会一次,不存在取不取消标记的问题
 * 3. 图遍历BFS结束条件是访问完所有的顶点了(队列为空)
 * 4. 无向图生成的邻接矩阵二维数组沿着主对角线对齐
 * */

//存储生成的二维数组 记录图的顶点从索引1开始
int a2[6][6]={
        {0,0,0,0,0,0},
        {0,0,1,1,-1,1},
        {0,1,0,-1,1,-1},
        {0,1,-1,0,-1,1},
        {0,-1,1,-1,0,-1},
        {0,1,-1,1,-1,0}
};

int visit2[10]={0};//标记图中顶点是否被访问

void PrintMap2(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if(a1[i][j]>=0){
                std::cout<<" "<<a1[i][j]<<" ";
            }else{
                std::cout<<a1[i][j]<<" ";
            }

        }
        std::cout<<std::endl;
    }
}

void BFS2(){
    std::queue<int>  que; //这里不再用std::array模拟队列了 直接使用队列

    visit2[1] = 1;//1号标记
    que.push(1);//入队列

    while(!que.empty()){//队列不为空
        int cur = que.front();//取出当前图顶点编号
        que.pop();

        std::cout<<cur<<" ";

        if(cur > 5){//当前编号大于图顶点最大的序号
            break;//
        }

        //进行扩展
        for(int k=1;k<=5;k++){
            if(a2[cur][k]==1 && visit2[k]==0){//图顶点能通并且没有被访问过
                visit2[k] = 1; //标记
                que.push(k);//入队列
            }
        }
    }

    std::cout<<std::endl;
}

int TestBFS2(){
    auto start = std::chrono::steady_clock::now();

    PrintMap2();//打印地图

    BFS2();//广搜

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP2__H__