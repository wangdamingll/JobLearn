#include "Enumeration1.hpp"
#include "Enumeration2.hpp"
#include "Enumeration3.hpp"
#include <algorithm>
using namespace std;

/* 算法:枚举算法
 *
 * 算法思想:
 *  有序的去尝试每一种可能
 *
 * 注意事项:
 *  1.尽可能先做逻辑判断，减少枚举数字的范围和需要枚举的个数，从而降低整体的时间复杂度
 *
 * 枚举算法的应用
 *  1.全排列系列问题:
 *  2.火柴棍问题
 * */

 void STL(){
    int s1[]={1,2,3};
    /**下面为next_permutation的用法::升序*/
    do{
        printf("%d %d %d\n",s1[0],s1[1],s1[2]);
    }while(next_permutation(s1,s1+3));

    std::cout<<"------------------"<<std::endl;

    int s2[]={3,2,1};
    /**下面为prev_permutation的用法:降序*/
    do{
        printf("%d %d %d\n",s2[0],s2[1],s2[2]);
    }while(prev_permutation(s2,s2+3));

}

int main() {
    STL();              //STL实现
    TestEnumeration1(); //全排列问题
    TestEnumeration2(); //火柴棍问题
    TestEnumeration3();
    TestEnumeration4(); //全排列问题变形
}
