#ifndef __QUICK_SELECT__H__
#define __QUICK_SELECT__H__

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*快速选择----在一组数据中选择第k小的元素
 *
 * 问题描述:
 * 选择第k小的元素:3 8 9 6 5 4 2 1
 *
 * */

int32_t Divide(std::vector<int32_t>& vec, int32_t left, int32_t right)
{
    int32_t base = vec[left];//保存基准值
    while(left < right)
    {
        while(left < right && vec[right] >= base)//从右向左找比基准值小的
        {
            right--;
        }
        vec[left] = vec[right];//交换

        while(left < right && vec[left] <= base)//从左向右找比基准值大的
        {
            left++;
        }
        vec[right] = vec[left];//交换
    }
    vec[left] = base;//基准值复位
    return left;
}

int32_t QuickSelect(std::vector<int32_t>& vec, int32_t left, int32_t right, int32_t k)
{
    if(left == right)
    {
        return vec[left];
    }

    int32_t base = Divide(vec, left, right);

    if(k == base)
    {
        return vec[base];
    }
    else if(k < base)
    {
        return QuickSelect(vec, left , base - 1, k);
    } else
    {
        return QuickSelect(vec, base + 1, right, k);
    }
}

int TestQuickSelect()
{
    std::vector<int32_t> vec{3, 2, 7, 8, 9, 1, 0};
    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
       std::cout<<it<<",";
       return 0;
    });
    std::cout<<std::endl;

    int32_t k = 2;
    int32_t target = QuickSelect(vec, 0, vec.size() - 1, k - 1);//k - 1:是算法要求这样的  <-- 第k小的数
    //int32_t target = QuickSelect(vec, 0, vec.size() - 1, vec.size() - k);//<-- 第k大的数

    //会破坏原数组
    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
        std::cout<<it<<",";
        return 0;
    });
    std::cout<<std::endl;

    std::cout<<"第"<<k<<"小/大数:"<<target<<std::endl;

    return 0;
}


#endif //__QUICK_SELECT__H__