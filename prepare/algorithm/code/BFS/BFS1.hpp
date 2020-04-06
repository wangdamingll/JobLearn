#ifndef __BFS1__H__
#define __BFS1__H__

#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <array>
#include <stack>

using namespace std;

/*迷宫问题----广度优先搜索算法(BFS)
 *
 * 问题描述:
 * 迷宫由n行m列的单元格组成(n和m都小于等于50)，每个单元格要么是空地，要么是障碍物。找到一条从迷宫的起点通往某个位置的最短路径。
 * 注意:障碍物是不能走的
 *
 * 思考:
 * 1.先用array模拟队列,实现广搜,也可以直接用std::queue
 * 2.同样的迷宫问题,广搜的时间复杂度要比深搜小很多
 * 3.广度优先搜索的时间复杂度为 O(V+E)，V为顶点个数，E为边的条数。
 * 针对一个所有顶点都是联通的图，E 肯定要大于 V-1，所以时间复杂度可以简写为 O(V)
 * 4.空间复杂度为O(V),V为顶点个数
 * */

int a1[51][51]={0}; //迷宫地图
int visit1[51][51]={0}; //有没有在路径里面
int n,m =0; //迷宫的行数和列数
int startx,starty=0;//起点位置
int p,q=0;; //迷宫终点位置

//记录路径 array模拟队列
struct Pos{
    Pos() = default;
    Pos(int posx,int posy,int step,int findex):x(posx),y(posy),s(step),f(findex){}
    int x {0};
    int y {0};
    int s {0};//步数
    int f {0};//父节点在队列中的索引
};
std::array<Pos,51*51> que={};
//Pos que[51*51]={};
int head =0;//队列头
int tail =0;//队列尾

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
    //得到所有父节点的index
    std::stack<int> stack;
    stack.push(tail-1);

    int index = tail-1;
    while(que[index].f!=0){
        stack.push(que[index].f);
        index = que[index].f;
    }

    //输出路径
    int first = 1;
    while (!stack.empty()){
        index=stack.top();
        stack.pop();
        if(first==1){
            std::cout<<"("<<que[index].x<<","<<que[index].y<<")";
        }else{
            std::cout<<"->("<<que[index].x<<","<<que[index].y<<")";
        }
        first++;
    }
    std::cout<<std::endl;
}

void BFS1(){
    int flag=0; //表示有木有找到

    //队列初始化
    head = tail = 1;
    que[tail].x = startx;
    que[tail].y = starty;
    que[tail].s = 0;
    que[tail].f = 0;
    tail++;

    visit1[startx][starty]=1; //将起点标识在路径中

    //广搜
    while(head<tail){//表示队列不为空
        //枚举周围4点
        static int next[4][2]={
                {0,1},  //往右
                {1,0},  //往下
                {0,-1}, //往左
                {-1,0}  //往上
        };
        for(int k=0;k<4;k++){
            int tx = que[head].x + next[k][0];
            int ty = que[head].y + next[k][1];

            if(tx<1 || tx>n || ty<1 || ty>m){//边界
                continue;
            }

            if(a1[tx][ty]==0 && visit1[tx][ty]==0){//不是障碍物并且不再路线中
                visit1[tx][ty]=1; //广搜只加一次
                //加入队列
                que[tail].x = tx;
                que[tail].y = ty;
                que[tail].s = que[head].s+1;//父节点步数加1
                que[tail].f = head;
                tail++;
            }

            if(tx==p && ty==q){//找到目标点
                flag=1;
                break;
            }
        }

        if(flag==1){
            break;
        }

        head++;//弹出队列
    }

    if(flag==1){
        std::cout<<"找到了目标点:step="<<que[tail-1].s<<std::endl;//tail此时在队尾的下一个位置
        PrintPath();
    } else{
        std::cout<<"没有找到目标点"<<std::endl;
    }
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

    BFS1(); //广搜

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout<<"time:"<<time.count()<<"s"<<std::endl;

    return 0;
}


#endif //__BFS1__H__
