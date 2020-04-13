#include "BellmanFord1.hpp"
#include "BellmanFord2.hpp"
#include "BellmanFord3.hpp"
using namespace std;


/* 图最短路径-----Bellman-Ford
 *
 * 图定义：
 * 简单的说,图就是由一些小圆点(称为顶点)和连接这些小圆点的直线(称为边)组成的.
 *
 * Bellman-Ford
 * 解决单源最短路问题
 * */

int main() {
    TestMapStore();         //图存储----邻接表存储法
    TestBellmanFord2();     //Bellman-Ford--单源最短路---邻接矩阵存储法
    TestBellmanFord3();     //Bellman-Ford--判断图中有无负权回路
}