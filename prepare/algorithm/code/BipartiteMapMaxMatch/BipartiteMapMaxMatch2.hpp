#ifndef __BIPARTITE_MAP_MAX_MATCH2__H__
#define __BIPARTITE_MAP_MAX_MATCH2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstring>
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

constexpr int INF = 0x3f3f3f3f;

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
bool DFS2(int girl){
    visit2g[girl] = 1;//标识
    //找出girl所有有好感的男生
    int k = first2[girl];
    while(k!=-1){
        if(visit2b[v2[k]] == 1){//每个男生只能每轮只能被匹配一次
            k = next2[k];
            continue;
        }
        int gap = exv2g[u2[k]] + exv2b[v2[k]] - w2[k]; //exv2g[u2[k]] + exv2b[v2[k]] == w2[k],即女生和男生的期望值和等于比边权
        if(gap==0 ){//满足要求
            visit2b[v2[k]] = 1; //标识
            if(match2[v2[k]]==0 || DFS2(match2[v2[k]])){//该男生没有被匹配成功过 或者 "连锁反应"
                match2[v2[k]] = girl;
                return true;
            }

        } else{
            slack2[v2[k]] = std::min(slack2[v2[k]],gap);//slack 可以理解为该男生要得到女生的倾心 还需多少期望值 取最小值
        }

        k = next2[k];
    }

   return false;
}

//带权二分图匹配,权和最大----KM算法
void BipartiteMapMaxMatch2(){
    StoreMap2();
    PrintMap2();

    //KM算法核心部分
    //每个女生的初始期望值是与她相连的男生最大的好感度
    for(int i=1;i<=n2/2;i++){
        int k = first2[i];
        exv2g[i] = w2[k];//先假设第一个为最大值
        while(k!=-1){
            exv2g[i] = std::max(exv2g[i],w2[k]);
            k = next2[k];
        }
    }

    //尝试为每一个女生解决归宿问题
    for(int i=1;i<=n2/2;i++){
        //因为要求最小值,所以需要初始化无穷大
        std::memset(slack2,INF, sizeof(slack2));

        while (true){//为每个女生解决归宿问题的方法是:如果找不到就降低期望值,直到找到为止
            //记录每轮匹配中男生女生是否被尝试匹配过
            std::memset(visit2b,0, sizeof(visit2b));
            std::memset(visit2g,0, sizeof(visit2g));

            if(DFS2(i)) break; //尝试成功 则退出

            //不成功则降低期望值
            //最少可降低的期望值
            int d = INF;
            for(int j=1;j<=n2;j++){//任意一个参与匹配女生能换到任意一个这轮没有被选择过的男生所需要降低的最小值
                if(!visit2b[j]){
                    d = std::min(d,slack2[j]);//slack可以理解为该男生要得到女生的倾心 还需多少期望值 取最小值
                }
            }

            for(int i2=1;i2<=n2;i2++){
                if(visit2g[i2]){//为所有访问过的女生降低期望值
                    exv2g[i2] -= d;
                }
            }

            for(int j=1;j<=n2;j++){
                if(visit2b[j]){//所有访问过的男生增加期望值
                    exv2b[j] += d;
                }else{//没有访问过的男生们 因为女生们的期望值降低,距离得到女生倾心又进了一步!
                    slack2[j] -= d;
                }
            }
        }
    }

    //匹配完成 求出所有配对的好感度的和
    std::cout<<"匹配情况:";
    int sum =0;
    for(int i3=1;i3<=n2/2;i3++){
        int k = first2[i3];
        while(k!=-1){
            if(i3 == match2[v2[k]]){
                sum+=w2[k];
                std::cout<<u2[k]<<"<->"<<v2[k]<<std::endl;
            }
            k = next2[k];
        }
    }
    std::cout<<std::endl;
    std::cout<<"匹配总和:"<<sum<<std::endl;
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