#ifndef __DFS5__H__
#define __DFS5__H__

#include <iostream>
#include <chrono>
using namespace std;

/*图遍历----深度优先搜索算法(DFS)-----无向图和有向图
 *
 * 问题描述:
 *
 * 思考:
 * */




//打印地图
void PrintMap5(){

}


void CreateMap5(){

}


int TestDFS5(){
    auto start = std::chrono::steady_clock::now();


    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS5__H__