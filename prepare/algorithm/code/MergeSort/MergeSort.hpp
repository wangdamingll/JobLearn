#ifndef __MERGE_SORT1__H__
#define __MERGE_SORT1__H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Merge(std::vector<int32_t>& vec, int32_t left, int32_t right, int32_t mid, std::vector<int32_t>& tmp)
{
    int32_t leftL = left; //左半部分左边
    int32_t leftR = mid;  //左半部分右边
    int32_t rightL = mid + 1; //右半部分左边
    int32_t rightR = right;   //右半部分右边

    int32_t len = 0;
    //先对共有部分进行合并
    while(leftL <= leftR && rightL <= rightR)
    {
        if(vec[leftL] < vec[rightL])
        {
            tmp[len++] = vec[leftL++];
        } else
        {
            tmp[len++] = vec[rightL++];
        }
    }

    //多余出来的合并
    while(leftL <= leftR)
    {
        tmp[len++] = vec[leftL++];
    }
    while(rightL <= rightR)
    {
        tmp[len++] = vec[rightL++];
    }

    //合并到原数列之中
    for(int32_t i = 0; i < len; i++)
    {
        vec[left + i] = tmp[i];
    }
}

void MerSort(std::vector<int32_t>& vec, int32_t left, int32_t right, std::vector<int32_t>& tmp)
{
    if(left >= right)
    {
        return;
    }
    int32_t mid = (left + right) / 2;
    MerSort(vec, left, mid, tmp);
    MerSort(vec, mid + 1, right, tmp);

    Merge(vec, left, right, mid, tmp);
}

#endif //__MERGE_SORT1__H__