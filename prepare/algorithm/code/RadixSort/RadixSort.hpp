#ifndef __RADIX_SORT1__H__
#define __RADIX_SORT1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;

/*排序算法----计数排序
 *
 * 问题描述:
 * 对整个数据进行升序排序:3 8 9 6 5 4 2 1
 *
 * 算法应用:
 *
 * 思考:
 *
 * */

int a[] ={53, 3, 542, 748, 14, 214, 154, 63, 616,987,565,14};

void Print(int* arr, int len){
    for(int i=0;i<len;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}

/*
 * 获取数组a中最大值
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
int GetMax(const int* arr, int n){

    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

/*
 * 对数组按照"某个位数"进行排序(桶排序)
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 *     exp -- 指数。对数组a按照该指数进行排序。
 *
 * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
 *    (01) 当exp=1表示按照"个位"对数组a进行排序
 *    (02) 当exp=10表示按照"十位"对数组a进行排序
 *    (03) 当exp=100表示按照"百位"对数组a进行排序
 *    ...
 */
void CountSort(int* arr, int n, int exp){
    int output[n];             // 存储"被排序数据"的临时数组
    std::memset(output,0,n*sizeof(int));

    int i=0;
    int buckets[10] = {0};

    // 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++){
        buckets[ (arr[i]/exp)%10 ]++;
    }

    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < 10; i++){
        buckets[i] += buckets[i - 1];
    }

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--){
        int k = (arr[i]/exp)%10;
        int j = buckets[ (arr[i]/exp)%10 ];
        output[buckets[ (arr[i]/exp)%10 ] - 1] = arr[i];
        buckets[ (arr[i]/exp)%10 ]--;
    }

    // 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++){
        arr[i] = output[i];
    }
}

/*
 * 基数排序
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
void RadixSort(int* arr, int n){
    int exp=0;    // 指数. 当对数组按各位进行排序时,exp=1;按十位进行排序时，exp=10；...
    int max = GetMax(arr, n);    // 数组a中的最大值

    // 从个位开始，对数组a按"指数"进行排序
    for (exp = 1; max/exp > 0; exp *= 10)
        CountSort(arr, n, exp);
}

int TestRadixSort1(){
    auto start = std::chrono::steady_clock::now();
    Print(a, sizeof(a)/ sizeof(a[0]));

    RadixSort(a, sizeof(a)/ sizeof(a[0]));

    Print(a, sizeof(a)/ sizeof(a[0]));

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__RADIX_SORT1__H__