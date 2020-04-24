#include "BTreeEach.hpp"
#include "BTreeBroadCastEach.hpp"

using namespace BTreeEach1;
using namespace BTreeEach2;

/* 二叉树-----遍历
 *
 * */

int main() {
    BTreeEach1::TestBTreeEach();//二叉树深度优先遍历(递归)
    BTreeEach2::TestBTreeEach();//二叉树广度优先遍历
}
