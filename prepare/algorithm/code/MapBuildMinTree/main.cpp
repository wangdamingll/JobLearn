#include "UnionFind1.hpp"
using namespace std;


/* 二叉树应用-----并查集
 *
 * 1.并查集定义:
 * 并查集实际上就是并集和查集的过程.集(集合)可以理解为一棵树,即一个根结点连着无数个子节点.并查集也称为不相交集数据结构.
 * 形象地来说,有点像"朋友圈":A和B是朋友,A和B就构成了一个朋友圈,C和D是朋友,C和D也构成了一个朋友圈,那么这时,如果B和C在成为了朋友,A、B、C、D就构成了一个大的朋友圈.
 *
 * 2.算法思想:
 * 并查集通过一个一维数组来实现,其本质是维护一个森林.刚开始的时候,森林的每个点都是孤立的,也可以理解为每个点就是一棵只有一个结点的树,
 * 之后通过一些条件,逐渐将这些树合并成一棵大树.其实合并的过程就 是"认爹"的过程.在"认爹"的过程中,要遵守"靠左"原则和"擒贼先擒王"原则.
 * 在每次判断两个结点是否已经在同一棵树中的时候(一棵树其实就是一个集合).也要注意必 须求其根源,中间父亲结点("小BOSS")是不能说明问题的,必须找到其祖宗(树的根结点),
 * 判断两个结点的祖宗是否是同一个根结点才行.
 *
 * 3.并查集遵循原则
 * "靠左"原则
 * "擒贼先擒王"
 *
 * 4.算法解决问题
 *  1)判断图中2个点是否已经连通问题(如:图的最小生成树---Kruskal算法中用到)
 *  2)"朋友圈"问题-------找出一堆数据中有联系的各个组等
 * */


int main() {
    TestUnionFind1();         //二叉树应用---并查集
}
