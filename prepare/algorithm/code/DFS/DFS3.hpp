#ifndef __DFS3__H__
#define __DFS3__H__

#include <iostream>
#include <chrono>
using namespace std;

/*迷宫问题----深度优先搜索算法(DFS)
 *
 * 问题描述:
 *
 * */



int TestDFS2(){
    auto start = std::chrono::steady_clock::now();



    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS3__H__