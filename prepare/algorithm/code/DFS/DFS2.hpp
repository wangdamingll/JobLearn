#ifndef __DFS2__H__
#define __DFS2__H__

#include <iostream>
#include <chrono>
using namespace std;

/*全排列系列问题----深度优先搜索算法(DFS)
 *
 * 问题描述:
 * string= "abc"有多少种排列？
 *
 * 思考:
 * 1.这其实和将a b c 放入3个格子里是差不多的
 * 2.下面例子的时间复杂度是多少？
 * T(N)=T(N-1)+O(N)  ----> O(N^2)
 * */


string str="abc";
int total2=0;
string a2[4]={};//存放a b c
int book2[4]={0};//表示a b c 是否在手中. 全排列系列问题变形

void DFS2(int step){
    //判断条件
    if(step>str.length()){
        for(int i=1;i<=str.length();i++){
            std::cout<<a2[i];
        }
        std::cout<<std::endl;
        total++;
        return;
    }

    //尝试每一种可能
    for(int i=0;i<str.length();i++){
        if(book2[i]==0){
            a2[step] = str[i];
            book2[i] =1;
            DFS2(step+1);
            book2[i]=0;
        }
    }
}


int TestDFS2(){
    auto start = std::chrono::steady_clock::now();

    DFS2(1);//第一步在abc的a位置

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"total:"<<total<<std::endl;
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS2__H__