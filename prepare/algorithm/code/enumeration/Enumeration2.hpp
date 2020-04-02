#ifndef __ENUMERATION2__H__
#define __ENUMERATION2__H__

#include <iostream>
#include <sstream>
#include <chrono>
using namespace std;

/* 火柴棍等式问题:
 *
 * 问题描述:
 * 有一组数字:0 1 2 3 4 5 6 7 8 9,分别拼成上面数字所需的火柴棍个数为:6 2 5 5 4 5 6 3 7 6,
 * 希望拼成形如:A+B=C的等式，A B C均是用火柴棍拼出来的整数(若数字非0，则最高位不能是0)，
 * 现在有m根火柴(m<=24),那么能品拼出多少种形如 A + B = C的等式？
 *
 * 注意:
 * 1.加号和等号各需要两个火柴棍
 * 2.如果A不等于B，则 A+B=C 与 B+A=C视为不同的等式(A B C 均大于0)
 * 3.所有的火柴棍必须全部用上
 * 4.规定的时间为1秒
 *
 * -----------------------------------------------------------
 *
 * 思考:
 * 1.尽可能先做逻辑判断，减少枚举数字的范围和需要枚举的数量，从而降低整体的时间复杂度
 * 2.假如有24根火柴,去掉加号和等号，就剩20根火柴了，如果要摆出的数字范围最大，则所需的火柴数量越少，也就是1所需的火柴数量最少，为2根，
 * 则最大能摆出的数字为10个1，又因为A+B=C,其中任意一个数字都不能大于11111,所以枚举的数字有了范围，为0~11111
 * 3.如果要枚举A B C 3个数，则时间复杂度为O(N^3)约定于11112^3，时间超过了1s, 这里C可以由A+B计算出来，所以时间复杂度降低为O(N^2)
 *
 * 优化:
 * 1.上面的枚举范围0~11111,是按照m=24根火柴算的最大值，但是能不能根据m实时算出最大值呢？
 * max = (m-4)/2/2 = m-4/4
 * */

constexpr int M = 20;

int num[10]={6,2,5,5,4,5,6,3,7,6}; //0-9数字所需的火柴棍个数

int fun(int x){ //计算某个数字摆成需要的火柴棍个数 注意这里如何将一个数字分解为单个数字的:123->顺序分解为3 2 1
    int total = 0;
    while(x/10!=0){//这里x至少为2位数
        total+=num[x%10];//个位数字需要的火柴棍个数
        x/=10;
    }
    total+=num[x];
    return total;
}

//0~11111枚举 其实时间要求达不到
int testEnumeration2(){
    auto start = std::chrono::steady_clock::now();
    int total = 0;
    //枚举A和B
    for(int a=0;a<11111;a++){
        for(int b=0;b<11111;b++){
            int c= a+b;
            if(fun(a) + fun(b) + fun(c) == M-4){
                std::cout<<a<<"+"<<b<<"="<<c<<std::endl;
                total++;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout<<"total:"<<total<<std::endl;
    std::cout<<"time:"<<time.count()<<std::endl;
    return 0;
}

//优化枚举的数字范围:0~(m-4)/4
int testEnumeration3(){
    auto start = std::chrono::steady_clock::now();
    int total = 0;

    int numOne = (M-4)/4;
    stringstream iss;
    for(int i=0;i<numOne;i++){
        iss<<"1";
    }
    int max = std::atoi(iss.str().c_str());

    //枚举A和B
    for(int a=0;a<max;a++){
        for(int b=0;b<max;b++){
            int c= a+b;
            if(fun(a) + fun(b) + fun(c) == M-4){
                std::cout<<a<<"+"<<b<<"="<<c<<std::endl;
                total++;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout<<"total:"<<total<<std::endl;
    std::cout<<"time:"<<time.count()<<std::endl;
    return 0;
}


#endif