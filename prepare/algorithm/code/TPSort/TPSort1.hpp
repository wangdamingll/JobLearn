#ifndef __TP_SORT1__H__
#define __TP_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/* 有向无环图-----拓扑排序---BFS
 *
 * 问题描述:
 * 求有向无环图的拓扑排序结果
 *
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 第一行两个整数n m,n表示图的顶点个数,m表示图的边数. 接下来m行,每行有3个数x y z,表示从顶点x到顶点y的边权
 *  6 6      //注意这里图的边权为0(这里用不到)
 *  5 2 0    //顶点为6个: 0 1 2 3 4 5,将顶点初始编号为0,也是为了和索引对应,好理解
 *  5 0 0
 *  4 0 0
 *  4 1 0
 *  2 3 0
 *  3 1 0
 *
 * 时间复杂度:
 *  O(N+M),N为顶点数,M为边数(因为图广度搜索共处理N个顶点,将所有顶点的度都处理到0(其实就是边的数量))
 *
 * 算法步骤:
 * 1. 定义一个队列Q,并把所有入度为0的结点加入队列.
 * 2. 取队首结点,访问输出.然后删除所有从它出发的边,并令这些边到达的顶点的入度减1,如果某个顶点的入度减为0,则将其加入队列.
 * 3. 重复进行2操作,直到队列为空.如果队列为空时入过队的结点数恰好为N,说明拓扑排序成功,图为有向无环图;否则,拓扑排序失败,图G有环.
 * 
 * 算法特点:
 * 1. 建立边的领接表关系
 * 2. 记录所有顶点的入度
 * 3. 使用图的广度优先搜索
 * 思考:
 *
 * */

namespace TPSort1{

constexpr int N = 6;//顶点数
std::vector<int> adj[N]; //领接表
int inDegree[N]={0};//每个顶点的入度
std::queue<int> Q;//图的广度优先遍历使用
std::vector<int> result;//保存最终结果

//保存领接表数据(u->v)
void AddEdge(int u,int v){
    adj[u].push_back(v);//边关系
    ++inDegree[v];//入度加1
}

//打印地图
void PrintEdge() {
    for(int i=0;i<N;i++){
        int size = adj[i].size();
        for(int j=0;j<size;j++){
            std::cout<<i<<"->"<<adj[i][j]<<std::endl;
        }
    }
}

//拓扑排序----BFS
void TPSort(){
    AddEdge(5,2);
    AddEdge(5,0);
    AddEdge(4,0);
    AddEdge(4,1);
    AddEdge(2,3);
    AddEdge(3,1);

    PrintEdge();

    //拓扑排序核心代码部分
    //将入度为0的节点加入队列
    for(int i=0;i<N;i++){
        if(inDegree[i]==0){
            Q.push(i);
        }
    }

    while(!Q.empty()){
        int u = Q.front(); //取出度为0的节点
        Q.pop();

        result.push_back(u);//保存结果

        for(const auto& it:adj[u]){//删除节点u所有的出边的顶点入度减1,如果该节点的入度为0,则加入队列
            if(--inDegree[it]==0){
                Q.push(it);
            }
        }
        adj[u].clear();//删除u的所有出边
    }

    if(result.size() == N){
        std::cout<<"拓扑排序成功"<<std::endl;
        for(auto it:result){
            std::cout<<it<<" ";
        }
        std::cout<<std::endl;

    }else{
        std::cout<<"拓扑排序失败,图有环"<<std::endl;
    }

}

int TestTPSort(){
    auto start = std::chrono::steady_clock::now();

    TPSort();//拓扑排序----BFS

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}
}

#endif //__TP_SORT1__H__