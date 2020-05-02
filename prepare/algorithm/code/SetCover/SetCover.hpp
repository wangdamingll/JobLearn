#ifndef __SET_COVER_HPP_H__
#define __SET_COVER_HPP_H__

#include <iostream>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

/*NPC问题-----集合问题
 *
 * 问题描述:
 * 假设你办了个广播节目,要让全美50个州的听众都收听得到.为此,你需要决定在哪些广播台播出.在每个广播台播出都需要支付费用,因此你力图在尽可能少的广播台播岀
 *
 * 说明:
 * 1. 这里为了简便起见,假设有5个广播电台
 *
 * 时间复杂度:
 * 1. 这是NPC问题,所有的组合的时间复杂度为:O(2^N),N为广播电台数量
 *
 * 算法特点:
 * 1. 每次找剩余的广播电台中覆盖未覆盖地点最多的广播电台,直到所有的地点都被覆盖为止
 *
 * 思考:
 * 1. 此为NPC问题,广播电台数量越多,时间复杂度越大,因此精确解法不在适用了,可以考虑近似算法中的贪婪算法
 * 2. 使用set_intersection要求所在范围具有同一标准的排序,所以尽量用同一种容器,如果不是关联容器,要先排序
 * */

namespace setcover{

void SetCover(){
    std::set<std::string> allBroadcast={"mt", "wa", "or", "id", "nv", "ut","ca", "az"};//所有需要覆盖的地点
    std::set<std::string> coverNeed;//未覆盖地点
    std::set<std::string> finalBroadcast;//存储最终电台的集合
    std::unordered_map<std::string,std::set<std::string>> broadcast;//存储每个电台所能覆盖地点的信息
    broadcast["kone"]={"id", "nv", "ut"};
    broadcast["ktwo"] = {"wa", "id", "mt"};
    broadcast["kthree"] = {"or", "nv", "ca"};
    broadcast["kfour"] = {"nv", "ut"};
    broadcast["kfive"] = {"ca", "az"};

    coverNeed = allBroadcast;
    std::set<std::string> cover;//存储交集信息
    std::set<std::string> tmp;//临时保存电台信息
    std::string broadcastname="";//电台名称

    while(!coverNeed.empty()){  //直到所有的地点都被覆盖到
        for(auto it : broadcast){//找到能覆盖未覆盖地点最大的电台
            std::set_intersection(it.second.begin(),it.second.end(),coverNeed.begin(),coverNeed.end(),std::inserter(cover,cover.begin()));
            if(cover.size()>tmp.size()){
                cover.clear();
                tmp = it.second;
                broadcastname = it.first;
            }
        }
        finalBroadcast.emplace(broadcastname);
        for(auto it : broadcast[broadcastname]){ //更新需要覆盖的地点
            auto iter = coverNeed.find(it);
            if(iter!=coverNeed.end()){
                coverNeed.erase(iter);
            }
        }

        cover.clear();
        tmp.clear();
        broadcastname.clear();
    }

    for(auto it : finalBroadcast){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
};

void TestSetCover(){
    auto start = std::chrono::steady_clock::now();

    SetCover();//集合问题

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<"time:"<<time.count()<<":ms"<<std::endl;
};
}
#endif