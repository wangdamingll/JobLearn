#ifndef __BUCKET_SORT1__H__
#define __BUCKET_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----计数排序
 *
 * 问题描述:
 * 对整个数据进行升序排序:3 8 9 6 5 4 2 1
 *
 * 算法应用:
 * 1. 可以统计某个数出现的次数
 * 2. 可以对某个数出现进行标记
 * 3. 可以排序,但是要求这组数据要大体上均匀分布的
 *
 * 思考:
 * 1. 一定要注意这组数据的最大值和最小值,从而可以计算桶数
 * 2. 这组数据要大体上均匀分布的
 *
 * */

constexpr int n1 = 8;
int h1[n1+1] ={0,3,8,9,6,5,4,2,1};

void Print(){
    for(int i=1;i<=n1;i++){
        std::cout<<h1[i]<<" ";
    }
    std::cout<<std::endl;
}

//计数排序
void Count1(){
    int bucket[9+1]={0}; //桶:注意这组数据最大值为9,所以要有9个桶
    for(int i=1;i<=n1;i++){
        ++bucket[h1[i]];
    }
    for(int i=1;i<=9;i++){
        int size = bucket[i];
        for(int j=1;j<=size;j++){
            std::cout<<i<<" ";
        }
    }
    std::cout<<std::endl;
}

int TestCount1(){
    auto start = std::chrono::steady_clock::now();
    Print();

    Count1();//计数排序

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__BUCKET_SORT1__H__