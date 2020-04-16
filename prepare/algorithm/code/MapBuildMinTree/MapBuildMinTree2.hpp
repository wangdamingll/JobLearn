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
 *
 * */

//图最小生成树-----Prim算法
void MapBuildMinTree2(){



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