#ifndef __DIJKSTRA2__H__
#define __DIJKSTRA2__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;


/* 图最短路径-----Dijkstra
 *
 * 问题描述:
 * 下面是一个由图(有向图)转换成的邻接矩阵存储的二维数组(邻接矩阵存储法),求指定一个顶点到其他各个顶点的最短路径(也就是单源最短路径问题)
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 上面和左边1 2 3 4 5 6是图的顶点
 * 3. 下图二维数组中第i行第j列表示的就是顶点i到顶点j是否有边.大于0表示有边，-表示没有边(下面用99999999表示),这里我们将自己到自己(即i等于j)设为0.
 *          1   2   3   4   5   6
 *
 *   1      0   1   12  -   -   -
 *   2      -   0   9   3   -   -
 *   3      -   -   0   -   5   -
 *   4      -   -   4   0   13  15
 *   5      -   -   -   -   0   4
 *   6      -   -   -   -   -   0
 *
 * 算法思想:
 * 每次找到离源点(本例子源点就是1号顶点)最近的一个顶点,然后以该顶点为中心进行扩展(通过边松弛),最终得到源点到其余所有点的最短路径
 *
 * 时间复杂度
 * 1. 用一般的图的邻接矩阵法存的话,时间复杂度为O(N^2)
 * 2. 对于稀疏图来说,用堆和邻接表存储法,可以将时间复杂度优化为O((M+N)logN),N为顶点数,M为边数.最坏的情况M等于N^2,那么O((M+N)logN)比O(N^2)大,但是一般来说边没有那么多,所以O((M+N)logN)比O(N^2)小很多
 *
 * 算法特点
 * 1. 可以求图中单源最短路问题
 * 2. 时间复杂度为O(N^2),可以优化为O((M+N)logN),N为顶点数,M为边数
 * 3. 图中边权不可以有负值

 * 思考:
 * 1. 需要一个集合标识已知最短路程集合P和未知最短路程集合Q,直到集合Q为空时停止
 * 2. 需要一个一维数组dis,记录源点s能到达其他顶点i的距离,到自己的距离为0,能直接到达的其他顶点i为d[i]为a2[s][i],不能到达的设为无穷大
 * 3. 每次集合Q中选择离源点s最近的顶点u(dis[u]在一维数组中最小),并考察所有以顶点u为起点,对每条边进行松弛操作,如果存在一条从u->v的边,
 *    使得dis[v] > (dis[u] + a2[u][v]), 则更新dis[v];
 *
 * */

//存储生成的二维数组 记录图的顶点从索引1开始 用于多源最短路
static int a2[7][7] = {
        {0,0,0,0,0,0,0},
        {0,0,1,12,99999999,99999999,99999999},
        {0,99999999,0,9,3,99999999,99999999},
        {0,99999999,99999999,0,99999999,5,99999999},
        {0,99999999,99999999,4,0,13,15},
        {0,99999999,99999999,99999999,99999999,0,4},
        {0,99999999,99999999,99999999,99999999,99999999,0}
};

void PrintMap2()
{
    for(int i=1; i <= 6; i++)
    {
        for(int j = 1; j <= 6; j++)
        {
            if(a2[i][j] != 99999999)
            {
                std::cout<<"       "<<a2[i][j]<<" ";
            }else
            {
                std::cout<<a2[i][j]<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

//邻接矩阵存储---未优化O(N^2)
void Dijkstra21()
{
    PrintMap2(); //原始地图

    constexpr int n2 = 6;      //顶点数量本例为6
    int visit[n2 + 1] = {0};   //标识顶点i是不是已经知道最短距离
    std::vector<int> path[n2 + 1];//记录路线

    //dis初始化赋值,这里直接以1号顶点为源点s
    int dis[n2 + 1] = {0};
    for(int i = 1; i <= n2; i++)
    {
        dis[i] = a2[1][i];
        path[i].emplace_back(1);//路线起点
    }

    visit[1] = 1; //1号顶点已经知道最短距离了,为0
    int min = 0;
    int u2 = 0;  //u的顶点编号
    for(int i = 1; i <= n2 - 1; i++)//为什么循环n2-1次,因为n2个顶点,由于1号顶点已经知道了最短距离为0,剩下n2-1个顶点是未知的
    {
        //找到离源点s最短距离顶点u,这里s为1号顶点
        min = 99999999;
        for(int j = 1; j <= n2; j++)
        {
            if(visit[j] == 0 && dis[j] < min) //该顶点必须是未知距离
            {
                min = dis[j];
                u2 = j;
            }
        }

        visit[u2] = 1;//u顶点确定最短距离了,加入集合P中

        //以u为起点,松弛所有出边
        for(int v2 = 1; v2 <= n2; v2++)
        {
            if(a2[u2][v2] < 99999999)//u->v有路线
            {
                if(dis[v2] > dis[u2] + a2[u2][v2])
                {
                    dis[v2] = dis[u2] + a2[u2][v2];
                    path[v2].push_back(u2);
                }
            }
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i = 1; i <= n2; i++)
    {
        std::cout<<"1->"<<i<<":"<< dis[i] << std::endl;
        std::cout<<"路线为:";
        for(auto it:path[i])
        {
            std::cout<<it<<"->";
        }
        std::cout<<i<<std::endl;
    }
    std::cout<<std::endl;
}

//----------------------------------------------------------------------
struct Info
{
    Info() = default;
    Info(int index,int dis):m_index(index),m_dis(dis){};

    bool operator <(const Info& another)const
    {
        return m_dis<another.m_dis;
    }

    bool operator >(const Info& another)const
    {
        return m_dis>another.m_dis;
    }

    int m_index {0};//顶点编号
    int m_dis  {0};//顶点距离
};

constexpr int n2 = 6; //顶点数量本例为6
int visit22[n2 + 1] = {0};//标识顶点i是不是已经知道最短距离
std::vector<Info> disV;//堆使用

//dis中获取最小值堆优化
//或者使用std::priority_queue 优先级队列优化
int GetMinElem()
{
    int index=0;
    int finish=false;

    do{
        std::pop_heap(disV.begin(), disV.end(), std::greater<Info>{});//将最小元素移动到末尾
        auto elem = disV.back();
        disV.pop_back();

        if(visit22[elem.m_index] == 0)//该顶点没有被处理过
        {
            index = elem.m_index;
            finish = true;
        }
    }while(!finish);
    return index;
}

//邻接矩阵存储---部分优化,使用堆
void Dijkstra22()
{
    PrintMap2();//原始地图

    //dis初始化赋值,这里直接以1号顶点为源点s
    int dis[n2 + 1] = {0};
    for(int i = 1; i <= n2; i++)
    {
        dis[i] = a2[1][i];
        disV.emplace_back(i, a2[1][i]);
    }

    std::make_heap(disV.begin(), disV.end(), std::greater<Info>{});//min heap

    visit22[1] = 1; //1号顶点已经知道最短距离了,为0

    int u2 = 0;  //u的顶点编号
    for(int i = 1; i <= n2 - 1; i++)//为什么循环n2-1次,因为n2个顶点,由于1号顶点已经知道了最短距离为0,剩下n2-1个顶点是未知的
    {
        //找到离源点s最短距离顶点u,这里s为1号顶点
        u2 = GetMinElem();//找到dis中离源点1最短距离的顶点u

        visit22[u2] = 1;//u顶点确定最短距离了,加入集合P中

        //以u为起点,松弛所有出边
        for(int v2 = 1; v2 <= n2; v2++)
        {
            if(a2[u2][v2] < 99999999)//u->v有路线
            {
                if(dis[v2] > dis[u2] + a2[u2][v2])
                {
                    dis[v2] = dis[u2] + a2[u2][v2];
                    //disV.push_back(Info{v2,dis[v2]});
                    disV.emplace_back(v2, dis[v2]);//v2相同但是dis[v2]不相同,这是2个对象,不会覆盖,这个函数不会出错
                    std::push_heap(disV.begin(),disV.end(), std::greater<Info>{});
                }
            }
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i = 1; i <= n2; i++)
    {
        std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
    }
    std::cout<<std::endl;
}

//单源最短路
int TestDijkstra2()
{
    auto start = std::chrono::steady_clock::now();

    Dijkstra21();//邻接矩阵存储---未优化O(N^2)

    Dijkstra22();//邻接矩阵存储---部分优化,使用堆

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__DIJKSTRA2__H__