#ifndef __BUBBLE_SORT1__H__
#define __BUBBLE_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----冒泡排序
 *
 * 问题描述:
 * 对整个数据进行升序排序:3 8 9 6 5 4 2 1
 *
 * 算法应用:
 *
 * 思考:
 *
 * */

constexpr int n = 8;
int h[n] ={3,8,9,6,5,4,2,1};

void Print(){
    for(auto it:h){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
}

//冒泡排序
void BubbleSort(){
    Print();

    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){//外层i为了统计总共需要n-1轮用的
            if(h[j]>h[j+1]){
                std::swap(h[j],h[j+1]);
            }
        }
    }

    Print();
}

int TestBubbleSort1(){
    auto start = std::chrono::steady_clock::now();

    BubbleSort();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__BUBBLE_SORT1__H__