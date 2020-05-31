#ifndef __QUICK_SELECT__H__
#define __QUICK_SELECT__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;

/*快速选择----在一组数据中选择第k小的元素
 *
 * 问题描述:
 * 选择第k小的元素:3 8 9 6 5 4 2 1
 *
 * */

constexpr int n1 = 8;
int h1[n1+1] ={0,3,8,9,6,5,4,2,1};

void Print(){
    for(int i=1;i<=n1;i++){
        std::cout<<h1[i]<<" ";
    }
    std::cout<<std::endl;
}

//交换
void Swap(int x,int y){
#if 1
    std::swap(h1[x],h1[y]);
#else
    int t = h1[x];
    h1[x] = h1[y];
    h1[y] = t;
#endif
}


//快速选择(快排变形)
void QuickSelect(int low,int hight,int k){
    if(low>=hight){//递归退出条件
        return ;
    }

    int i =low;     //哨兵i
    int j = hight;  //哨兵j
    int tmp = h1[i];//缓存基准数

    while(i!=j){    //当哨兵不相遇时
        while (h1[j]>=tmp && i<j){//向左找到第一个小于基准数的
            j--;
        }
        while(h1[i]<=tmp && i<j){//向右找到第一个大于基准数的
            i++;
        }
        if(i<j){//哨兵不相遇
            Swap(i,j);//交换
        }
    }

    //当哨兵相遇时,将i和基准数交换
    Swap(low,i);

    if(k<=i){
        QuickSelect(low,i-1,k);
    }else if(k>i+1){
        QuickSelect(i+1,hight,k);
    }
}

int TestQuickSelect(){
    auto start = std::chrono::steady_clock::now();
    Print();

    int k = 4;
    QuickSelect(1,n1,k);//快速排序

    Print();//会破坏原来数组

    std::cout<<"第"<<k<<"小数:"<<h1[k]<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__QUICK_SELECT__H__