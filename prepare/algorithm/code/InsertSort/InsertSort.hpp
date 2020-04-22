#ifndef __INSERT_SORT1__H__
#define __INSERT_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----插入排序
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

//插入排序(这里以升序排序为例)
void InsertSort(){
    Print();

    for(int i=1;i<n;i++){ //第一个元素是有序的,从第二个元素开始与它前一个元素比较
        if(h[i]<h[i-1]){//如果比它前一个元素小
            int tmp = h[i];//缓存i元素
            int j=0;
            for(j=i-1;j>=0&&tmp<h[j];j--){//从i-1的元素开始,如果比i元素大,向后移动一位,直到找到比i元素小的
                h[j+1] = h[j];
            }
            //找到了
            h[j+1] = tmp; //当前位置的后一个位置才是正确的位置
        }
    }

    Print();
}

int TestInsetSort(){
    auto start = std::chrono::steady_clock::now();

    InsertSort();//排序算法---插入排序

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__INSERT_SORT1__H__