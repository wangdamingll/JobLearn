#ifndef __ENUMERATION3__H__
#define __ENUMERATION3__H__

#include <iostream>
#include <chrono>
using namespace std;

/*全排列系列问题----枚举算法
 *
 * 问题描述:
 * string= "abc"有多少种排列？
 *
 * 思考:
 * 1.这其实和将a b c 放入3个格子里是差不多的
 * 2.下面例子的时间复杂度是多少呢？
 * O(N^3) 所以str3越大，耗时越多，这次情况下深度优先算法(DFS)就会比较好一些
 * */

int total3=0;
string str3 = "abc";
int a3[3] = {0}; //假设有3个格子,存储a b c

int TestEnumeration4(){
    auto start = std::chrono::steady_clock::now();

    for(int i=0;i<3;i++){
        a3[0]=str3[i]; //放入第一个格子中
        for(int j=0;j<3;j++){
            a3[1]=str3[j]; //放入第二个格子中
            for(int k=0;k<3;k++){
                a3[2]=str3[k]; //放入第三个格子中

                int book3[200]={0}; //统计每个字母出现的次数
                int sum=0;
                for(auto it :a3){
                    book3[it] = 1;
                }
                for(auto it : book3){
                    sum+=it;
                }

                if(sum==3){//每个字母各出现一次
                    std::cout<< (char)a3[0]<<(char)a3[1]<<(char)a3[2]<<std::endl;
                    total3++;
                }
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    std::cout<<"total:"<<total3<<std::endl;
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif