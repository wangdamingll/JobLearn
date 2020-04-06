#ifndef __BFS1__H__
#define __BFS1__H__

#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <array>

using namespace std;

/*迷宫问题----广度优先搜索算法(BFS)
 *
 * 问题描述:
 * 迷宫由n行m列的单元格组成(n和m都小于等于50)，每个单元格要么是空地，要么是障碍物。找到一条从迷宫的起点通往某个位置的最短路径。
 * 注意:障碍物是不能走的
 *
 * 思考:
 * 1.先用array模拟队列,实现广搜
 * */

int a1[51][51]={0}; //迷宫地图
int visit1[51][51]={0}; //有没有在路径里面
int n,m =0; //迷宫的行数和列数
int minStep = 999999; //最短路径
int startx,starty=0;//起点位置
int p,q=0;; //迷宫终点位置

//记录路径 array模拟栈
struct Pos{
    Pos() = default;
    Pos(int posx,int posy):x(posx),y(posy){}
    int x {0};
    int y {0};
};
std::array<Pos,51*51> que={};
int top=0;

/* 1 表示是障碍物
 * 0 表示可以通行
 * */
void CreateMap(){
    std::default_random_engine random(time(nullptr));
    std::uniform_int_distribution<int> dis(0,3);
    std::cout<<"请输入迷宫的行数和列数(中间以空格作为分隔符):";
    std::cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i==1&&j==1){
                a1[i][j]=0;//保证迷宫起点不能有障碍物
            }else{
                a1[i][j]=dis(random)/3;//为了让0出现的概率大些
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            std::cout<<a1[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void PrintPath(){
}

void BFS1(int x, int y,int step){





//    //到达终点
//    if(x==p && y==q){
//        if(step<minStep) {
//            minStep = step; //最短路径
//            PrintPath();    //最短线路
//        }
//        return;
//    }
//
//    //尝试每个坐标点
//    static int next[4][2]={
//            {0,1},  //往右
//            {1,0},  //往下
//            {0,-1}, //往左
//            {-1,0}  //往上
//    };
//    for(int k=0;k<4;k++){
//        int nextx = x+next[k][0];
//        int nexty = y+next[k][1];
//        if(nextx<1 || nextx>n || nexty<1 || nexty>m){ //越界判断
//            continue;
//        }
//        if(a1[nextx][nexty]==0 && visit1[nextx][nexty]==0) { //不是障碍物并且不再路线中
//            visit1[nextx][nexty] = 1; //加入路线中
//            Pos pos{nextx,nexty};   //压栈
//            que[top] = pos;
//            top++;
//
//            BFS1(nextx, nexty, step + 1);  //深搜
//
//            visit1[nextx][nexty] = 0;//从路径中删除
//            top--;//出栈
//        }
//    }
}

int TestBFS1(){
    //构造一个地图
    CreateMap();

    auto start = std::chrono::steady_clock::now();

    std::cout<<"请输入迷宫的起点x和起点位置y(中间以空格作为分隔符):";
    std::cin>>startx>>starty;
    std::cout<<"迷宫的起点位置:("<<startx<<","<<starty<<")"<<std::endl;

    std::cout<<"请输入迷宫的终点x和终点位置y(中间以空格作为分隔符):";
    std::cin>>p>>q;
    std::cout<<"迷宫的终点位置:("<<p<<","<<q<<")"<<std::endl;

    visit1[startx][starty]=1; //将起点标识在路径中

    BFS1(startx,starty,0);//深度优先算法

    if(minStep == 999999){
        std::cout<<"没有最短路径"<<std::endl;
    }else{
        std::cout<<"minStep:"<<minStep<<std::endl;
    }

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout<<"time:"<<time.count()<<"s"<<std::endl;

    return 0;
}


#endif //__BFS1__H__
