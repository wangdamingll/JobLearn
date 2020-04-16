#ifndef __MAP_BUILD_MIN_TREE1__H__
#define __MAP_BUILD_MIN_TREE1__H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*二叉树应用-----并查集
 *
 * 问题描述:
 * 现在有10个强盗:
 *  1号强盗与2号强盗是同伙.
 *  3号强盗与4号强盗是同伙.
 *  5号强盗与2号强盗是同伙.
 *  4号强盗与6号强盗是同伙.
 *  2号强盗与6号强盗是同伙.
 *  8号强盗与7号强盗是同伙.
 *  9号强盗与7号强盗是同伙.
 *  1号强盗与6号强盗是同伙.
 *  2号强盗与4号强盗是同伙.
 *  有一点需要注意:强盗同伙的同伙也是同伙. 你能帮助警方查出有多少个独立的犯罪团伙吗？
 *
 * 说明:
 * 第一行n,m，n表示强盗的人数,m表示警方搜集到的m条线索,接下来的m行每一行有两个数a b,表示强盗a和强盗b是同伙
 * 10 9
 * 1 2
 * 3 4
 * 5 2
 * 4 6
 * 2 6
 * 8 7
 * 9 7
 * 1 6
 * 2 4
 *
 * 并查集遵循原则:
 *  "靠左"原则
 *  "擒贼先擒王"
 *
 * 思考:
 * 1.这其实就是个类似"朋友圈"的问题
 *
 * */
constexpr int n=10;

int f[n+1] = {0}; //存储强盗信息
int sum =0; //强盗团伙数量

//团伙信息
struct Info{
    Info() = default;
    Info(int x1,int y1):x(x1),y(y1){}
    int x {0};
    int y {0};
};

//递归查找团队最高BOSS
int getF(int v){
    if(f[v] == v){
        return v;
    }else{
        //这里是路径压缩,每次在函数返回的时候,顺带把路上遇到的人的"BOSS"改为最后找
        //到的祖宗编号,也就是犯罪团伙的最高领导人编号.这样可以提高今后找到犯罪团伙的最高领导人(其实就是树的祖先)的速度
        f[v] = getF(f[v]);
        return f[v];
    }
}

//合并两个子集
void Merge(int v, int u){
    int t1 = getF(v);//查找团队领导人
    int t2 = getF(u);
    if(t1!=t2){//判断两个结点是否在同一个集合中,即是否为同一个祖先.
#if 0
        //打开这个函数,不影响统计的独立团伙个数,但是路径压缩彻底,影响输出的团伙成员信息,优点是效率高
        f[t2] = t1;//"靠左"原则,左边变成右边的BOSS.即把右边的集合,作为左边集合的子集合,经过路径压缩以后.将f[u]的根的值也赋值为v的祖先f[t1]
#else
        //打开这个函数,能统计出独立团伙数量和团伙成员,但是效率低
        //以下不属于并查集算法,这里添加是为了输出强盗团伙成员信息
        //函数功能:当把t2的BOSS指定为t1时,需要将原f中所有BOSS为t2的强盗也指定BOSS为t1.进一步路径压缩
        for(auto& it:f){
            if(it == t2){
                it = t1;
            }
        }
#endif
    }
}

void UnionFind1(){
    //初始化
    for(int i=1;i<=n;i++){
        f[i] = i; //先把自己的BOSS初始化为自己
    }

    //初始化强盗团伙数据
    std::vector<Info> v = {{1,2},
                          {3,4},
                          {5,2},
                          {4,6},
                          {2,6},
                          {8,7},
                          {9,7},
                          {1,6},
                          {2,4},
                        };
    std::unordered_map<int,unordered_set<int>> um;//保存强盗团伙信息<BOSS,...>

    //开始合并团伙数据
    for(auto it : v){
        Merge(it.x,it.y);
    }

    //扫描有多少个独立团伙
    for(int i=1;i<=n;i++){
        if(f[i] == i){
            um.emplace(i,unordered_set<int>{});
            sum++;
        }
    }

    //存储每个强盗团伙成员信息
    for(auto& it : um){
        for(int i=1;i<=n;i++){
            if(f[i] == it.first){
                it.second.emplace(i);
            }
        }
    }

    std::cout<<"独立的强盗团伙数量:"<<sum<<std::endl;
    std::cout<<"独立的强盗团伙成员信息:"<<std::endl;
    for(auto it : um){
        std::cout<<"强盗团伙BOSS:"<<it.first<<std::endl;
        std::cout<<"团伙成员信息:";
        for(auto iter:it.second){
            std::cout<<iter<<" ";
        }
        std::cout<<std::endl;
    }
}

int TestUnionFind1(){
    auto start = std::chrono::steady_clock::now();

    UnionFind1();//独立的犯罪团伙

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}


#endif //__MAP_BUILD_MIN_TREE1__H__