#ifndef __BUCKET_SORT2__H__
#define __BUCKET_SORT2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include <cstring>
using namespace std;

/*排序算法----桶排序
 *
 * 问题描述:
 * 对整个数据进行升序排序
 *
 * 算法应用:
 * 1. 可以排序,但是要求这组数据要大体上均匀分布的
 * 2. 如果要排序的数组非常大且有规律或者大体分布均匀或者通过某种方式能够对数据进行放大缩小,可以考虑桶排序,期望的时间复杂度为O(N)
 *
 * 思考:
 * 1. 一定要注意这组数据的最大值和最小值,从而可以计算桶数
 * 2. 这组数据要大体上均匀分布的
 *
 * */

constexpr int MAX =100;     //假设最大数为100
constexpr long long N =10000000;       //源数据数量
constexpr int BUCKETN =5;   //假设有5个桶

void Print2(int* arr,int len){
    for(int i=1;i<=len;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}

//桶排序
void BucketSort(){
    const int bucketWidth = MAX/BUCKETN;//每个桶容纳的数据范围
    int* arr = new int[N+1];
    std::memset(arr,0,N+1);

    std::random_device ed;
    std::vector<int> v[BUCKETN+1]; //如果是100的话 index=5
    std::default_random_engine re(ed());
    std::uniform_int_distribution<int> uniform_dist(1,MAX);

    for(int i=1;i<=N;i++){
        arr[i] = uniform_dist(re);
    }

    //Print2(arr, N);

    //桶排序
    for(int i=1;i<=N;i++){
        v[arr[i]/bucketWidth].push_back(arr[i]);
    }
    int p=0;
    for(auto it:v){
        std::sort(it.begin(),it.end());
        for(auto iter:it){
            arr[++p] = iter;
        }
    }

    //Print2(arr, N);
}

int TestBucketSort2(){
    auto start = std::chrono::steady_clock::now();

    BucketSort();//桶排序

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout<<"time:"<<time.count()<<"s"<<std::endl;

    return 0;
}


#endif //__BUCKET_SORT2__H__