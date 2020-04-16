#ifndef __HeapSort2__H__
#define __HeapSort2__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

/*堆排序----对数据的第K大(小)的数
 *
 * 问题描述:
 * 有数据如:3 8 9 6 5 4 2 1,求第K大(小)的数
 *
 * 算法思想:
 * 1. 求一个数列中第K大的数,只需要建立一个大小为K的最小堆,堆顶就是第K大的数
 * 2. 求一个数列中第K小的数,只需要建立一个大小为K的最大堆,堆顶就是第K小的数
 *
 * 时间复杂度:
 * O(NlogK),N为全部数据个数,K为第K的数量
 *
 * 思考
 * 源数据:3 8 9 6 5 4 2 1
 * 升序:1  2  3  4  5  6  8  9
 *      --->              <---
 *      第K小             第K大
 *      最大堆            最小堆
 *
 * 1. 在源数据中任意取K个数,初始化为最大堆(最小堆)
 * 2. 第K大的数(最小堆):依次取剩下的数,如果当前的数比堆顶的数小,不需要处理,如果比堆顶的数大,则用这个数替换堆顶的数,用此数替换为堆顶,然后调整堆
 * 3. 第K小的数(最大堆):依次取剩下的数,如果当前的数比堆顶的数大,不需要处理,如果比堆顶的数小,则用这个数替换堆顶的数,用此数替换为堆顶,然后调整堆
 * */

constexpr int n2 = 8;
int h2[n2+1] ={0,3,8,9,6,5,4,2,1};
int k2=0; //K
int tmp2[n2+1] ={0};

void Print2(int* arr,int size){
    for(int i=1;i<=size;i++){
        if(arr[i]==0){
            continue;
        }
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}

//交换
void Swap2(int* arr,int x,int y){
#if 1
    std::swap(arr[x],arr[y]);
#else
    int t = arr[x];
    arr[x] = arr[y];
    arr[y] = t;
#endif
}

//向下调整:往往在更新arr[1]即第一个元素时,向下调整
void SiftDown2(int* arr, int i,int len){
    int flag =0;//需不需要继续调整
    int t =0; //记录最小值的编号
    while(i*2<=len&&flag==0){ //表示i节点有儿子(如有儿子必须是左子树),且需要调整
        t = i;//假设当前节点值最小
        if(arr[i]>arr[2*i]){//就需要这里以最小堆为例
            t = 2*i;
        }

        if(2*i+1<=len && arr[t]>arr[2*i+1]){//存在右子树
            t = 2*i+1;
        }

        if(t!=i){//表示最小值有变动
            Swap2(arr,i,t);//交换i 和 t(最小值编号)
            i = t;
        } else{
            flag=1;
        }
    }
}

//向上调整:向堆中插入新元素时(实际上是插入到末尾),需要向上调整
void SiftUp2(int i){
    int flag =0;
    if(i==1){   //是根顶点
        return ;
    }

    while(i!=1 && flag==0){ //i不是根顶点且需要在调整
        if(tmp2[i/2]>tmp2[i]){ //这里以最小堆堆为例
            Swap2(tmp2,i/2,i);
        } else{
            flag = 1;
        }
        i = i/2; //更新编号
    }

}

//求第K大(小)的数:这里以求第K大的数为例,需要建立最小堆
void HeapSortK21(){
    Print2(h2,sizeof(h2)/sizeof(int));

    std::cout<<"请输入K(1<=K<=8):";
    std::cin>>k2;

    for(int i=1;i<=n2;i++){
        if(i<=k2){//从源数据中任意取K个数,创建最小堆
            tmp2[i] = h2[i];
            SiftUp2(i);
        }

        if(i>k2){//对源数据剩下的数据进行处理
            if(h2[i]>tmp2[1]){//比堆顶的数大,则替换堆顶
                tmp2[1] = h2[i];
                SiftDown2(tmp2,1,k2);//对整个堆进行向下调整
            }
        }
    }

    std::cout<<"第"<<k2<<"大的数:"<<tmp2[1]<<std::endl;
}

//-------------------------------------------------------------------------------------------

//求第K大(小)的数:这里以求第K大的数为例,需要建立最小堆
void HeapSortK22(){
    Print2(h2,sizeof(h2)/sizeof(int));

    std::cout<<"请输入K(1<=K<=8):";
    std::cin>>k2;

    std::vector<int> tmpV;
    for(int i=1;i<=n2;i++){
        if(i<=k2){//从源数据中任意取K个数
            tmpV.push_back(h2[i]);
        }

        if(i==k2){//创建最小堆
            std::make_heap(tmpV.begin(),tmpV.end(),std::greater<int>{});
        }

        if(i>k2){//对源数据剩下的数据进行处理
            if(h2[i]>tmpV[0]){//比堆顶的数大,则替换堆顶
#if 0
                tmpV[0] = h2[i];
                std::make_heap(tmpV.begin(),tmpV.end(),std::greater<int>{});//初始化堆需要从最后一个非叶子节点开始调整知道根节点,这里不需要遍历这些元素
#else
                tmpV[0] = h2[i];//更新堆顶元素
                std::swap(tmpV[0],tmpV[k2-1]);//将堆顶的元素和堆尾互换
                std::push_heap(tmpV.begin(),tmpV.end(),std::greater<int>{});//向上调整堆
#endif
            }
        }
    }

    std::cout<<"第"<<k2<<"大的数:"<<tmpV[0]<<std::endl;
}

int TestHeapSort2(){
    auto start = std::chrono::steady_clock::now();

    HeapSortK21();//第K大的数---自实现堆算法

    HeapSortK22();//第K大的数----标准库

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__HeapSort2__H__