#ifndef __DFS3__H__
#define __DFS3__H__

#include <iostream>
#include <chrono>
using namespace std;

/*迷宫问题----深度优先搜索算法(DFS)
 *
 * 问题描述:
 * 迷宫由n行m列的单元格组成（n和m都小于等于50），每个单元格要么是空地，要么是障碍物。找到一条从迷宫的起点通往某个位置的最短路径。
 * 注意:障碍物是不能走的
 *
 * */




int TestDFS3(){
    auto start = std::chrono::steady_clock::now();



    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS3__H__