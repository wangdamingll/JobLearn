#ifndef __BIPARTITE_MAP_MAX_MATCH1__H__
#define __BIPARTITE_MAP_MAX_MATCH1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*二分图最大匹配
 *
 * 问题描述:
 *
 *
 * 说明:
 * 1. 无向图的概念
 * 边无方向的图称为无向图
 * 2. 第一行两个整数n m,n表示图的顶点个数,m表示图的边数. 接下来m行,每行有3个数x y z,表示从顶点x到顶点y的边权
 *  6 14      //注意注意是无向图
 *  1 4 1
 *  1 3 1
 *  4 2 1
 *  3 2 1
 *  2 5 1
 *  5 6 1
 *  4 1 1   //和上面数据对称
 *  3 1 1
 *  2 4 1
 *  2 3 1
 *  5 2 1
 *  6 5 1
 *
 * 时间复杂度:
 *
 * 算法特点:
 *
 * 思考:
 *
 * */


constexpr int n1 = 6;//
constexpr int m1 = 12;//

//以下为了方便,直接初始化了
int u1[m1+1] ={0,1,1,4,3,2,5, 4,3,2,2,5,6};
int v1[m1+1] ={0,4,3,2,2,5,6, 1,1,4,3,2,5};
int w1[m1+1] ={0,1,1,1,1,1,1, 1,1,1,1,1,1};

int first1[n1+1]={0}; //存储图的顶点
int next1[m1+1] ={0};//存储边


//保存地图
void StoreMap(){
    for(auto& it : first1){ //初始化
        it = -1;
    }

    for(int i=1;i<=m1;i++){
        next1[i] = first1[u1[i]];
        first1[u1[i]] = i;
    }
}

//打印地图
void PrintMap(){
    for(int i=1;i<=n1;i++){
        int k = first1[i];
        while(k!=-1){
            std::cout<<u1[k]<<" "<<v1[k]<<" "<<w1[k]<<std::endl;
            k = next1[k];
        }
    }
}



//求二分图最大匹配
void BipartiteMapMaxMatch(){
    StoreMap();
    PrintMap();

}

int TestBipartiteMapMaxMatch(){
    auto start = std::chrono::steady_clock::now();

    BipartiteMapMaxMatch();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__BIPARTITE_MAP_MAX_MATCH1__H__