#ifndef __TSP__H__
#define __TSP__H__

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;


/* NPC问题-----旅行商问题
 *
 * 问题描述:
 * 有一个旅行商要前往5个不同的城市,他需要找出前往这5个城市的最短路径.
 *
 * 说明:
 * 下面用无向图来描述问题:
 * 1. 第一行两个整数n m,n表示顶点个数(顶点编号为1~n),m表示边的条数. 接下来m行,每行有3个数x y z,表示顶点x到顶点y的边的权值为z
 *  5 14
 *  1 2 1
 *  1 3 12
 *  2 3 9
 *  2 4 3
 *  3 5 5
 *  4 3 4
 *  4 5 13
 *  2 1 1   //这里为方便起见,以边权相同处理,也就是无向图
 *  3 1 12
 *  3 2 9
 *  4 2 3
 *  5 3 5
 *  3 4 4
 *  5 4 13
 *
 * 算法思想:
 * NPC问题----旅行商问题,无法用精确的算法求解,因为当城市比较多时,时间复杂度为O(N!).这里可以用近似算法中的贪婪算法求解:
 * 因为旅行商可以从任意城市开始,所以这里任意选择一个城市起点,借助Dijkstra算法进行求近似解
 *
 * 时间复杂度
 * 1. 旅行商问题时间复杂度为:O(N!)
 * 2. 采用Dijkstra算法求近似解,用堆和邻接表存储法,可以将时间复杂度优化为O((M+N)logN),N为顶点数,M为边数.
 *
 * 算法特点
 * 1. 借助Dijkstra算法求近似解

 * 思考:
 * 1. 旅行商问题是有向图模型,且A到B和B到A极有可能权不一样,这里为方便起见,以权相同处理.
 * */

struct Edge{
    Edge()= default;
    Edge(int u1,int v1,int w1):u(u1),v(v1),w(w1){}
    int u {0};//出边点
    int v {0};//终边点
    int w {0};//权值
};

struct HeapInfo{
    HeapInfo() = default;
    HeapInfo(int index,int dis):m_index(index),m_dis(dis){};

    bool operator <(const HeapInfo& another)const{
        return m_dis<another.m_dis;
    }

    bool operator >(const HeapInfo& another)const{
        return m_dis>another.m_dis;
    }

    int m_index {0};//顶点编号
    int m_dis  {0};//顶点距离
};

constexpr int n=5; //图的顶点数量(上面的数据)

int visit[n+1]={0};//标识顶点是否最短距离已知
std::vector<HeapInfo> disV;//堆优化使用

std::vector<Edge> adj[n+1];//邻接表存储数据
std::vector<int> path[n+1];//记录路线

//邻接表存储
void StoreMap(){
    adj[1].emplace_back(Edge {1,2,1});
    adj[1].emplace_back(Edge {1,3,12});
    adj[2].emplace_back(Edge {2,3,9});
    adj[2].emplace_back(Edge {2,4,3});
    adj[3].emplace_back(Edge {3,5,5});
    adj[4].emplace_back(Edge {4,3,4});
    adj[4].emplace_back(Edge {4,5,13});
    adj[2].emplace_back(Edge {2,1,1});
    adj[3].emplace_back(Edge {3,1,12});
    adj[3].emplace_back(Edge {3,2,9});
    adj[4].emplace_back(Edge {4,2,3});
    adj[5].emplace_back(Edge {5,3,5});
    adj[3].emplace_back(Edge {3,4,4});
    adj[5].emplace_back(Edge {5,4,13});
}

//遍历邻接表的每一条边
void PrintMap(){
    for(auto it:adj){
        for(auto iter:it){
            std::cout<<iter.u<<" "<<iter.v<<" "<<iter.w<<std::endl;
        }
    }
}


//dis中获取最小值堆优化
//或者使用std::priority_queue 优先级队列优化
int GetMinElem(){
    int index=0;
    int finish=false;
    do{
        std::pop_heap(disV.begin(),disV.end(),std::greater<HeapInfo>{});//将最小元素移动到末尾
        auto elem = disV.back();
        disV.pop_back();

        if(visit[elem.m_index]==0){//该顶点没有被处理过
            index = elem.m_index;
            finish = true;
        }
    }while(!finish);
    return index;
}

//NPC问题----旅行商问题
void TSP(){
    StoreMap();//存储图
    PrintMap();//打印图

    //旅行商问题,这里采用Dijskstra算法作为近似算法求解,选择1号顶为起点
    //Dijkstra算法 这里以1号顶点为源点s,顶点s不能直接到达的依旧用99999999表示
    //初始化dis
    int dis[n+1]={99999999,0,99999999,99999999,99999999,99999999};
    for(auto it : adj[1]){
        dis[it.v] = it.w;
        disV.emplace_back(HeapInfo{it.v,it.w});//堆
    }
    for(int i=1;i<=n;i++){
        path[i].emplace_back(1);//初始化路劲起点
    }

    std::make_heap(disV.begin(),disV.end(),std::greater<HeapInfo>{});//初始化 min heap

    visit[1] = 1; //表示顶点1的最短距离已知

    int u =0;
    for(int i=1;i<=n-1;i++){//松弛dis中的所有顶点
        //找到dis中距离顶点1最短距离的顶点编号
        u=GetMinElem();

        //松弛所有u的出边
        for(auto it:adj[u]){//邻接表存储
            if(dis[it.v]>dis[u]+it.w){
                dis[it.v] = dis[u]+it.w;//更新dis
                disV.emplace_back(HeapInfo{it.v,dis[it.v]});//进行堆排序
                std::push_heap(disV.begin(),disV.end(),std::greater<HeapInfo>{});
                path[it.v].emplace_back(it.u);//添加路径
            }
        }
    }

    //输出最终结果
    std::cout<<"顶点1能够到达其他顶点的距离为:"<<std::endl;
    for(int i=1;i<=n;i++){
        std::cout<<"1->"<<i<<":"<<dis[i]<<std::endl;
        std::cout<<"路线:";
        for(auto it:path[i]){
            std::cout<<it<<"->";
        }
        std::cout<<i<<std::endl;
    }
    std::cout<<std::endl;
}

//NPC问题----旅行商问题
int TestTSP(){
    auto start = std::chrono::steady_clock::now();

    TSP();//NPC问题----旅行商问题

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__TSP__H__