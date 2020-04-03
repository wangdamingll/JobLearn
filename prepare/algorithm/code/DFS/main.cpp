#include "Enumeration1.hpp"
#include "DFS1.hpp"
#include "DFS2.hpp"
#include <algorithm>
using namespace std;

/* 算法:搜索算法---深度优先搜索(DFS)
 *
 * 算法思想:
 *  1.不撞南墙不回头，递归调用自己
 *  2.理解DFS的关键:DFS在于解决"当下该如何做"，至于"下一步如何做"和"当下该如何做"是一样的
 *
 * DFS的基本模型
 * void dfs(int step){
 *      //判断边界
 *      //满足条件则返回
 *
 *      //尝试每一种可能
 *      for(int i=1;i<n;i++){
 *          //继续下一步
 *          dfs(step+1)
 *      }
 *
 *      //返回
 * }
 *
 * 注意事项:
 *  1.一定要注意边界判断条件
 *
 * 深度优先搜索算法的应用
 *  1.全排列系列问题(枚举算法也能解决)
 *  2.
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
    TestDFS1();         //数的全排列问题(dfs)
    TestDFS2();         //全排列问题变形
    TestEnumeration1(); //数的全排列问题(枚举)
}
