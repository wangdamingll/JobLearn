#include "BipartiteMapMaxMatch1.hpp"
#include "BipartiteMapMaxMatch2.hpp"
using namespace std;


/* 二分图最大匹配
 *
 * 图的相关概念:
 * 二分图:如果一个图的所有顶点可以被分为X和Y两个集合,并且所有边的两个顶点恰好一个属于集合X,另一个属于集合Y,即每个集合内的顶点没有边相连,那么此图就是二分图.
 * 无权二分图:没有权重
 * 待权权二分图:有边权
 *
 * */


int main() {
    TestBipartiteMapMaxMatch1();         //无权二分图最大匹配---匈牙利算法
    TestBipartiteMapMaxMatch2();         //带权二分图最大匹配---KM算法(acm)
}
