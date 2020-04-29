#ifndef __TP_SORT2__H__
#define __TP_SORT2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/* 有向无环图-----拓扑排序---DFS
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
 *  1 0 0 //图有环测试数据
 *  0 4 0
 *
 * 时间复杂度:
 *  O(N+M),N为顶点数,M为边数(因为图广度搜索共处理N个顶点,将所有顶点的度都处理到0(其实就是边的数量))
 *
 * 算法步骤:
 * 1. 枚举所有顶点,将顶点入度为0的节点作为DFS的入口开始
 * 2. DFS主体:
 *   1) 首先将当前顶点加到结果集中,删除当前顶点的所有出边;
 *   2) 对当前节点的所有出边终点进行枚举,并将当前终点的入度减1,如果当前终点的入度为0,则对此节点继续递归; 
 *
 * 算法特点:
 * 1. 建立边的领接表关系
 * 2. 记录所有顶点的入度
 * 3. 使用图的深度优先搜索
 * 思考:
 *
 * */


namespace TPSort2{

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

//打印数据
void PrintEdge() {
    for(int i=0;i<N;i++){
        int size = adj[i].size();
        for(int j=0;j<size;j++){
            std::cout<<i<<"->"<<adj[i][j]<<std::endl;
        }
    }
}

//拓扑排序----DFS
void TPSort(int u){
    //基线条件:其实这里不一定会走这个条件
    if(result.size() == N){
        return;
    }

    result.push_back(u);//添加结果

    std::vector<int> uVector = std::move(adj[u]);//删除u的所有出边

    for(auto it:uVector){
        if(--inDegree[it]==0){ //当顶点入度为0时继续递归
            TPSort(it);
        }
    }
}

int TestTPSort(){
    auto start = std::chrono::steady_clock::now();

    AddEdge(5,2);
    AddEdge(5,0);
    AddEdge(4,0);
    AddEdge(4,1);
    AddEdge(2,3);
    AddEdge(3,1);

    //有环测试边
//    AddEdge(1,0);
//    AddEdge(0,4);

    PrintEdge();

    //从入度为0的节点开始
    for(int i=0;i<N;i++){
        if(inDegree[i]==0){
            TPSort(i);//拓扑排序----DFS
        }
    }

    if(result.size()==N){
        std::cout<<"拓扑排序成功"<<std::endl;
    }else{
        std::cout<<"拓扑排序失败:图有环"<<std::endl;
        return 0;
    }
    for(auto it:result){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}
}

#endif //__TP_SORT2__H__