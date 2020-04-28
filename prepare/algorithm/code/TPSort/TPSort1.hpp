#ifndef __TP_SORT1__H__
#define __TP_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/* 有向无环图-----拓扑排序---BFS
 *
 * 问题描述:
 * 求有向无环图的拓扑排序结果
 *
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 第一行两个整数n m,n表示图的顶点个数,m表示图的边数. 接下来m行,每行有3个数x y z,表示从顶点x到顶点y的边权
 *  6 7      //注意这里图的边权为0(这里用不到)
 *  1 4 0
 *  1 3 0
 *  4 2 0
 *  3 2 0
 *  2 5 0
 *  5 6 0
 *
 * 时间复杂度:
 *
 * 算法特点:
 *
 * 思考:
 *
 * */

namespace TPSort1{
//保存地图
void StoreMap(){

}

//打印地图
void PrintMap() {

}

//拓扑排序----BFS
void TPSort(){
    StoreMap();
    PrintMap();

}

int TestTPSort(){
    auto start = std::chrono::steady_clock::now();

    TPSort();//拓扑排序----BFS

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}
}

#endif //__TP_SORT1__H__