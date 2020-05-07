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
 *  每个右花括号、右方括号及右圆括号必然对应其相应的左括号.序列[()]是合法的,但[(])是错误的.
 *
 * 2. 中缀表达式转后缀表达式
 *
 *
 *
 * 3. 后缀表达式计算结果
 *  当见到一个数时就把它推入栈中;在遇到一个运算符时该运算符就作用于从该栈弹出的两个数(符号)上,再将所得结果推入栈中.
 *
 * 算法特点:
 * 1. 平衡符号采用的联机算法,时间复杂度是O(N)
 * 3. 后缀表达式计算结果时间复杂度是O(N)
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