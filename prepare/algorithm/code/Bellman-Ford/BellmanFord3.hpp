#ifndef __BELLMAN_FORD3__H__
#define __BELLMAN_FORD3__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <queue>
using namespace std;

/* 图有无负权回路-----Bellman-Ford
 *
 * 问题描述:
 * 下面是一个由图(有向图)转换成的邻接表存储的源数据,求指定一个顶点到其他各个顶点的最短路径(也就是单源最短路径问题)
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 第一行两个整数n m,n表示顶点个数(顶点编号为1~n),m表示边的条数. 接下来m行,每行有3个数x y z,表示顶点x到顶点y的边的权值为z
 *  5 5
 *  2 3 2
 *  1 2 -3
 *  1 5 5
 *  4 5 2
 *  3 4 3
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
constexpr int n3=5; //图的顶点数量(上面的数据)
constexpr int m3=5; //图的边数量(上面的数据)

//比m大1 分别存储顶点i到顶点j的权值,这里直接初始化上图数据
static int u3[m3+1]={0,2,1, 1,4,3};//顶点i
static int v3[m3+1]={0,3,2, 5,5,4};//顶点j
static int w3[m3+1]={0,2,-3,5,2,3};//权值

//比n大1 分别存储编号i的第一条边的编号和编号i的边的下一条边的编号
int first3[n3+1]={0};
//比m大1
int next3[m3+1]={0};

//邻接表存储
void StoreMap3(){
    //初始化first3数组
    for(auto& it : first3){
        it = -1;
    }

    //邻接表存储
    for(int i=1;i<=m3;i++){
        next3[i] = first3[u3[i]];
        first3[u3[i]] = i;
    }
}

//遍历邻接表的每一条边
void PrintMap3(){
    for(int i=1;i<=n3;i++){
        int k = first3[i]; //取出顶点
        while(k!=-1){
            std::cout<<u3[k]<<" "<<v3[k]<<" "<<w3[k]<<std::endl;
            k=next3[k];
        }
    }
}


void BellmanFord3(){
    StoreMap2();//存储图
    PrintMap2();//打印图

    //Bellman-Ford算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n3+1]={99999999,0,99999999,99999999,99999999,99999999};
    int bak[n3+1]={0};//每次松弛备份dis做比较

    //Bellman-Ford核心代码:对所有边进行n-1次松弛
    for(int i=1;i<=n3-1;i++){ //最多n-1次松弛
        for(int k3=1;k3<=n3;k3++){//备份dis
            bak[k3] = dis[k3];
        }
        for(int j=1;j<=m3;j++){ //所有边
            if(dis[v3[j]]>dis[u3[j]]+w3[j]){
                dis[v3[j]]=dis[u3[j]]+w3[j];
            }
        }

        //优化
        int check=0;
        for(int tmp=1;tmp<=n3;tmp++){
            if(bak[tmp]!=dis[tmp]){
                check=1;
                break;
            }
        }
        if(check==0){ //如果dis数组没有更新,则退出循环
            break;
        }
    }

    int flag = 0;
    for(int i=1;i<=m3;i++){
        if(dis[v3[i]]>dis[u3[i]]+w3[i]){
            flag=1;
        }
    }

    if(flag==1){
        std::cout<<"此图有负权循环"<<std::endl;
    }else{
        std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
        for(int i=1;i<=n3;i++){
            std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
        }
        std::cout<<std::endl;
    }
}


//判断图中有无负权回路
int TestBellmanFord3(){
    auto start = std::chrono::steady_clock::now();

    BellmanFord3();//判断图中有无负权回路

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__BELLMAN_FORD3__H__