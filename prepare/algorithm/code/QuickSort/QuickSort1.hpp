#ifndef __QUICK_SORT1__H__
#define __QUICK_SORT1__H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int32_t Division(std::vector<int32_t>& vec, int32_t left, int32_t right)
{
    int32_t base = vec[left];//保存基准值
    while(left < right)
    {
        //从右向左找到小于基准值的位置
        while(left < right && vec[right] >= base)
        {
            right--;
        }
        vec[left] = vec[right];

        //从左向右找大于base值的位置
        while (left < right && vec[left] <= base)
        {
            left++;
        }
        vec[right] = vec[left];
    }
    vec[left] = base;//填充基准值
    return  left;
}

void QuickSort(std::vector<int32_t>& vec, int32_t left, int32_t right)
{
    if(left < right)
    {
        int32_t base = Division(vec, left, right);//找到基准位置
        QuickSort(vec, left, base - 1);
        QuickSort(vec, base + 1, right);
    }
}


#endif //__QUICK_SORT1__H__