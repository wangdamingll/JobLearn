#ifndef __ENUMERATION1__H__
#define __ENUMERATION1__H__

#include <iostream>
#include <chrono>
using namespace std;

/* 全排列系列问题 -------枚举算法
 * 问题描述:
 * 坑爹的奥数
 * 口口口 + 口口口 = 口口口
 * 将1~9的数字填入上面9个口中，每个数字只能使用1次，使上面等式成立，请问有多少种组合？
 * 比如:173 + 286 = 459 就是一组组合
 * 注意:173 + 286 = 459 和 286 + 173 = 459 是同一个组合
 *
 * --------------------------------------------------------------------------
 *
 * 思考:
 * 1.每个空格枚举的数字范围是1~9,无法缩小范围
 * 2.采用标记法记录每个数字出现的次数，当总次数等于9时，满足要求(每个数字只出现一次)
 * 3.此类问题用枚举算法最突出的问题是时间复杂度为O(N^9)(下面的例子),所以枚举的范围大的时候，不是好方方法
 * */

int testEnumeration1(){
    int a[10] = {0};//每个空格的数字
    int total = 0;

    //time
    auto start = std::chrono::steady_clock::now();

    //枚举每个空格的数字
    for(a[1]=1;a[1]<10;a[1]++){
    for(a[2]=1;a[2]<10;a[2]++){
    for(a[3]=1;a[3]<10;a[3]++) {
    for(a[4]=1;a[4]<10;a[4]++) {
    for(a[5]=1;a[5]<10;a[5]++) {
    for(a[6]=1;a[6]<10;a[6]++) {
    for(a[7]=1;a[7]<10;a[7]++) {
    for(a[8]=1;a[8]<10;a[8]++) {
        for(a[9]=1;a[9]<10;a[9]++) {
            int sum = 0; //统计所有空格出现不同数字的个数
            int book[10] = {0};//标记法:标记每个数字出现的次数
            for(int i=1;i<10;i++){
                book[a[i]] = 1;
            }
            for(auto it : book){
                sum+=it;
            }

            if(sum==9 && (a[1]*100+a[2]*10+a[3]+a[4]*100+a[5]*10+a[6]==a[7]*100+a[8]*10+a[9])){//一个组合
                std::cout<<a[1]<<a[2]<<a[3]<<"+"<<a[4]<<a[5]<<a[6]<<"="<<a[7]<<a[8]<<a[9]<<std::endl;
                total++;
            }
        }
    }}}}}}}}

    auto end = std::chrono::steady_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout<<"total:"<<total/2<<std::endl;
    std::cout<<"time:"<<time.count()<<std::endl;
    return 0;
}


#endif