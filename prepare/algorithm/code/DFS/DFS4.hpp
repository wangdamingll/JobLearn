#ifndef __DFS4__H__
#define __DFS4__H__

#include <iostream>
#include <chrono>
using namespace std;

/*独立子图问题----深度优先搜索算法(DFS)-----种子填充法
 *
 * 问题描述:
 * 有一个二维数组,0表示海洋,其他数字代表陆地,求图中有多少个独立的岛屿?(相邻的全部是不为0的格子)
 *
 * 思考:
 * 1.采用深度优先算法遍历整个二维数组
 * 2.采用种子填充法对不为0的格子进行染色(种子填充法)
 * */


int a4[51][51]={0}; //地图
int visit4[51][51]={0}; //有没有在路径里面
int n4,m4 =0; //地图的行数和列数

//打印地图
void PrintMap4(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a4[i][j]>=0){
                std::cout<<" "<<a4[i][j]<<" ";
            } else{
                std::cout<<a4[i][j]<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

/* 0 表示海洋,无法通过,其他数字代表陆地,可以通过
 * */
void CreateMap4(){
    std::default_random_engine random(time(nullptr));
    std::uniform_int_distribution<int> dis(0,5);
    std::cout<<"请输入地图的行数和列数(中间空格作为分隔符):";
    std::cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a4[i][j]=dis(random)/2;//让出现海洋的机会大些
        }
    }

    PrintMap4();
}

//深搜着色
void DFS4(int x,int y,int color){

    a4[x][y] = color;//染色

    //尝试每个坐标点
    static int next[4][2]={
            {0,1},  //往右
            {1,0},  //往下
            {0,-1}, //往左
            {-1,0}  //往上
    };
    for(int k=0;k<4;k++){
        int tx = x+next[k][0];
        int ty = y+next[k][1];

        if(tx<1 || tx>n || ty<1 || ty>m){//边界
            continue;
        }

        if(a4[tx][ty]>0 && visit4[tx][ty]==0){//是陆地且没有访问过
            visit4[tx][ty] = 1;//标记
            //sum++; 这里也可以统计出每个独立子图的大小或者所有独立子图的和的大小,注意这里DFS4()回溯的时候不需要取消标记
            DFS4(tx,ty,color);
            //不需要取消标记
        }
    }
}


int TestDFS4(){
    auto start = std::chrono::steady_clock::now();

    CreateMap4();

    //遍历整个地图 找出不为0的格子执行深搜染色
    int num =0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a4[i][j]>0){ //是陆地
                num--;
                visit4[i][j] = 1;//加入路径中
                DFS4(i,j,num);//深搜
            }
        }
    }

    std::cout<<"独立子图的个数:"<<-num<<std::endl;
    PrintMap4();//染色后的地图

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS4__H__