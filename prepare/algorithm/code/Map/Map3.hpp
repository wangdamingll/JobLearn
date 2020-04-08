#ifndef __MAP3__H__
#define __MAP3__H__

#include <iostream>
#include <chrono>
#include <array>
using namespace std;


/*图遍历----深度优先搜索算法(DFS)-----有向图
 *
 * 问题描述:求城市地图之前2个城市的最短距离
 * 下面是一个由图(有向图)转换成的邻接矩阵存储的二维数组(邻接矩阵存储法)
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 上面和左边1 2 3 4 5是图的顶点(也就是各个城市)
 * 3. 下图二维数组中第i行第j列表示的就是顶点i到顶点j是否有边.大于0表示顶点i到j的距离，-表示没有边,这里我们将自己到自己(即i等于j)的距离设为0.
 *          1   2   3   4   5
 *
 *   1      0   2   -   -  10
 *   2      -   0   3   -   7
 *   3      4   -   0   4   -
 *   4      -   -   -   0   5
 *   5      -   -   3   -   0
 *
 *
 * 算法思想:
 * DFS主要思想就是:首先以一个未被访问过的顶点作为起始顶点,沿当前顶点的边走到未访问过的顶点;当没有未访问过的顶点时,则回到上一个顶点,继续试探访问别的顶点,
 * 直到所有的顶点都被访问过.显然,深度优先遍历是沿着图的某一条分支遍历直到末端,然后回溯,再沿着另一条进行同样的遍历,直到所有的顶点都被访问过为止.
 *
 * 思考:
 * 1. 图的遍历方法和迷宫问题(二维数组)遍历有不同,迷宫问题路线标记方法是将二维数组中的某一个点标记,而图遍历只需要标记某个顶点.
 *    同时尝试每一种可能时,不再是坐标点,而是图的每个顶点编号
 * 2. 由于图遍历采用DFS,此例是涉及路线问题,DFS回溯的时候需要将顶点取消标记
 * 3. 图遍历DFS参数不再是坐标了,而是图中某个顶点的编号
 * 4. 图遍历DFS结束条件是,在此例中,当找到目标顶点时,更新最短距离即可(这里额外需要输出最短路线图,可以用array模拟栈)
 * */

//存储生成的二维数组 记录图的顶点从索引1开始
int a3[6][6]={
        {0,0,0,0,0,0},
        {0,0,2,-1,-1,10},
        {0,-1,0,3,-1,7},
        {0,4,-1,0,4,-1},
        {0,-1,-1,-1,0,5},
        {0,-1,-1,3,-1,0}
};

int visit3[10]={0};//标记图中顶点是否被访问
int start3 = 0;//代表起始城市顶点
int n3=0;  //代表目标城市顶点
int min3=99999;//代表最短距离

std::array<int,6> stack={0}; //模拟栈 用于输出路线
int top =0;

void PrintMap3(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if(a3[i][j]>=0){
                std::cout<<" "<<a3[i][j]<<" ";
            }else{
                std::cout<<a3[i][j]<<" ";
            }

        }
        std::cout<<std::endl;
    }
}

//打印路线
void PrintPath(int dis){
    for(int i=0;i<top;i++){
        if(i==0){
            std::cout<<stack[i];
        }else{
            std::cout<<"->"<<stack[i];
        }
    }
    std::cout<<" dis="<<dis<<std::endl;
}

//cur顶点编号
void DFS3(int cur,int dis){
    if(cur == n3){ //代表已经达到目标城市顶点
        if(dis<min3){
            min3 = dis; //记录最短距离
            PrintPath(min3);//打印路线
        }
        //PrintPath(dis);//打印所有路线
        return;
    }

    //尝试每一种可能
    for(int k=1;k<=5;k++){
        if(a3[cur][k]>0 && visit3[k] == 0){//图中顶点可以通并且没有访问过
            visit3[k] = 1;  //标记
            stack[top++] = k; //加入路线
            DFS3(k,dis+a3[cur][k]);
            //涉及路线问题需要取消标记
            visit3[k] = 0;
            top--;
        }
    }
}

int TestDFS3(){
    auto start = std::chrono::steady_clock::now();
    PrintMap3();//打印地图

    std::cout<<"请输入开始的城市顶点:";
    std::cin>>start3;
    std::cout<<"请输入目标的城市顶点:";
    std::cin>>n3;

    visit1[start3] = 1;//标记
    stack[top++] = start3;//加入路线
    DFS3(start3,0);//从顶点start3开始遍历
    std::cout<<std::endl;

    std::cout<<"minDis:"<<min3<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP3__H__