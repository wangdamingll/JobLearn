#ifndef __HeapSort1__H__
#define __HeapSort1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
using namespace std;


/*堆排序----对整个数据进行排序---这里以最小堆为例
 *
 * 问题描述:
 * 对整个数据进行升序排序:3 8 9 6 5 4 2 1
 *
 * 算法思想:
 * 从小到大排序的时候不建立最小堆而建立最大堆,最大堆建立好后，最大的元素在h[1],因为我们的需求是从小到大排序,希望最大的放在最后,
 * 因此我们将h[1]和h[n]交换，此时h[n]就是数组中的最大的元素请注意,交换后还需将h[1]向下调整以保持堆的特性.OK,现在最大的元素已经归位.
 * 需要将堆的大小减1,即n--,然后再将h[1]和h[n]交换,并将h[1]向下调整.如此反复,直到堆的大小变成1为止.此时数组h中的数就已经是排序好的了.
 *
 * 时间复杂度:
 * O(NlogN)
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

//向下调整:往往在更新h[1]即第一个元素时,向下调整
void SiftDown(int i,int len){
    int flag =0;//需不需要继续调整
    int t =0; //记录最大值的编号
    while(i*2<=len&&flag==0){ //表示i节点有儿子(如有儿子必须是左子树),且需要调整
        t = i;//假设当前节点值最大
        if(h1[i]<h1[2*i]){//要求升序排序,就需要这里以最大堆为例
            t = 2*i;
        }

        if(2*i+1<=len && h1[t]<h1[2*i+1]){//存在右子树
            t = 2*i+1;
        }

        if(t!=i){//表示最大值有变动
            Swap(i,t);//交换i 和 t(最大值编号)
            i = t;
        } else{
            flag=1;
        }
    }
}

//向上调整:向堆中插入新元素时(实际上是插入到末尾),需要向上调整
void SiftUp(int i){
    int flag =0;
    if(i==1){   //是根顶点
        return ;
    }

    while(i!=1 && flag==0){ //i不是根顶点且需要在调整
        if(h1[i/2]<h1[i]){ //这里以最大堆为例
            Swap(i/2,i);
        } else{
            flag = 1;
        }
        i = i/2; //更新编号
    }

}

//创建堆
void CreatHeap(){
    for(int i=n1/2;i>=1;i--){//从最后一个非叶子节点开始调整,依次向上
        SiftDown(i,n1);     //n1为整个堆的大小,从最后一个非叶子节点开始,向下调整
    }
}

//堆排序
void HeapSort1(){
    Print();
    //创建堆
    CreatHeap();

    //堆排序
    int i=n1;
    while(i>1){
        Swap(1,i);       //交换元素
        SiftDown(1,--i); //注意--i,将最大值交换到末尾,堆的调整大小减1,调整前面的堆(从根向下调整)
    }

    Print();
}

int TestHeapSort1(){
    auto start = std::chrono::steady_clock::now();

    HeapSort1();//堆排序

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__HeapSort1__H__