#include "MergeSort.hpp"
using namespace std;


/* 排序算法----归并排序
 *
 * 解决问题
 * 1. 排序问题
 * 2. 求逆序对的个数
 *
 * 时间复杂度:
 * O(NlogN)
 *
 * 算法思想:
 * "分治"思想
 * 递归思想
 *
 * 算法特点:
 * 1. 归并排序 = 归并排序主体递归 + 合并算法
 * 2. 归并排序的主体部分的temp参数是主调函数分配内存
 * 3. 合并其实是递归回溯的时候自下而上的合并
 * 4. 该排序可以说是以空间换时间的排序算法
 * 5. 稳定排序
 *
 * 思考:
 *
 *
 * */


int main()
{
    std::vector<int32_t> vec{3,8,9,6,5,4,2,1};
    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
        std::cout<<it<<",";
        return 0;
    });
    std::cout <<std::endl;

    int32_t size = vec.size();
    std::vector<int32_t> tmp;
    tmp.resize(size);

    MerSort(vec, 0, size - 1, tmp);

    std::for_each(vec.begin(), vec.end(), [](int32_t it)->int {
        std::cout<<it<<",";
        return 0;
    });
    std::cout <<std::endl;
    return 0;
}
