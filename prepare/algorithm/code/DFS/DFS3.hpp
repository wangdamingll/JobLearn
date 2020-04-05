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
 * 1.这里我自行测试过，有时候当地图比较大时，我测试的是10行10列，minStep计算有时候是错误的，并且有时候还会无限循环下去，暂时没有找出来原因
 * */



int a3[51][51]={0}; //迷宫地图
int book3[51][51]={0}; //有没有在路径里面
int n,m =0; //迷宫的行数和列数
int minStep = 999999; //最短路径
int startx,starty=0;//起点位置
int p,q=0;; //迷宫终点位置

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
                a3[i][j]=0;//保证迷宫起点不能有障碍物
            }else{
                a3[i][j]=dis(random)/3;//为了让0出现的概率大些
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            std::cout<<a3[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

//待完善
void DFS3(int x, int y,int step){
    std::cout<<"("<<x<<","<<y<<") ("<<p<<","<<q<<")"<<std::endl;
    //到达终点
    if(x==p && y==q){
        if(step<minStep){
            minStep = step;
        }
        return;
    }

    //尝试每个坐标点
    static int next[4][2]={
            {0,1},  //往右
            {1,0},  //往下
            {0,-1}, //往左
            {-1,0}  //往上
    };
    for(int k=0;k<4;k++){
        int nextx = x+next[k][0];
        int nexty = y+next[k][1];
        if(nextx<1 || nextx>n || nexty<1 || nexty>m){ //越界判断
            continue;
        }
        if(a3[nextx][nexty]==0 && book3[nextx][nexty]==0) { //不是障碍物并且不再路线中
            book3[nextx][nexty] = 1; //加入路线中
            DFS3(nextx, nexty, step + 1);  //深搜
            book3[nextx][nexty] = 0;//从路径中删除
        }
    }
}

int TestDFS3(){
    //构造一个地图
    CreateMap();

    auto start = std::chrono::steady_clock::now();

    std::cout<<"请输入迷宫的起点x和起点位置y(中间以空格作为分隔符):";
    std::cin>>startx>>starty;
    std::cout<<"迷宫的起点位置:("<<startx<<","<<starty<<")"<<std::endl;

    std::cout<<"请输入迷宫的终点x和终点位置y(中间以空格作为分隔符):";
    std::cin>>p>>q;
    std::cout<<"迷宫的终点位置:("<<p<<","<<q<<")"<<std::endl;

    book3[startx][starty]=1; //将起点标识在路径中

    DFS3(startx,starty,0);//深度优先算法

    if(minStep == 999999){
        std::cout<<"没有最短路径"<<std::endl;
    }else{
        std::cout<<"minStep:"<<minStep<<std::endl;
    }

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS3__H__



//#ifndef __DFS3__H__
//#define __DFS3__H__
//
//#include <iostream>
//#include <chrono>
//#include <random>
//#include <ctime>
//#include <array>
//using namespace std;
//
///*迷宫问题----深度优先搜索算法(DFS)
// *
// * 问题描述:
// * 迷宫由n行m列的单元格组成(n和m都小于等于50)，每个单元格要么是空地，要么是障碍物。找到一条从迷宫的起点通往某个位置的最短路径。
// * 注意:障碍物是不能走的
// *
// * 思考:
// * 1.这里不但要输出最短路径，还要把最短路线输出出来
// * */
//
//struct Pos{
//public:
//    Pos() = default;
//    Pos(int x,int y,int fx,int fy){
//        this->x = x;
//        this->y = y;
//        this->fx = fx;
//        this->fy = fy;
//    }
//
//    bool operator ==(const Pos& another) const{
//        return(this->x==another.x&&this->y==another.y);
//    }
//public:
//    int x {0}; //当前位置行数
//    int y {0}; //当前位置列数
//    int fx {0};//当前位置父节点行数
//    int fy {0};//当前位置父节点列数
//};
//
//int a3[51][51]={0}; //迷宫地图
//int book3[51][51]={0}; //有没有在路径里面
//int n,m =0; //迷宫的行数和列数
//int minStep = 999999; //最短路径
//Pos finalPos;; //迷宫终点位置
//
///* 1 表示是障碍物
// * 0 表示可以通行
// * */
//void CreateMap(){
//    std::default_random_engine random(time(nullptr));
//    std::uniform_int_distribution<int> dis(0,3);
//    std::cout<<"请输入迷宫的行数和列数(中间以空格作为分隔符):";
//    std::cin>>n>>m;
//
//    for(int i=0;i<n;i++){
//        for(int j=0;j<m;j++){
//            if(i==0&&j==0){
//                a3[i][j]=0;//保证迷宫起点不能有障碍物
//            }else{
//                a3[i][j]=dis(random)/3;//为了让0出现的概率大些
//            }
//        }
//    }
//
//    for(int i=0;i<n;i++){
//        for(int j=0;j<m;j++){
//            std::cout<<a3[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
//}
//
////待完善
//void DFS3(const Pos pos,int step){
//    //到达终点
//    if(pos == finalPos){
//        if(step<minStep){
//            minStep = step;
//        }
//        return;
//    }
//
//    static int next[4][2]={
//            {0,1},  //往右
//            {1,0},  //往下
//            {0,-1}, //往左
//            {-1,0}  //往上
//    };
//
//    //尝试每个坐标点
//    for(int k=0;k<4;k++){
//        Pos nextPos {pos.x+next[k][0],pos.y+next[k][1],pos.x,pos.y};
//        if(nextPos.x<1 || nextPos.x>n || nextPos.y<1 || nextPos.y>m){ //越界判断
//            continue;
//        }
//        if(a3[nextPos.x][nextPos.y]==0 && book3[nextPos.x][nextPos.y]==0){ //不是障碍物并且不再路线中
//            book3[nextPos.x][nextPos.y]=1; //加入路线中
//            DFS3(nextPos,step+1);  //深搜
//            book3[nextPos.x][nextPos.y]=0;//从路径中删除
//        }
//    }
//}
//
//int TestDFS3(){
//    //构造一个地图
//    CreateMap();
//
//    auto start = std::chrono::steady_clock::now();
//
//    Pos startPos;
//    std::cout<<"请输入迷宫的起点x和起点位置y(中间以空格作为分隔符):";
//    std::cin>>startPos.x>>startPos.y;
//    std::cout<<"迷宫的起点位置:("<<startPos.x<<","<<startPos.y<<")"<<std::endl;
//
//    std::cout<<"请输入迷宫的终点x和终点位置y(中间以空格作为分隔符):";
//    std::cin>>finalPos.x>>finalPos.y;
//    std::cout<<"迷宫的终点位置:("<<finalPos.x<<","<<finalPos.y<<")"<<std::endl;
//
//    book3[startPos.x][startPos.y]=1; //将起点标识在路径中
//
//    DFS3(startPos,0);//深度优先算法
//
//    if(minStep == 999999){
//        std::cout<<"没有最短路径"<<std::endl;
//    }else{
//        std::cout<<"minStep:"<<minStep<<std::endl;
//    }
//
//    auto end = std::chrono::steady_clock::now();
//    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
//    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;
//
//    return 0;
//}
//
//
//#endif //__DFS3__H__