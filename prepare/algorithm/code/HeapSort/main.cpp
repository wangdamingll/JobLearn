#include "HeapSort1.hpp"
#include "HeapSort2.hpp"
using namespace std;


/* 二叉树应用-----堆排序
 *
 * 堆定义：
 * 所有父结点都比子结点要小,符合这样特点的完全二叉树我们称为最小堆,反之,如果所有父结点都比子结点要大.这样的完全二叉树称为最大堆
 *
 * */


int main() {
    TestHeapSort1();         //堆排序---数据升序排序
    TestHeapSort2();         //堆排序---第K大(小)的数
}
