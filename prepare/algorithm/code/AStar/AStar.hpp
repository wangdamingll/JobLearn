#ifndef __ASTAR_HPP_H__
#define __ASTAR_HPP_H__

#include <vector>
#include <set>
#include <algorithm>
#include "Vector2i.hpp"

using namespace std;

class AStar{
public:
    AStar() = default;

public:
    std::vector<Vector2i> AStarAlgorithm(const Vector2i& from,const Vector2i& dst,Map& map){
        static int addOpenListIndex=0;
        //逆时针坐标访问
        static int nextPos[8][8]={{0,1},//向上
                                  {1,1},//向右上
                                  {1,0},//向右
                                  {1,-1},//向右下
                                  {0,-1},//向下
                                  {-1,-1},//向左下
                                  {-1,0},//向左
                                  {-1,1},//向左上
                                };

        auto& startMapGrid = map.GetMapGridByPos(from);//寻路起点
        const auto& dstMapGrid = map.GetMapGridByPos(dst);//寻路终点

        startMapGrid.property.pos = from;
        startMapGrid.index = ++addOpenListIndex;    //加入openList的顺序.
                                                    //从速度上考虑,选择最后加入 openList 的方格更快.这导致了在寻路过程中,当靠近目标时,
                                                    //优先使用新找到的方格的偏好.但是这并不重要
        openListV.push_back(startMapGrid);
        openList[startMapGrid.property.index] = 1;//标记已经加入开启列表中 加快查找效率

        while(!openListV.empty()){
            auto curMapGrid = GetMinF();//获取F最小的格子
            clostList[curMapGrid.property.index] = 1;//标记已经加入了关闭列表中

            //下一个坐标(逆时针访问)
            int tx=0;
            int ty=0;
            for(int k=0;k<8;k++){
                tx =curMapGrid.property.pos.m_x + nextPos[k][0];
                ty = curMapGrid.property.pos.m_y + nextPos[k][1];

                //越界
                if(tx<0||tx>map.m_MapWidth||ty<0||ty>map.m_MapHeight){
                    continue;
                }

                //如果是障碍物或者已经在关闭列表中,则忽略
                auto& nextMapGrid = map.GetMapGridByPos(tx,ty);
                if(nextMapGrid.property.barrier==1 || clostList[nextMapGrid.property.index]==1){
                    continue;
                }

                if(openList[nextMapGrid.property.index]==0){//如果不在开启列表中,把它加入openList.并且把当前方格设置为它的父亲.记录该方格的F,G和H值
                    //计算F G H 值
                    if(nextPos[k][0]==0 || nextPos[k][1]==0){//十字方向移动
                        nextMapGrid.property.gCost = curMapGrid.property.gCost + 10;//假设十字方向移动为10

                    }else{//斜方向移动
                        nextMapGrid.property.gCost = curMapGrid.property.gCost + 14;//假设斜方向移动消耗14
                    }
                    nextMapGrid.property.hCost = (std::abs(dstMapGrid.property.pos.m_x-tx)+std::abs(dstMapGrid.property.pos.m_y-ty))*10;//曼哈顿距离消耗
                    nextMapGrid.property.fCost = nextMapGrid.property.gCost + nextMapGrid.property.hCost;

                    //计入openList
                    nextMapGrid.property.fIndex = curMapGrid.property.index;//把当前格子设置为父节点
                    nextMapGrid.property.pos = {tx,ty};
                    nextMapGrid.index = ++addOpenListIndex;
                    openListV.push_back(nextMapGrid);
                    openList[nextMapGrid.property.index] = 1;
                    std::push_heap(openListV.begin(),openListV.end(),std::greater<MapGrid>{});//堆排
                }else{//如果在开启列表中
                    //待完善



                }

            }
        }


        return {};
    }

private:
    MapGrid GetMinF(){
        std::pop_heap(openListV.begin(),openListV.end(),std::greater<MapGrid>{});
        MapGrid grid = openListV.back();
        openListV.pop_back();
        openList[grid.property.index] = 0;//取消标记
        return grid;
    }

private:
    int openList[1024]={0};//标记是否在开启列表中
    int clostList[1024]={0};//标记是否在关闭列表中
    std::vector<MapGrid> openListV;//寻路开启列表
};


#endif //__ASTAR_HPP_H__