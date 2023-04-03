#include "BucketSort1.hpp"
#include "BucketSort2.hpp"
#include "BucketSort3.hpp"
using namespace std;


/* 排序算法----桶排序
 *
 * 算法思想:
 * 1. 对值域进行分块,每块分别排序.由于每块元素不多,一般使用插入排序.如果使用稳定的内层排序,并且将元素插入桶中时不改变相对顺序,那么桶排序就是稳定的.
 *
 * 时间复杂度:
 * 期望复杂度为O(N)
 *
 * 算法特点:
 * 1. 适用于待排序数据值域较大但分布比较均匀的情况
 *
 * 思考:
 * 1. 桶排序最初始是计数排序
 * 2. 对桶数量进行分组控制,则进化为真正意义上的桶排序
 *
 * */


int main() {
    TestCount1();           //计数排序
    TestBucketSort2();      //桶排序(相当于原来的数缩小了)
    TestBucketSort3();      //桶排序(原来的数不用缩小)
}
