#ifndef __BELLMAN_FORD2__H__
#define __BELLMAN_FORD2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <queue>
using namespace std;

/* 图最短路径-----Bellman-Ford
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
constexpr int n2=5; //图的顶点数量(上面的数据)
constexpr int m2=5; //图的边数量(上面的数据)

//比m大1 分别存储顶点i到顶点j的权值,这里直接初始化上图数据
static int u2[m2+1]={0,2,1, 1,4,3};//顶点i
static int v2[m2+1]={0,3,2, 5,5,4};//顶点j
static int w2[m2+1]={0,2,-3,5,2,3};//权值

//比n大1 分别存储编号i的第一条边的编号和编号i的边的下一条边的编号
int first2[n2+1]={0};
//比m大1
int next2[m2+1]={0};

std::queue<int> queue2;
int visit2[n2+1]={0};//表示顶点是否在队列中

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
void BellmanFord21(){
    StoreMap2();//存储图
    PrintMap2();//打印图

    //Bellman-Ford算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n2+1]={99999999,0,99999999,99999999,99999999,99999999};

    //Bellman-Ford核心代码:对所有边进行n-1次松弛
    for(int i=1;i<=n2-1;i++){ //最多n-1次松弛
        for(int j=1;j<=m2;j++){ //所有边
            if(dis[v2[j]]>dis[u2[j]]+w2[j]){
                dis[v2[j]]=dis[u2[j]]+w2[j];
            }
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i=1;i<=n2;i++){
        std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
    }
    std::cout<<std::endl;
}

//优化1:如果第k次松弛后,dis和结果和第K-1次一样,那就退出循环,因为目的以达到
void BellmanFord22(){
    StoreMap2();//存储图
    PrintMap2();//打印图

    //Bellman-Ford算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n2+1]={99999999,0,99999999,99999999,99999999,99999999};
    int bak[n2+1]={0};//每次松弛备份dis做比较

    //Bellman-Ford核心代码:对所有边进行n-1次松弛
    for(int i=1;i<=n2-1;i++){ //最多n-1次松弛
        for(int k2=1;k2<=n2;k2++){//备份dis
            bak[k2] = dis[k2];
        }
        for(int j=1;j<=m2;j++){ //所有边
            if(dis[v2[j]]>dis[u2[j]]+w2[j]){
                dis[v2[j]]=dis[u2[j]]+w2[j];
            }
        }

        //优化
        int check=0;
        for(int tmp=1;tmp<=n2;tmp++){
            if(bak[tmp]!=dis[tmp]){
                check=1;
                break;
            }
        }
        if(check==0){ //如果dis数组没有更新,则退出循环
            break;
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i=1;i<=n2;i++){
        std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
    }
    std::cout<<std::endl;
}


//优化2:使用队列进行优化:每次仅对最短路程发生变化了的点的相邻边执行松弛操作,使用队列保存这些最短路程变化了的点
void BellmanFord23(){
    StoreMap2();//存储图
    PrintMap2();//打印图

    //Bellman-Ford算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis,和Dijkstra算法不同,dis不在需要初始化到源点s的直接边的估计值
    int dis[n2+1]={99999999,0,99999999,99999999,99999999,99999999};

    //Bellman-Ford队列优化
    queue2.push(1); //源点1入队列
    visit2[1] = 1;      //标记源点1已经在队列中

    while(!queue2.empty()){
        int i = queue2.front(); //取出顶点

        int k2 = first2[i]; //邻接表遍历顶点i所有的出边,进行松弛操作, k2是顶点i在上面源数据中最后出现所在的行
        while(k2!=-1){
            //Bellman-Ford核心代码
            if(dis[v2[k2]]>dis[u2[k2]]+w2[k2]){
                dis[v2[k2]]=dis[u2[k2]]+w2[k2];

                if(visit2[v2[k2]] == 0){ //该顶点不在队列中,其实如果重复入队列没有必要
                    queue2.push(v2[k2]); //入队列
                    visit2[v2[k2]] =1;  //标记
                }
            }
            k2 = next2[k2];//顶点i下一条数据所在的行数
        }

        queue2.pop();   //出队列
        visit2[i] =0;   //取消标记
    }

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

    BellmanFord21();//未优化

    BellmanFord22();//如果第k次松弛后,dis和结果和第K-1次一样,那就退出循环,因为目的以达到

    BellmanFord23();//使用队列进行优化:每次仅对最短路程发生变化了的点的相邻边执行松弛操作,使用队列保存这些最短路程变化了的点

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__BELLMAN_FORD2__H__