#ifndef __MAP_CUT_EDGE1__H__
#define __MAP_CUT_EDGE1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*图的割边-----tarjan算法
 *
 * 问题描述:
 * 求图的割边
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
 * 1. 深度优先遍历或广度优先遍历:O(N(N+M))
 * 2. 本例割边算法:
 *  用邻接矩阵存储:O(N^2)
 *  用邻接表存储:O(N+M)
 *
 * 算法特点:
 * 1. 需要用DFS遍历图的所有顶点,记录num[顶点编号] = 顶点深度遍历时间戳
 * 2. 当遍历到顶点u时,枚举顶点u的所有出边,比如v,如何知道v不经过父节点u能否回到祖先节点呢?对子节点v再次DFS
 * 3. 需要记录每个子节点v在不经过父节点u的情况下,能够回到的最小时间戳(若存在v的父节点不止u一个的情况下):lows[v] = min(lows[v],nums[f])
 * 4. v回溯的时候获取当前节点的最小时间戳low[u]=min(low[u],low[v]),如果low[v]>=num[u],表示v不能不经过u回到祖先,即u为割点,
 *    如果low[v]>num[u],表示v不经过u,也没有其他的父节点,即u<->v是割边
 *
 * 思考:
 * 1. 图的割边可以用DFS或BFS处理:依次删除每条边,然后用DFS或者BFS检查图是否连通,若图不在连通,则该边是图的割边,但是此方法时间复杂度比较高
 * 2. 图的数据可以用邻接矩阵,也可以用邻接表存储,本例割点算法如果实际应用,建议采用邻接表方法,时间复杂度比较低
 * */


constexpr int n1 = 6;//
constexpr int m1 = 12;//

//以下为了方便,直接初始化了
int u1[m1+1] ={0,1,1,4,3,2,5, 4,3,2,2,5,6};
int v1[m1+1] ={0,4,3,2,2,5,6, 1,1,4,3,2,5};
int w1[m1+1] ={0,1,1,1,1,1,1, 1,1,1,1,1,1};

int first1[n1+1]={0}; //存储图的顶点
int next1[m1+1] ={0};//存储边

int nums1[n1+1] = {0};//保存深度遍历图时顶点对应的时间戳 nums[顶点] = 时间戳
int lows1[n1+1] = {0};//保存子节点v不经过父节点u能够达到的最小时间戳 lows[顶点] = 时间戳
int index1=0;//时间戳起点
int root1 = 0; //标识根节点

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

//深搜遍历图顶点
void DFS(int cur, int father){
    int child = 0;//统计cur子节点的个数
    index1++; //时间戳累计
    nums1[cur] = index1;//初始化为自己
    lows1[cur] = index1;

    //枚举cur顶点的所有出边,找到子节点
    int k = first1[cur];
    while(k!=-1){
        int v = v1[k];//子节点
        if(nums1[v] == 0){//节点有没有被访问过
            child++;
            DFS(v,cur);//继续深搜
            //更新当前顶点cur能否访问到最早顶点的时间戳
            lows1[cur] = std::min(lows1[cur],lows1[v]);
            if(lows1[v]>nums1[cur]){//割边判断
                std::cout<<cur<<"<->"<<v<<std::endl;
            }
        } else if(v!=father){//节点被访问过,但是不是cur的父节点(递归生成树中father是cur的父节点),
                             //但是在对cur再次递归时,发现cur的父节点不止一个,即v也是cur的父节点,则需要更新当前节点cur能否访问到最早顶点的时间戳
            lows1[cur] = std::min(lows1[cur],nums1[v]);
        }

        k = next1[k];
    }

}

//求地图割边
void MapCutEdge(){
    StoreMap();
    PrintMap();

    root1 =1;
    DFS(1,root1);//从1号顶点开始
}

int TestMapCutEdge1(){
    auto start = std::chrono::steady_clock::now();

    MapCutEdge();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_CUT_EDGE1__H__