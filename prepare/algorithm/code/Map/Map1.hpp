#ifndef __MAP1__H__
#define __MAP1__H__

#include <iostream>
#include <chrono>
using namespace std;

/*图遍历----深度优先搜索算法(DFS)-----无向图
 *
 * 问题描述:
 *
 *
 * 思考:
 *
 * */



void PrintMap4(){

}


void CreateMap1(){

}


void DFS1(int x,int y,int color){

}



int TestDFS1(){
    auto start = std::chrono::steady_clock::now();



    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP1__H__