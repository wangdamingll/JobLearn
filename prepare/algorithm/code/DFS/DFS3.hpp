#ifndef __DFS3__H__
#define __DFS3__H__

#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <array>
using namespace std;

/*迷宫问题----深度优先搜索算法(DFS)
 *
 * 问题描述:
 * 迷宫由n行m列的单元格组成(n和m都小于等于50)，每个单元格要么是空地，要么是障碍物。找到一条从迷宫的起点通往某个位置的最短路径。
 * 注意:障碍物是不能走的
 *
 * 思考:
 * 1.这里不但要输出最短路径，还要把最短路线输出出来
 * */



int a3[51][51]={0}; //迷宫地图
int book3[51][51]={0}; //有没有在路径里面
struct Pos{
public:
    Pos() = default;
    Pos(int x,int y,int fx,int fy){
        this->x = x;
        this->y = y;
        this->fx = fx;
        this->fy = fy;
    }
public:
    int x {0}; //当前位置行数
    int y {0}; //当前位置列数
    int fx {0};//当前位置父节点行数
    int fy {0};//当前位置父节点列数
};

/* 1 表示是障碍物
 * 0 表示可以通行
 * */
void CreateMap(){
    std::default_random_engine random(time(nullptr));
    std::uniform_int_distribution<int> dis(0,3);
    int n,m=0;
    std::cout<<"请输入迷宫的行数:";
    std::cin>>n;
    std::cout<<"请输入迷宫的列数:";
    std::cin>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0&&j==0){
                a3[i][j]=0;//保证迷宫起点不能有障碍物
            }else{
                a3[i][j]=dis(random)/3;//为了让0出现的概率大些
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            std::cout<<a3[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

//待完善
void DFS(int x,int y,int step){
    //判断条件
    //退出

    //尝试每一种可能
    //DFS(step+1)

    //退出
}

int TestDFS3(){
    //构造一个地图
    CreateMap();

    auto start = std::chrono::steady_clock::now();

    Pos startPos;
    std::cout<<"请输入迷宫的起点x:";
    std::cin>>startPos.x;
    std::cout<<"请输入迷宫的起点y:";
    std::cin>>startPos.y;

    book3[startPos.x][startPos.y]=1; //将起点标识在路径中

    DFS(startPos.x,startPos.y,0);//深度优先算法

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS3__H__