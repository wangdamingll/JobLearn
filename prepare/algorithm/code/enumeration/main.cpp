#include "Enumeration1.hpp"
#include "Enumeration2.hpp"
using namespace std;

/* 算法:枚举算法
 *
 * 算法思想:
 *  有序的去尝试每一种可能
 *
 * 注意事项:
 *  1.尽可能先做逻辑判断，减少枚举数字的范围，从而降低整体的时间复杂度
 *
 * 枚举算法的应用
 *  1.数的全排列系列问题:
 *  2.火柴棍问题
 * */

int main() {
    testEnumeration1(); //数的全排列问题
    testEnumeration2(); //火柴棍问题
    testEnumeration3();
}
