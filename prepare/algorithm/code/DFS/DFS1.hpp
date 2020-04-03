#ifndef __DFS__H__
#define __DFS__H__

#include <iostream>
#include <chrono>
using namespace std;

/*不撞南墙不回头----深度优先搜索算法(DFS)
 *
 * 问题描述:
 * 坑爹的奥数
 * 口口口 + 口口口 = 口口口
 * 将1~9的数字填入上面9个口中，每个数字只能使用1次，使上面等式成立，请问有多少种组合？
 * 比如:173 + 286 = 459 就是一组组合
 * 注意:173 + 286 = 459 和 286 + 173 = 459 是同一个组合
 * */

int a[10]={0};   //代表9个格子
int book[10]={0};//表示1~9个数字是否还在手里
int total = 0;  //记录有多少种组合

//万能的搜索------深度优先算法
void DFS1(int step){
    //判断边界:表示目前在第10个格子位置上，意味着前面9个格子已经放好了数字
    if(step == 10){
        //满足等式条件
        if(a[1]*100+a[2]*10+a[3] + a[4]*100+a[5]*10+a[6] == a[7]*100+a[8]*10+a[9]){
            std::cout<<a[1]<<a[2]<<a[3]<<"+"<<a[4]<<a[5]<<a[6]<<"="<<a[7]<<a[8]<<a[9]<<std::endl;
            total++;
        }
        return;
    }

    //尝试每种可能:在第step个格子位置上,从1~9个数字中选择一个放进格子中，但是不是每种都能成功的，因为不是每个数字都在手中
    for(int i=1;i<10;i++){
        if(book[i]==0){ //等于0 表示该数字还在手里
            a[step] = i;//将该数字放在格子里
            book[i] = 1;//表示该数字不在手里了
            DFS1(step+1);//继续往前一步，到下一个格子位置上
            book[i]=0;       //不到南墙不回头，当到第10个格子位置时，手里已经没有数字了，需要回头了(后退一步)，并且把该位置上的数字拿到手中
        }
    }
}

int TestDFS1(){
    auto start = std::chrono::steady_clock::now();

    DFS1(1); //站在第一个格子位置

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"total:"<<total/2<<std::endl;
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__DFS__H__