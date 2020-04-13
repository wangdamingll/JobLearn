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
 *    使得dis[v]>(dis[u]+a2[u][v]),则更新dis[v];
 *
 * */

struct Info3{
    Info3() = default;
    Info3(int index,int dis):m_index(index),m_dis(dis){};

    bool operator <(const Info3& another)const{
        return m_dis<another.m_dis;
    }

    bool operator >(const Info3& another)const{
        return m_dis>another.m_dis;
    }

    int m_index {0};//顶点编号
    int m_dis  {0};//顶点距离
};

//为方便这里就直接把上图的行数据初始化了
constexpr int n3=6; //图的顶点数量(上面的数据)
constexpr int m3=9; //图的边数量(上面的数据)

//比m大1 分别存储顶点i到顶点j的权值,这里直接初始化上图数据
static int u3[m3+1]={0,1,1, 2,2,3,4,4, 4, 5};//顶点i
static int v3[m3+1]={0,2,3, 3,4,5,3,5, 6, 6};//顶点j
static int w3[m3+1]={0,1,12,9,3,5,4,13,15,4};//权值

//比n大1 分别存储编号i的第一条边的编号和编号i的边的下一条边的编号
int first3[n3+1]={0};
//比m大1
int next3[m3+1]={0};

int visit3[n3+1]={0};//标识顶点是否最短距离已知
std::vector<Info3> disV3;//堆优化使用

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


//dis中获取最小值堆优化
//或者使用std::priority_queue 优先级队列优化
int GetMinElem3(){
    int index =0;
    bool finish = false;
    std::make_heap(disV3.begin(),disV3.end(),std::greater<Info3>{});
    do{
        std::pop_heap(disV3.begin(),disV3.end(),std::greater<Info3>{});
        auto elem = disV3.back();
        disV3.pop_back();
        if(visit3[elem.m_index]==0){//没有被处理过的顶点
            index = elem.m_index;
            finish = true;
        }
    }while(!finish);
    return index;
}

//邻接接表存储---堆优化
void Dijkstra3(){
    StoreMap3();//存储图
    PrintMap3();//打印图

    //Dijkstra算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n3+1]={99999999,0,99999999,99999999,99999999,99999999,99999999};
    int k = first3[1];//取出1号顶点所在的行数(也就是上面源数据的1号顶点所在的行)
    while(k!=-1){
        dis[v3[k]]=w3[k];//取出1号顶点到顶点k的距离
        disV3.emplace_back(v3[k],w3[k]);
        k=next3[k];
    }

    visit3[1] = 1; //表示顶点1的最短距离已知

    int u =0;
    for(int i=1;i<=n3-1;i++){//松弛dis中的所有顶点
        //找到dis中距离顶点1最短距离的顶点编号
        u=GetMinElem3();

        visit3[u] = 1;//标记

        //对u的每条出边进行处理
        int k1 = first3[u];//取出u号顶点所在的行数(也就是上面源数据的u号顶点所在的行)
        while(k1!=-1){
            if(dis[v3[k1]]>dis[u] + w3[k1]){
                dis[v3[k1]]=dis[u] + w3[k1];
                disV3.emplace_back(v3[k1],dis[v3[k1]]);
            }
            k1=next3[k1];
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i=1;i<=n3;i++){
        std::cout<<"1->"<<i<<":"<<dis[i]<<" ";
    }
    std::cout<<std::endl;
}

//单源最短路
int TestBellmanFord2(){
    auto start = std::chrono::steady_clock::now();

    Dijkstra3();//Dijkstra优化-------堆优化和邻接表优化 时间复杂度O((M+N)logN)

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__BELLMAN_FORD1__H__