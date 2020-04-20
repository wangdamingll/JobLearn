#ifndef __BIPARTITE_MAP_MAX_MATCH2__H__
#define __BIPARTITE_MAP_MAX_MATCH2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/* 带权二分图匹配,权和最大----KM算法
 *
 * 问题描述:
 *  1 2 3 为女生, 4 5 6为男生,1可以和4 5匹配,2可以和5 6匹配,3可以和4匹配,要求最终的匹配都是男女相互认识的,求匹配的权和最大?
 *
 *  1    4
 *
 *  2    5
 *
 *  3    6
 *
 * 说明:
 * 1. 第一行两个整数n m,n男生和女生的总人数,m总的配对关系. 接下来m行,每行有3个数x y z,表示从女生x到男生y的边权(.注:1 2 3为女生,4 5 6为男生
 *  6 12    //注意注意是无向图
 *  1 4 3
 *  1 6 4
 *  2 4 2
 *  2 5 1
 *  2 6 3
 *  3 6 5
 *  4 1 3   //和上面数据对称
 *  6 1 4
 *  4 2 2
 *  5 2 1
 *  6 2 3
 *  6 3 5
 *
 * 时间复杂度:
 *
 *
 * 算法特点:
 *
 *
 * 思考:
 *  1. 可参考这位大神的博文:https://www.cnblogs.com/wenruo/p/5264235.html,详细画图推演了算法流程
 *  2. 本例将上面博客提到的模板算法有邻接矩阵存储图的方式(O(N^3))改为邻接表的方式存储,进一步降低了时间复杂度
 *  3. 这里的KM算法可以当成一个算法模板
 *
 * */


constexpr int n2 = 6;//人数
constexpr int m2 = 12;//配对数

//以下为了方便,直接初始化了
int u2[m2+1] ={0,1,1,2,2,2,3, 4,6,4,5,6,6};
int v2[m2+1] ={0,4,6,4,5,6,6, 1,1,2,2,2,3};
int w2[m2+1] ={0,3,4,2,1,3,5, 3,4,2,1,3,5};

int first2[n2+1]={0}; //存储图的顶点
int next2[m2+1] ={0};//存储边

int match2[n2+1]={0};//保存配对关系
int visit2g[n2+1]={0};//标识女生有没有被访问过
int visit2b[n2+1]={0};//标识男生有没有被访问过

int exv2g[m2+1] = {0};//标识每个女生的期望值
int exv2b[m2+1] = {0};//标识每个男生的期望值

int slack2[n2+1]={0};//记录每个男生如果能被女生倾心最少还需要多少期望值

//保存地图
void StoreMap2(){
    for(auto& it : first2){ //初始化
        it = -1;
    }

    for(int i=1;i<=m2;i++){
        next2[i] = first2[u2[i]];
        first2[u2[i]] = i;
    }
}

//打印地图
void PrintMap2(){
    for(int i=1;i<=n2;i++){
        int k = first2[i];
        while(k!=-1){
            std::cout<<u2[k]<<" "<<v2[k]<<" "<<w2[k]<<std::endl;
            k = next2[k];
        }
    }
}

//深度优先搜索
int DFS2(int u){


   return 0;
}

//带权二分图匹配,权和最大----KM算法
void BipartiteMapMaxMatch2(){
    StoreMap2();
    PrintMap2();

}

int TestBipartiteMapMaxMatch2(){
    auto start = std::chrono::steady_clock::now();

    BipartiteMapMaxMatch2();//带权二分图匹配,权和最大----KM算法

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__BIPARTITE_MAP_MAX_MATCH2__H__