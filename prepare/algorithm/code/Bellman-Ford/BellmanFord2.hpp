#ifndef __BELLMAN_FORD2__H__
#define __BELLMAN_FORD2__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

/* 图最短路径-----Bellman-Ford
 *
 * 问题描述:
 * 下面是一个由图(有向图)转换成的邻接表存储的源数据,求指定一个顶点到其他各个顶点的最短路径(也就是单源最短路径问题)
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 第一行两个整数n m,n表示顶点个数(顶点编号为1~n),m表示边的条数. 接下来m行,每行有3个数x y z,表示顶点x到顶点y的边的权值为z
 *  6 9
 *  1 2 1
 *  1 3 12
 *  2 3 9
 *  2 4 3
 *  3 5 5
 *  4 3 4
 *  4 5 13
 *  4 6 15
 *  5 6 4
 *
 * 算法思想:
 * 一句话概括:对所有的边进行n-1次"松弛"操作(n为顶点数量)(因为在一个含有n个顶点的图中,任意两点之间的最短路径最多包含n-1边)
 *
 * 时间复杂度
 * 1. 未使用队列优化过的:O(NM),N为顶点 M为边
 * 2. 使用队列优化过的,最坏的时间复杂度是O(NM),N为顶点 M为边
 *
 * 特点
 * 1. 是一个无论是思想上还是代码实现上都堪称完美的最短路算法,核心代码只有4行
 * 2. 可以处理带有负权边的图
 * 3. 经常会在未达到n-1轮松弛前就已经计算出最短路(最多进行n-1轮边的松弛操作,n为顶点数量)
 *
 * 优化
 * 1. 经常会在未达到n-1轮松弛前就已经计算出最短路,所以这时可以跳出循环,做优化
 * 2. 可以使用队列进行优化:每次仅对最短路程发生变化了的点的相邻边执行松弛操作,使用队列保存这些最短路程变化了的点
 *
 * 思考:
 *
 * */

//为方便这里就直接把上图的行数据初始化了
constexpr int n2=6; //图的顶点数量(上面的数据)
constexpr int m2=9; //图的边数量(上面的数据)

//比m大1 分别存储顶点i到顶点j的权值,这里直接初始化上图数据
static int u2[m2+1]={0,1,1, 2,2,3,4,4, 4, 5};//顶点i
static int v2[m2+1]={0,2,3, 3,4,5,3,5, 6, 6};//顶点j
static int w2[m2+1]={0,1,12,9,3,5,4,13,15,4};//权值

//比n大1 分别存储编号i的第一条边的编号和编号i的边的下一条边的编号
int first2[n2+1]={0};
//比m大1
int next2[m2+1]={0};

int visit2[n2+1]={0};//标识顶点是否最短距离已知

//邻接表存储
void StoreMap2(){
    //初始化first2数组
    for(auto& it : first2){
        it = -1;
    }

    //邻接表存储
    for(int i=1;i<=m2;i++){
        next2[i] = first2[u2[i]];
        first2[u2[i]] = i;
    }
}

//遍历邻接表的每一条边
void PrintMap2(){
    for(int i=1;i<=n2;i++){
        int k = first2[i]; //取出顶点
        while(k!=-1){
            std::cout<<u2[k]<<" "<<v2[k]<<" "<<w2[k]<<std::endl;
            k=next2[k];
        }
    }
}

//未优化
void BellmanFord2(){
    StoreMap2();//存储图
    PrintMap2();//打印图

    //Dijkstra算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n2+1]={99999999,0,99999999,99999999,99999999,99999999,99999999};

    //待完善


    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i=1;i<=n2;i++){
        std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
    }
    std::cout<<std::endl;
}

//单源最短路
int TestBellmanFord2(){
    auto start = std::chrono::steady_clock::now();

    BellmanFord2();//未优化

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__BELLMAN_FORD1__H__