#ifndef __SHELL_SORT1__H__
#define __SHELL_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----希尔排序
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

//希尔排序(这里以升序排序为例)
void ShellSort(){
    Print();

    int increament = n;
    do{
        increament = increament/3 + 1; //理论上最优步长计算方法
        for(int i = increament;i<n;i+=increament){//分组插入排序
            for(int j=i+increament;j<n;j+=increament){//插入排序核心部分代码
                if(h[j]<h[j-increament]){//比它前面那个元素小
                    int tmp = h[j]; //缓存元素
                    int k =0;
                    for(k=j-increament;k>=0&&tmp<h[k];k-=increament){//从j的前一个元素向前,如果比j大,则向后以移动,直到找到比j元素小的地方插入
                        h[k+increament] = h[k];
                    }
                    h[k+increament] = tmp;
                }
            }
        }
    }while(increament>1);//步长等于1时结束

    Print();
}

int TestShellSort(){
    auto start = std::chrono::steady_clock::now();

    ShellSort();//排序算法---希尔排序

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__SHELL_SORT1__H__