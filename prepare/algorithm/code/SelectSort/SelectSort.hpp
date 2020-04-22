#ifndef __SELECT_SORT1__H__
#define __SELECT_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----选择排序
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

//选择排序
void SelectSort(){
    Print();

    for(int i=0;i<n;i++){
        int min = i;
        for(int j=i+1;j<n;j++){
            if(h[min]>h[j]){ //每轮求最小值
                min = j;
            }
        }
        if(min!=i){
            std::swap(h[min],h[i]);
        }
    }

    Print();
}

int TestSelectSort(){
    auto start = std::chrono::steady_clock::now();

    SelectSort();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__SELECT_SORT1__H__