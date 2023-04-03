#include "QuickSort1.hpp"
using namespace std;


/* 排序算法----快速排序
 *
 * 算法思想:
 * 1. 二分法思想
 * 2. 递归思想
 *
 * 时间复杂度:
 * 最坏的时间复杂度:O(N^2)
 * 平均时间复杂度:O(NlogN)
 *
 * 算法特点:
 * 1.数据越有序,越快
 *
 * 思考:
 * 1.需要设置2个哨兵,左边的起始位置为哨兵i,右边的起始位置为哨兵j
 * 2.当基准数选在左边第一个数时,必然是哨兵j先向左移动
 *
 * */


int main()
{
    std::vector<int32_t> vec{6, 4, 8, 9, 2, 3, 1};

    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
        std::cout<<it<<",";
        return 0;
    });
    std::cout <<std::endl;
    int32_t size = vec.size();

    //快排
    QuickSort(vec, 0, size - 1);

    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
        std::cout<<it<<",";
        return 0;
    });
    std::cout <<std::endl;
    return 0;
}