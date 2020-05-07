#ifndef __STACK_USE__H__
#define __STACK_USE__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;

/* 栈-----栈的应用
 *
 * 算法思想:
 * 1. 平衡符号
 *
 *
 *
 * */

int TestStackUse(){
    auto start = std::chrono::steady_clock::now();




    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__STACK_USE__H__