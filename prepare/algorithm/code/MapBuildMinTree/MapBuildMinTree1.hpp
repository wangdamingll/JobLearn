#ifndef __MAP_BUILD_MIN_TREE1__H__
#define __MAP_BUILD_MIN_TREE1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*图最小生成树-----Kruskal算法
 *
 * 问题描述:
 * 下面是一个由图(无向图)转换成的邻接表存储的源数据,镖局现在霱要选择一些道路进行硫通,以便镖局可以到达任意一个城镇,要求是花费的银子越少越好.
 * 换句话说,镖局的要求就是用最少的边让图连通(任意两点之间可以互相到达),其实就是将多余的边去掉.
 * 说明:
 * 1. 无向图的概念
 * 边无方向的图称为无向图
 * 2. 第一行两个整数n m,n表示城市个数(城市编号为1~n),m表示道路条数. 接下来m行,每行有3个数x y z,表示从城市x到城市y所需的银子数量z
 *  5 5
 *  2 3 2
 *  1 2 -3
 *  1 5 5
 *  4 5 2
 *  3 4 3
 *
 *
 * 时间复杂度:
 *
 * */


int TestMapBuildMinTree1(){
    auto start = std::chrono::steady_clock::now();



    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_BUILD_MIN_TREE1__H__