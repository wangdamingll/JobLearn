#ifndef __UNIONFIND1__H__
#define __UNIONFIND1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

/*二叉树应用-----并查集
 *
 * 问题描述:
 *
 *
 * 时间复杂度:
 *
 * */


int TestUnionFind1(){
    auto start = std::chrono::steady_clock::now();



    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__UNIONFIND1__H__