#ifndef __ASTAR_HPP_H__
#define __ASTAR_HPP_H__

#include <vector>
#include <algorithm>
#include <memory>
#include "Vector2i.hpp"

using namespace std;

class AStar{
public:
    AStar() = default;
    AStar(Map* map1):map(map1){}

public:
    /* A* 寻路算法demo
     * 1. 当起点和终点是障碍物时,寻路可能会失败
     * */
    std::vector<Vector2i> AStarAlgorithm(const Vector2i& from,const Vector2i& dst){
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

        auto& startMapGrid = map->GetMapGridByPos(from);//寻路起点
        auto& dstMapGrid = map->GetMapGridByPos(dst);//寻路终点
        if(startMapGrid.property.barrier==1||dstMapGrid.property.barrier==1){
            std::cout<<"起点或者终点是障碍物"<<std::endl;
            return {};
        }
        startMapGrid.property.startPost =1;//标记起点
        dstMapGrid.property.dstPost = 1;//标记终点

        startMapGrid.property.pos = from;//设置起点坐标
        dstMapGrid.property.pos = dst; //设置终点坐标
        startMapGrid.index = ++addOpenListIndex;    //加入openList的顺序.
                                                    //从速度上考虑,选择最后加入 openList 的方格更快.这导致了在寻路过程中,当靠近目标时,
                                                    //优先使用新找到的方格的偏好.但是这并不重要
        openListV.push_back(startMapGrid);
        openList[startMapGrid.property.index] = 1;//标记已经加入开启列表中 加快查找效率

        bool flag = false;//表示是否找到
        while(!openListV.empty()){
            auto curMapGrid = GetMinF();//获取F最小的格子
            clostList[curMapGrid.property.index] = 1;//标记已经加入了关闭列表中

            //下一个坐标(逆时针访问)
            int tx=0;
            int ty=0;
            for(int k=0;k<8;k++){
                tx = curMapGrid.property.pos.m_x + nextPos[k][0];
                ty = curMapGrid.property.pos.m_y + nextPos[k][1];

                //越界
                if(tx<0||tx>map->m_MapWidth||ty<0||ty>map->m_MapHeight){
                    continue;
                }

                //如果是障碍物或者已经在关闭列表中,则忽略
                auto& nextMapGrid = map->GetMapGridByPos(tx,ty);
                if(nextMapGrid.property.barrier==1 || clostList[nextMapGrid.property.index]==1){
                    continue;
                }

                if(openList[nextMapGrid.property.index]==0){//如果不在开启列表中,把它加入openList.并且把当前方格设置为它的父亲.记录该方格的F,G和H值
                    //计算F G H 值
                    if(nextPos[k][0]==0 || nextPos[k][1]==0){//十字方向移动
                        nextMapGrid.property.gCost = curMapGrid.property.gCost + 10;//假设十字方向移动为10

                    }else{//斜方向移动
                        //对角穿过不合法判断
                        static int barrierPos[4][4]={{0,1},//向上
                                                  {1,0},//向右
                                                  {0,-1},//向下
                                                  {-1,0},//向左
                                            };
                        bool bFlag = false;
                        for(int j=0;j<4;j++){//对nextPost四个十字方向枚举
                            int btx = tx + barrierPos[j][0];
                            int bty = ty + barrierPos[j][1];

                            //越界
                            if(btx<0||btx>map->m_MapWidth||bty<0||bty>map->m_MapHeight){
                                continue;
                            }

                            const MapGrid& bMapGrid = map->GetMapGridByPos(btx,bty);
                            if(bMapGrid.property.barrier==1){//如果是障碍物,判断是不是当前格子(curMapGrid)和nextMapGrid的夹角的障碍物
                                //障碍物点到nextPos的坐标差
                                int dx1 = btx - tx;
                                int dy1 = bty - ty;

                                //障碍物点到当前节点的坐标差
                                int dx2 = btx - curMapGrid.property.pos.m_x;
                                int dy2 = bty - curMapGrid.property.pos.m_y;

                                //总共四个可能的夹角
                                if((dx1==0&&dy2==0)||(dy1==0&&dx2==0)){//对称的
                                    bFlag = true;
                                    break;
                                }
                            }
                        }
                        if(bFlag){
                            continue;
                        }

                        //如果当前节点和nextPos的夹角没有障碍物的话,那么这个节点是符合要求的
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
                    auto& curFMapGrid =map->GetMapGridByIndex(curMapGrid.property.fIndex);
                    int G1=0;   //从当前节点的父节点到这个节点的G消耗
                    int G2=0;   //从当前节点到这个节点的G消耗

                    //判断这个next格子在其父节点的方位
                    if(curFMapGrid.property.pos.m_x-tx==0 ||curFMapGrid.property.pos.m_y-ty==0){//这个格子在父节点的十字方向
                        G1 = curFMapGrid.property.gCost+10;//假设十字方向移动为10
                    }else{
                        G1 = curFMapGrid.property.gCost+14;//假设斜方向移动消耗14
                    }

                    //判断这个next格子在当前节点的方位
                    if(nextPos[k][0]==0 || nextPos[k][1]==0){//十字方向移动
                        G2 = curMapGrid.property.gCost+10;
                    }else{//斜方向移动
                        G2 = curMapGrid.property.gCost+14;
                    }

                    if(G2<G1){//表示通过当前节点到这个节点路线最优:Dijkstra算法思想
                        nextMapGrid.property.gCost = G2;
                        nextMapGrid.property.hCost = (std::abs(dstMapGrid.property.pos.m_x-tx)+std::abs(dstMapGrid.property.pos.m_y-ty))*10;
                        nextMapGrid.property.hCost = nextMapGrid.property.gCost + nextMapGrid.property.hCost;

                        //计入openList
                        nextMapGrid.property.fIndex = curMapGrid.property.index;//把当前格子设置为父节点
                        nextMapGrid.property.pos = {tx,ty};
                        nextMapGrid.index = ++addOpenListIndex;
                        openListV.push_back(nextMapGrid);
                        openList[nextMapGrid.property.index] = 1;
                        std::push_heap(openListV.begin(),openListV.end(),std::greater<MapGrid>{});//堆排
                    }
                }

                //找到了寻路终点
                if(dst.m_x==tx && dst.m_y==ty){
                    flag = true;
                    break;
                }
            }
            if(flag){
                std::cout<<"找到了从("<<from.m_x<<","<<from.m_y<<")到("<<dst.m_x<<","<<dst.m_y<<")的路线:"<<std::endl;
                break;
            }
        }

        if(!flag){ //表示没有找到
            std::cout<<"没有找到了从("<<from.m_x<<","<<from.m_y<<")到("<<dst.m_x<<","<<dst.m_y<<")的路线"<<std::endl;
            return {};
        }

        //获得路线
        return GetAStarPath(from,dst);
    }

private:
    //获取寻路路线
    std::vector<Vector2i> GetAStarPath(const Vector2i& from, const Vector2i& dst){
        std::vector<Vector2i> pathV;//寻路路线
        pathV.emplace_back(dst);//添加终点

        auto& dstMapGrid = map->GetMapGridByPos(dst);
        int fIndex = dstMapGrid.property.fIndex;
        while (fIndex!=0){
            auto curMapGrid = map->GetMapGridByIndex(fIndex);
            pathV.emplace_back(curMapGrid.property.pos);
            fIndex = curMapGrid.property.fIndex;
        }

        return pathV;
    }

    //获得最小F值得格子对象
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
    Map* map = nullptr; //地图对象(可以考虑单例获取)
};


#endif //__ASTAR_HPP_H__