#ifndef __MERGE_SORT1__H__
#define __MERGE_SORT1__H__

#include <iostream>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*排序算法----归并排序
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

void Merge(int* arr,int start,int end,int mid, int* tmp){
    int leftS = start;
    int leftE = mid;
    int rightS = mid+1;
    int rightE = end;

    int length =0; //tmp长度
    //将左半部分和右半部分合并
    while(leftS<=leftE && rightS<=rightE){
        if(arr[leftS]<arr[rightS]){//左边的数比右边的小,则把该数放到tmp中
            tmp[length++] = arr[leftS++];
        }else{
            tmp[length++] = arr[rightS++];
        }
    }

    //合并剩下的左边部分(若有)
    while(leftS<=leftE){
        tmp[length++] = arr[leftS++];
    }

    //合并剩下的右半部分(若有)
    while(rightS<=rightE){
        tmp[length++] = arr[rightS++];
    }

    //左右部分合并完成后,将tmp合并到arr中(注意原数列的合并的起始位置)
    for(int i=0;i<length;i++){
        arr[start + i] = tmp[i];
    }
}

//归并排序(这里以升序排序为例)
void MergeSort(int* arr,int start,int end,int* tmp){
    if(start>=end){//结束条件
        return;
    }

    int mid = (start+end)/2;

    MergeSort(arr,start,mid,tmp);//左半部分
    MergeSort(arr,mid+1,end,tmp);//右半部分

    Merge(arr,start,end,mid,tmp);//合并算法
}

int TestMergeSort(){
    auto start = std::chrono::steady_clock::now();
    Print();

    //分配辅助内存
    int* tmp = new int[n+1];
    std::memset(tmp,0,n+1);

    MergeSort(h,0,n-1,tmp);//排序算法---归并排序

    Print();

    delete[] tmp;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MERGE_SORT1__H__