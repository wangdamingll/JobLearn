#ifndef __BELLMAN_FORD1__H__
#define __BELLMAN_FORD1__H__

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;


/* 图存储-----邻接表存储法
 *
 * 问题描述:
 * 下面有一组数据(有向图),用邻接表存储法,将这个有向图的信息存储起来
 * 说明:
 * 1. 有向图的概念
 * 边有方向的图称为有向图
 * 2. 有向图数据
 * 第一行两个整数n m,n表示顶点个数(顶点编号为1~n),m表示边的条数. 接下来m行,每行有3个数x y z,表示顶点x到顶点y的边的权值为z
 *
 * 4 5
 * 1 4 9
 * 4 3 8
 * 1 2 5
 * 2 4 6
 * 1 3 7
 *
 * 存储方法思想:
 * 这种方法为每个顶点i(i从1-n)都设置了一个链表,里面保存了从顶点i出发的所有的边(这里用first和next数组来实现,待会再来详细介绍).
 * 首先我们需要为每一条边进行1~m的编号.用u、v和w三个数组来记录每条边的信息,即u[i] v[i]和w[i]表示第i条边是从第u[i]号顶点到v[i]号顶点(u[i]->v[i]),
 * 且权值为w[i].first数组的1~n号单元格分别用来存储1~n号顶点的第一条边的编号,初始的时候因为没有边加入所以都是-1.
 * 即first[u[i]]保存顶点u[i]的第一条边的编号,next[i]存储"编号为i的边"的"下一条边"的编号.
 *
 * 思考:
 * 1. 这个方法的空间复杂度O(M),时间复杂度也是O(M),M为边数
 * 2. 如果一个图是稀疏图(把M远小于N^2的图称为稀疏图,而M相对较大的图称为稠密图)的话,M要远小于N^2,因此稀疏图选用邻接表来存储要比用邻接矩阵来存储好很多
 * */


static int n=4; //图的顶点数量(上面的数据)
static int m=5; //图的边数量(上面的数据)

//比m大1 分别存储顶点i到顶点j的权值,这里直接初始化上图数据
static int u1[6]={0,1,4,1,2,1};//顶点i
static int v1[6]={0,4,3,2,4,3};//顶点j
static int w1[6]={0,9,8,5,6,7};//权值

//比n大1 分别存储编号i的第一条边的编号和编号i的边的下一条边的编号
int first1[5]={0};

//比m大1 存储边
int next1[6]={0};

//存储图
void StoreMap1(){
    //初始化first数组,-1表示没有出边
    for(auto& it : first1){
        it = -1;
    }

    //由于u v w 已经提前赋值好了,否则正常应该按行读取上面的数据,然后依次赋值
    for(int i=1;i<=m;i++){ //读取每一行数据给first和next赋值
        //邻接表核心语句
        next1[i] = first1[u1[i]];
        first1[u1[i]] = i;
    }
}

//遍历图的每一条边
void PrintMap1(){
    for(int i=1;i<=n;i++){//遍历first中所有的顶点
        int k = first1[i];//取出顶点
        while(k!=-1){//从next中遍历出顶点的所有出边
            std::cout<<u1[k]<<" "<<v1[k]<<" "<<w1[k]<<std::endl;
            k=next1[k];
        }
    }
}
//图存储
int TestMapStore(){
    auto start = std::chrono::steady_clock::now();

    StoreMap1();//存储图

    PrintMap1();//遍历图

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

#endif //__BELLMAN_FORD1__H__