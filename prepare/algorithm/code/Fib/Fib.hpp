#ifndef __FIBTEST__H__
#define __FIBTEST__H__

#include <iostream>
#include <chrono>
using namespace std;


/* 动态规划-------斐波那契数列
 *
 * 问题描述:
 * 计算在位置n的斐波那契数.
 *
 * 说明:
 * 菲波那切数列,指的是这样一个数列:1、1、2、3、5、8、13、21、34、……
 * 在数学上，斐波那契数列以如下被以递推的方法定义:F(1)=1,F(2)=1,F(n)=F(n-1)+F(n-2)  (n ≥ 3，n ∈ N*)
 *
 * 算法思想:
 * 1. 采用普通递归方式求解
 * 2. 采用动态规划求解
 *
 * 时间复杂度
 * 1.采用递归方式:O(2^N)
 * 2.采用动态规划:O(N)
 *
 * 算法特点
 * 1. 递归方式采用栈记录递归每步的数据,递归回溯的时候使用
 * 2. 动态规划采用一个或者几个变量记录上次的数据,下一步在使用
 *
 * 思考:
 * 1. 递归因为重复计算中间的数据,所以复杂度非常高
 *
 * */

//递归求解
uint64_t FibRec(int n){
    if(n<=1){
        return 1;
    }else{
        return FibRec(n-1) + FibRec(n-2);
    }
}

//动态规划求解
uint64_t Fib(int n){
    if(n<=2){
        return 1;
    }

    uint64_t last = 1;
    uint64_t nextToLast=1;
    uint64_t anwser = 1;

    for(int i=2;i<=n;i++){
        anwser = last + nextToLast;
        nextToLast = last;
        last = anwser;
    }

    return anwser;
}

int TestFib(){
    auto start = std::chrono::steady_clock::now();

    //递归方式
    uint64_t num = FibRec(4);
    std::cout<<"RECFib:num="<<num<<std::endl;

    //动态规划方式
    num = Fib(4);
    std::cout<<"Fib:num="<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__FIBTEST__H__