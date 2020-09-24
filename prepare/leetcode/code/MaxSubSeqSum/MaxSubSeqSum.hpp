#ifndef __TEST__H__
#define __TEST__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/* 最大子序列和问题
 *
 * 问题描述:
 * 求最大子序列和是多少?
 * -2,11,-4,13,-5,-2
 * 为方便起见,若所有整数均为负数,则最大子序列和为0
 *
 * 这里是答案是20
 *
 * 算法思想
 * 1. 暴力枚举
 * 规定i为当前子序列起点,从i开始枚举每种情况
 *
 * 2. 分治思想
 * 1) 采用递归二分,最大和出现在左半边或者右半边或者从左半边开始跨越终点到达右半边
 * 2) 因为要求左半边和右半边的值做比较,所以需要回溯时处理
 * 3) 可以查看main2.cpp中线段树解法
 *
 * 3. 联机算法
 * 子序列和为负值的一定不能是最终的最大子序列和的起点(相当于正效应)
 * 附带优点:它只对数据进行一次扫描,一旦arr[i]被读入并被处理,它就不再需要被记忆.
 *
 * */

int TestEnum(){
    auto start = std::chrono::steady_clock::now();

    int arr[]={-2,11,-4,13,-5,-2};
    int size = sizeof(arr)/sizeof(arr[0]);
    int max=0;
    int thisSum=0;
    for(int i=0;i<size;i++){
        thisSum=0;
        for(int j=i;j<size;j++){//规定i为当前子序列起点,从i开始枚举每种情况
            thisSum+=arr[j];
            if(thisSum>max){
                max = thisSum;
            }
        }
    }

    std::cout<<"TestEnum::最大子序列和为:"<<max<<std::endl;


    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

int MaxRe(int* arr,int start,int end){
    if(start>=end){//基线条件
        if(arr[start]>0){
            return arr[start];
        }else{
            return 0;
        }
    }

    int mid = (start+end)/2;
    int maxLeft = MaxRe(arr,start,mid);//左半部分最大值 [start,mid]
    int maxRight= MaxRe(arr,mid+1,end);//右半部分最大值 [mid+1,end]

    //从左半边跨越中点到右半部分最大值
    int leftSum = 0;
    int rightSum = 0;
    int maxLeftSum=0;
    int maxRightSum=0;

    for(int i=mid;i>=start;i--){ //这里是从mid向start遍历,如果从start到mid遍历这就固定了开始起点,这是不对的
        leftSum+=arr[i];
        if(leftSum>maxLeftSum){
            maxLeftSum= leftSum;
        }
    }
    for(int j=mid+1;j<=end;j++){//这里是从mid+1往end遍历
        rightSum+=arr[j];
        if(rightSum>maxRightSum){
            maxRightSum = rightSum;
        }
    }

    return std::max(std::max(maxLeft,maxRight),maxLeftSum+maxRightSum);//3者中的一个
}

int TestRe(){
    auto start = std::chrono::steady_clock::now();

    int arr[]={-2,11,-4,13,-5,-2};
    int size = sizeof(arr)/sizeof(arr[0]);

    int max = MaxRe(arr,0,size-1);
    std::cout<<"TestRe::最大子序列和为:"<<max<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__TEST__H__