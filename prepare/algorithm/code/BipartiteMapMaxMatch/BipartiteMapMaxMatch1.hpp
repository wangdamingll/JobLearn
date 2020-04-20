#ifndef __BIPARTITE_MAP_MAX_MATCH1__H__
#define __BIPARTITE_MAP_MAX_MATCH1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*无权二分图最大匹配----匈牙利算法
 *
 * 问题描述:
 *  1 2 3 为女生, 4 5 6为男生,1可以和4 5匹配,2可以和5 6匹配,3可以和4匹配,要求最终的匹配都是男女相互认识的,求最大匹配数?
 *
 *  1    4
 *
 *  2    5
 *
 *  3    6
 *
 * 说明:
 * 1. 也就是求无权二分图(无向图)的最大匹配数
 * 2. 无权二分图:没有边权的二分图
 * 3. 第一行两个整数n m,n男生和女生的总人数,m总的配对关系. 接下来m行,每行有3个数x y z,表示从女生x到男生y的边权(边权这里可以忽略).注:1 2 3为女生,4 5 6为男生
 *  6 10    //注意注意是无向图
 *  1 4 1
 *  1 5 1
 *  2 5 1
 *  2 6 1
 *  3 4 1
 *  4 1 1   //和上面数据对称
 *  5 1 1
 *  5 2 1
 *  6 2 1
 *  4 3 1
 *
 * 时间复杂度:
 * O(NM)
 *
 * 算法特点:
 * 1. 首先从任意一个未被配对的点u开始,从点u的边中任意选一条边(假设这条边是u→ν)开始配对,如果此时点v还没有被配对,则配对成功.此时便找到了一条增广路(只不过这条增广路比较简单).
 *    如果此时点v已经被配对了,那就要尝试进行"连锁反应".如果尝试成功了,则找到一条增广路,此时需要更新原来的配对关系.
 *    这里要用一个数组match来记录配对关系,比如点v与点配对了,就记作match[v]=u和match[u]=v配对成功后,记得要将配对数加1.
 *    配对的过程我们可以通过深度优先搜索来实现,当然广度优先搜索也可以.
 * 2. 如果刚才所选的边配对失败,要从点u的边中再重新选一条边,进行尝试.直到点u配对成功,或者尝试过点u所有的边为止.
 * 3. 接下来继续对剩下没有被配对的点一一进行配对,直到所有的点都尝试完毕,找不到新的增广路为止,输出配对数.
 *
 * 思考:
 * 1. 二分图数据可以用邻接矩阵存储,也可以用邻接表存储
 * 2. 遍历二分图点可以用DFS,也可以BFS
 * 3. n个顶点,最多有n/2条增广路
 *
 * */


constexpr int n1 = 6;//人数
constexpr int m1 = 10;//配对数

//以下为了方便,直接初始化了
int u1[m1+1] ={0,1,1,2,2,3, 4,5,5,6,4};
int v1[m1+1] ={0,4,5,5,6,4, 1,1,2,2,3};
int w1[m1+1] ={0,1,1,1,1,1, 1,1,1,1,1};//边权这里可以忽略

int first1[n1+1]={0}; //存储图的顶点
int next1[m1+1] ={0};//存储边

int match1[n1+1]={0};//保存配对关系
int visit1[n1+1]={0};//标识有没有被访问过

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

//深度优先搜索
int DFS(int u){
    int k = first1[u];
    while(k!=-1){//遍历u点的所有出边
        int v = v1[k];//u点出边的另一个点v
        if(visit1[v] == 0){ //v点没有被访问过
            visit1[v] =1;//标记
            if(match1[v]==0 || DFS(match1[v])){//表示v点已经没有被匹配,或者匹配成功了需要就行连锁反应
                match1[u] = v;
                match1[v] = u;
                return 1;
            }
        }
        k = next1[k];
    }

    return 0;
}

//求二分图最大匹配
void BipartiteMapMaxMatch(){
    StoreMap();
    PrintMap();

    int num =0;//配对数

    for(int i=1;i<=n1;i++){ //枚举每一个没有配对的点
        for(auto& it : visit1){ //清空上次的标记
            it =0;
        }
        if(DFS(i)){
            num++;
        }
    }

    std::cout<<"最大匹配数为:"<<num<<std::endl;
    std::cout<<"匹配关系为:"<<std::endl;
    for(int i=1;i<=n1/2;i++){//后3个重复了,最多有n/2条增广路
        std::cout<<i<<"<->"<<match1[i]<<" ";
    }
    std::cout<<std::endl;
}

int TestBipartiteMapMaxMatch1(){
    auto start = std::chrono::steady_clock::now();

    BipartiteMapMaxMatch();//无权二分图最大匹配----匈牙利算法

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__BIPARTITE_MAP_MAX_MATCH1__H__