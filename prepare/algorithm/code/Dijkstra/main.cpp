#include "Dijkstra1.hpp"
#include "Dijkstra2.hpp"
using namespace std;


/* 图最短路径-----Dijkstra
 *
 * 图定义：
 * 简单的说,图就是由一些小圆点(称为顶点)和连接这些小圆点的直线(称为边)组成的.
 *
 * Dijkstra
 * 解决单源最短路问题
 * */

int main() {
    TestMapStore();    //图存储----邻接表存储法
    //TestDijkstra2();         //Dijkstra--单源最短路---邻接矩阵存储法
    //TestDijkstra3();         //Dijkstra--单源最短路---邻接表存储法(对于稀疏图的优化)
}