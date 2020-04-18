#include "MapCutPoint1.hpp"
using namespace std;


/* 图的割点----tarjan算法
 *
 * 图的相关概念:
 * 连通图:在无向图中,若任意两个顶点vi与vj都有路径相通,则称该无向图为连通图.
 * 图的割点:如果去掉一个点以及与它连接的边,该点原来所在的图被分成两部分(不连通),则称该点为割点.
 *
 * */


int main() {
    TestMapCutPoint1();         //图的割点-----tarjan算法
}
