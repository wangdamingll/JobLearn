#ifndef __MAP_CUT_POINT1__H__
#define __MAP_CUT_POINT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*图的割点-----tarjan算法
 *
 * 问题描述:
 * 求图的割点
 *
 * 说明:
 * 1. 无向图的概念
 * 边无方向的图称为无向图
 * 2. 第一行两个整数n m,n表示城市个数(城市编号为1~n),m表示道路条数. 接下来m行,每行有3个数x y z,表示从城市x到城市y所需的银子数量z
 *  6 7      //注意注意是无向图
 *  1 4 1
 *  1 3 1
 *  4 2 1
 *  3 2 1
 *  2 5 1
 *  2 6 1
 *  5 6 1
 *  4 1 1   //和上面数据对称
 *  3 1 1
 *  2 4 1
 *  2 3 1
 *  5 2 1
 *  6 2 1
 *  6 5 1
 *
 * 时间复杂度:
 * 1. 深度优先遍历或广度优先遍历:O(N(N+M))
 * 2. 本例割点算法:
 *  用邻接矩阵存储:O(N^2)
 *  用邻接表存储:O(N+M)
 *
 * 算法特点:
 * 1. 需要用DFS遍历图的所有顶点,记录num[顶点编号] = 顶点深度遍历时间戳
 * 2. 当遍历到顶点u时,枚举顶点u的所有出边,比如v,如何知道v不经过父节点u能否回到祖先节点呢?对子节点v再次DFS
 * 3. 需要记录每个子节点v在不经过父节点u的情况下,能够回到的最小时间戳
 * 4. v回溯的时候判断获取当前节点的low[u]=min(low[u],low[v]),如果low[v]>=num[u],表示v不能不经过u回到祖先,即u为割点
 *
 * 思考:
 * 1. 图的割点可以用DFS或BFS处理:依次删除每个顶点,然后用DFS或者BFS检查图是否连通,若图不在连通,则该顶点是图的割点,但是此方法时间复杂度比较高
 * 2. 图的数据可以用邻接矩阵,也可以用邻接表存储,本例割点算法如果实际应用,建议采用邻接表方法,时间复杂度比较低
 * */


constexpr int n2 = 6;//
constexpr int m2 = 14;//

//以下为了方便,直接初始化了
int u2[m2+1] ={0,1,1,4,3,2,2,5, 4,3,2,2,5,6,6};
int v2[m2+1] ={0,4,3,2,2,5,6,6, 1,1,4,3,2,2,5};
int w2[m2+1] ={0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1};

int first2[n2+1]={0}; //存储城市编号
int next2[m2+1] ={0};//存储边

int TestMapCutPoint1(){
    auto start = std::chrono::steady_clock::now();


    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_CUT_POINT1__H__