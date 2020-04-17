#ifndef __MAP_BUILD_MIN_TREE2__H__
#define __MAP_BUILD_MIN_TREE2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*图最小生成树-----Prim算法
 *
 * 问题描述:
 * 镖局运输问题:
 * 古代镖局的运镖,就是运货,也就是现代的物流.镖局每到一个新地方开展业务,都霱要对运镖途中的绿林好汉进行打点.
 * 好说话的打点费就比较低,不好说话的打点费就比较高.现已知城镇地图如下(无向图数据).
 * 镖局现在需要选择一些道路进行疏通,以便镖局可以到达任意一个城镇,要求是花费的银子越少越好.换句话说,镖局的要求就是用最少的边让图连通(任意两点之间可以互相到
 * 达),其实就是将多余的边去掉.
 *
 * 说明:
 * 1. 无向图的概念
 * 边无方向的图称为无向图
 * 2. 第一行两个整数n m,n表示城市个数(城市编号为1~n),m表示道路条数. 接下来m行,每行有3个数x y z,表示从城市x到城市y所需的银子数量z
 *  6 9      //注意注意是无向图
 *  2 4 11
 *  3 5 13
 *  4 6 3
 *  5 6 4
 *  2 3 6
 *  4 5 7
 *  1 2 1
 *  3 4 9
 *  1 3 2
 *  4 2 11  //和上面数据对称
 *  5 3 13
 *  6 4 3
 *  6 5 4
 *  3 2 6
 *  5 4 7
 *  2 1 1
 *  4 3 9
 *  3 1 2
 *
 * 时间复杂度:
 * 1. 不使用任何优化方法,用邻接矩阵存储的话,时间复杂度O(N^2) ,N为城市数
 * 2. 使用堆和邻接表存储的话,时间复杂度O(MlogN),M为边数,N为顶点数
 *
 * 思考:
 * 1. Prim算法用到了Dijkstra算法的"变种",即在dis数组中找到与生成树最短的距离,而不是离源点s的最短距离
 * 2. 当生成树中顶点数量为n时,算法结束
 * 3. 无向图的数据采用邻接表存储法,也可以用邻接矩阵存储
 * 4. Dijkstra + 邻接表 的方式一定要注意图是有向图还是无向图,也就是说 Dijkstra + 邻接表要求边是有向的
 * */

//保存边信息
struct Edge2{
    Edge2() = default;
    Edge2(int index1,int dis1):index(index1),dis(dis1){}

    bool operator >(const Edge2& another) const{
        return this->dis>another.dis;
    }
    int index {0}; //城市编号
    int dis {0};    //距离
};

constexpr int n2 = 6;//城市个数
constexpr int m2 = 18;//边的个数(无向图)

//以下为了方便,直接初始化了
int u2[m2+1] ={0,2, 3, 4,5,2,4,1,3,1, 4, 5, 6,6,3,5,2,4,3};
int v2[m2+1] ={0,4, 5, 6,6,3,5,2,4,3, 2, 3, 4,5,2,4,1,3,1};
int w2[m2+1] ={0,11,13,3,4,6,7,1,9,2, 11,13,3,4,6,7,1,9,2};

int first2[n2+1]={0}; //存储城市编号
int next2[m2+1] ={0};//存储边

int book2[n1+1] = {0}; //标识是否在生成树中
int count2 = 0;//标识生成树种有多少个城市
int sum2 =0;//累计消耗

int dis[n2+1] ={0,0,99999999,99999999,99999999,99999999,99999999};//Dijkstra算法
std::vector<Edge2> disV;//堆排序使用

//邻接表存储
void StoreMap2(){
    for(auto& it : first2){ //初始化城市编号数组信息
        it = -1;
    }
    for(int i=1;i<=m2;i++){ //存储每一条边
        next2[i] = first2[u2[i]];
        first2[u2[i]] = i; //存储城市出发顶点对应数据所在的行号
    }
}

//打印邻接表
void PrintMap2(){
    for(int i=1;i<=n2;i++){ //遍历每一个城市编号
        int k = first2[i]; //取出城市编号对应的数据所在行数
        while(k!=-1){
            std::cout<<u2[k]<<" "<<v2[k]<<" "<<w2[k]<<std::endl;
            k = next2[k];
        }
    }
}

//获取离生成树最近的城市编号
int GetMinIndex(){
    int index=0;
    int finish=false;
    do{
        std::pop_heap(disV.begin(),disV.end(),std::greater<Edge2>{});//将最小元素移动到末尾
        auto elem = disV.back();
        disV.pop_back();

        if(book2[elem.index]==0){//有无在生成树中
            index = elem.index;
            finish = true;
        }
    }while(!finish);
    return index;
}

//图最小生成树-----Prim算法
void MapBuildMinTree2(){
    StoreMap2();
    PrintMap2();

    //初始化dis数组
    int k = first2[1];
    while(k!=-1) {
        dis[v2[k]] = w2[k];
        disV.emplace_back(v2[k],w2[k]);//用于堆排序
        k = next2[k];
    }

    //先初始化disV为最小堆
    std::make_heap(disV.begin(),disV.end(),std::greater<Edge2>{});

    //Prim核心代码
    book2[1] = 1;//可以把任意城市加入生成树,这里以1号城市为例
    count2++;
    while(count2<n2){
        int index  = GetMinIndex(); //选取离生成树最近的城市编号
        book2[index] = 1;//加入生成树
        sum2+=dis[index];//计算消耗
        count2++;//累加

        //枚举index所有的出边 进行松弛
        int k2 = first2[index];
        while(k2!=-1){
            if(dis[v2[k2]]>w2[k2]){//不在生成树中,w2[k2]表示index->v2[k2]顶点的距离,因为index已经加入生成树了,所以也就是v2[k2]到生成树的距离,Dijkstra算法思想
                dis[v2[k2]]=w2[k2];//松弛
                disV.emplace_back(v2[k2],w2[k2]);
                std::push_heap(disV.begin(),disV.end(),std::greater<Edge2>{});//调整堆
            }
            k2 = next2[k2];
        }
    }

    std::cout<<"消耗银子:"<<sum2<<std::endl;
}

int TestMapBuildMinTree2(){
    auto start = std::chrono::steady_clock::now();

    MapBuildMinTree2();//图最小生成树-----Prim算法

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_BUILD_MIN_TREE2__H__