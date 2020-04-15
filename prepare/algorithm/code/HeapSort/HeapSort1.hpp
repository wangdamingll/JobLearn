#ifndef __HeapSort1__H__
#define __HeapSort1__H__

#include <iostream>
#include <chrono>
using namespace std;


/*堆排序----对整个数据进行排序---这里以最小堆为例
 *
 * 问题描述:
 * 对整个数据进行升序排序:3 8 9 6 5 4 2 1
 *
 * 算法思想:
 * 从小到大排序的时候不建立最小堆而建立最大堆,最大堆建立好后，最大的元素在h[1],因为我们的需求是从小到大排序,希望最大的放在最后,
 * 因此我们将h[1]和h[n]交换，此时h[n]就是数组中的最大的元素请注意,交换后还需将h[1]向下调整以保持堆的特性.OK,现在最大的元素已经归位.
 * 需要将堆的大小减1,即n--,然后再将h[1]和h[n]交换,并将h[1]向下调整.如此反复,直到堆的大小变成1为止.此时数组h中的数就已经是排序好的了.
 *
 * 时间复杂度:
 * O(NlogN)
 *
 * */



int TestHeapSort1(){
    auto start = std::chrono::steady_clock::now();




    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__HeapSort1__H__