#ifndef __MAP_BUILD_MIN_TREE1__H__
#define __MAP_BUILD_MIN_TREE1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

/*图最小生成树-----Kruskal算法
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
 *  6 9
 *  2 4 11
 *  3 5 13
 *  4 6 3
 *  5 6 4
 *  2 3 6
 *  4 5 7
 *  1 2 1
 *  3 4 9
 *  1 3 2
 *
 * 时间复杂度:
 * 快速排序的时间复杂度:O(MlogM) M为边数
 * 从M条边找出N-1条边时间复杂度:O(MlogN)
 * 总时间复杂度:O(MlogM + MlogN),因为通常M比N大很多,所以Kruskal总的时间复杂度:O(MlogM)
 *
 * 思考:
 * 1. Kruskal算法中最重要的判断两个顶点是否已经连通要用到并查集
 * 2. 如果有n个顶点,那么该图的最小生成树所需的边的数量是n-1
 * 3. 无向图的数据采用邻接表存储法
 * 4. 对边可以进行排序处理,也可以借助堆(或者优先级队列)  
 *
 * */

//保存边信息
struct Edge{
    Edge() = default;
    Edge(int u1,int v1,int w1):u(u1),v(v1),w(w1){}

    bool operator <(const Edge& another) const{
        return this->w<another.w;
    }
    int u {0};
    int v {0};
    int w {0};
};

constexpr int n1 = 6;//城市个数
constexpr int m1 = 9;//边的个数
int f1[n1+1] = {0}; //并查集使用

//并查集Find
int GetF(int v){
    if(f1[v] == v){
        return v;
    }

    f1[v] = GetF(f1[v]);
    return f1[v];
}

//并查集Merge
int Merge(int v,int u){
    int t1 = GetF(v);
    int t2 = GetF(u);
    if(t1!=t2){
        f1[t2] = t1;
        return 1;//没有连通
    }
    return 0;//有连通
}


//图最小生成树-----Kruskal算法
void MapBuildMinTree1(){
    //初始化边信息
    std::vector<Edge> v ={{0,0,0},//加了这组数据 为了是城市编号和v的index相同
                          {2,4,11},
                          {3,5,13},
                          {4,6,3},
                          {5,6,4},
                          {2,3,6},
                          {4,5,7},
                          {1,2,1},
                          {3,4,9},
                          {1,3,2},
    };

    //对边进行排序,期望用的是快排吧
    std::sort(v.begin(),v.end());

    //并查集f初始化
    for(int i=1;i<=n1;i++){
        f1[i] = i;
    }

    //Kruskal核心语句
    int count = 0; //最小生成树已经使用的边的数量
    int sum =0;//消耗
    for(int i=1;i<=m1;i++){//枚举每条边
        if(1==Merge(v[i].u,v[i].v)){//两个城市没有连通
            count++;
            sum+=v[i].w;
        }
        if(count == n1-1){//n个城市的最小生成树用到的边是n-1
            break;
        }
    }

    std::cout<<"消耗银子:"<<sum<<std::endl;
}

int TestMapBuildMinTree1(){
    auto start = std::chrono::steady_clock::now();

    MapBuildMinTree1();//图最小生成树-----Kruskal算法

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_BUILD_MIN_TREE1__H__