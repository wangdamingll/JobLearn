#ifndef __MAP_HPP_H__
#define __MAP_HPP_H__

#include <vector>
#include <set>
#include <algorithm>
#include "Vector2i.hpp"
#include "MapGrid.hpp"

using namespace std;

class Map{
public:
    Map() = default;

public:
    /*地图初始化
     * 参数:
     * mapWidth:地图宽
     * mapHeight:地图高
     * gridSize:格子数
     * 返回值:
     * 无
     * */
    void InitMap(int mapWidth,int mapHeight,int gridSize){
        m_ColCount = mapWidth / gridSize +1;
        m_RowCount = mapHeight / gridSize +1;
        m_GridSize = gridSize;
        m_MapWidth = mapWidth;
        m_MapHeight = mapHeight;

        m_MaxIndex = m_ColCount * m_RowCount;
        m_MapGridVec.resize(m_MaxIndex);

        //初始化地图对象的index,用于快速查找
        int index=0;
        for(auto& it:m_MapGridVec){
            it.property.index = index++;
        }
    }

    /*计算移动坐标所在的格子坐标
     * 参数:
     * posX:移动的横坐标
     * posY:移动的纵坐标
     * 返回值:
     * 格子所在的坐标
     * */
    Vector2i ComputerGrid(int posX,int posY){
        if(posX<0) posX = 0;
        if(posY<0) posY = 0;
        if(posX>m_MapWidth) posX = m_MapWidth;
        if(posY>m_MapHeight) posY = m_MapHeight;
        return {posX/m_GridSize,posY/m_GridSize};
    }

    /*计算移动坐标所在格子的索引
     * 参数:
     * posX:移动的横坐标
     * posY:移动的纵坐标
     * 返回值:
     * 格子所在的索引
     * */
    int ComputerGridIndex(int posX, int posY){
        if(posX<0) posX = 0;
        if(posY<0) posY = 0;
        if(posX>m_MapWidth) posX = m_MapWidth;
        if(posY>m_MapHeight) posY = m_MapHeight;
        return (posY/m_GridSize * m_ColCount + posX/m_GridSize);
    }

    /* 根据格子坐标计算出格子索引
     * 参数:
     * pos:格子坐标
     * 返回值:
     * 格子对象的索引
     * */
    int GetGridIndexByPos(const Vector2i& pos){
        return (pos.m_y*m_ColCount+pos.m_x);
    }

    /* 根据格子坐标获取地图格子对象
     * 参数:
     * pos:格子坐标
     * 返回值:
     * 格子对象
     * */
    MapGrid& GetMapGridByPos(const Vector2i& pos){
        return m_MapGridVec[pos.m_y*m_ColCount + pos.m_x];
    }

    /* 根据格子索引获取地图格子对象
     * 参数:
     * index:格子索引
     * 返回值:
     * 格子对象
     * */
    MapGrid& GetMapGridByIndex(const int index){
        return m_MapGridVec[index];
    }

    /* 根据格子坐标获取地图格子对象
     * 参数:
     * posX:格子坐标横坐标
     * posY:格子纵坐标
     * 返回值:
     * 格子对象
     * */
    MapGrid& GetMapGridByPos(const int posX,const int posY){
        return m_MapGridVec[posY*m_ColCount + posX];
    }

    /*计算移动过程中增加或者减少的格子区域
     * 参数:
     * from:出发坐标点所在的格子坐标
     * dst:目的坐标点所在的格子坐标
     * deleteArea:移动过程中减少的格子区域(视野区域)
     * addArea:移动过程中增加的格子区域
     * 返回值:
     * 无
     * */
    void InterestArea(const Vector2i& from,const Vector2i& dst,set<int>& deleteArea, set<int>& addArea){
        set<int> fromArea = GetAll9Grid(from);
        set<int> dstArea = GetAll9Grid(dst);

        //求set交集
        set<int> intersection;
        std::set_intersection(fromArea.begin(),fromArea.end(),dstArea.begin(),dstArea.end(),std::inserter(intersection,intersection.begin()));//C++11

        //deleteArea =  fromArea - 交集
        std::set_difference(fromArea.begin(),fromArea.end(),intersection.begin(),intersection.end(),std::inserter(deleteArea,deleteArea.begin()));
        //addArea = dstArea - 交集
        std::set_difference(dstArea.begin(),dstArea.end(),intersection.begin(),intersection.end(),std::inserter(addArea,addArea.begin()));

        //DEBUG LOG
        std::cout<<"fromArea:"<<std::endl;
        Print(fromArea);
        std::cout<<"dstArea:"<<std::endl;
        Print(dstArea);
        std::cout<<"intersection:"<<std::endl;
        Print(intersection);
        std::cout<<"deleteArea:"<<std::endl;
        Print(deleteArea);
        std::cout<<"addArea:"<<std::endl;
        Print(addArea);
    }

    /*计算移动过程中增加或者减少的格子区域
     * 参数:
     * fromPosX:出发横坐标
     * fromPosY:目的纵坐标
     * dstPosX:目的点横坐标
     * dstPosY:目的地安纵坐标
     * deleteArea:移动过程中减少的格子区域(视野区域)
     * addArea:移动过程中增加的格子区域
     * 返回值:
     * 无
     * */
    void InterestArea(const int& fromPosX, const int& fromPosY,const int& dstPosX, const int& dstPosY,set<int>& deleteArea, set<int>& addArea){
        Vector2i from = ComputerGrid(fromPosX,fromPosY);
        Vector2i dst = ComputerGrid(dstPosX,dstPosY);
        return InterestArea(from,dst,deleteArea,addArea);
    }

    /* 设置地图格子属性
     * 参数:
     * index:地图格子索引
     * property:地图属性
     * 返回值:
     * 无
     * */
    void SetMapGridProperty(const int index,GridProperty& property){
        m_MapGridVec[index].property=std::move(property);
    }

    /*将角色添加到对应的格子中
     * 参数:
     * pos:角色移动的目标点对应格子所在的坐标
     * obj:角色对象
     * 返回值:
     * 无
     * */
    void AddObj(const Vector2i& pos,ObjBase& obj){
        m_MapGridVec[pos.m_y*m_ColCount + pos.m_x].AddObj(obj);//近似实现类似unordered的查找效率
    }

    /*将角色在对应的格子中删除
     * 参数:
     * obj:角色对象
     * 返回值:
     * 无
     * */
    void RemoveObj(const ObjBase& obj){
        m_MapGridVec[obj.GetPosY()*m_ColCount + obj.GetPosX()].RemoveObj(obj.GetId());
    }

    /* 获取地图
     * 参数:
     * 无
     * 返回值:
     * 地图
     * */
    std::vector<MapGrid>& GetMap(){
        return m_MapGridVec;
    }

    /* 打印地图
     * 参数:
     * 无
     * 返回值:
     * 无
     * */
    void PrintMap(){
        std::cout<<"起点:& 终点:? 路线:@ 障碍物:# 可通行:*"<<std::endl;
        for(int i=m_MapWidth-1;i>=0;i--){ //纵坐标
            for(int j=0;j<m_MapHeight;j++){//横坐标
                if(m_MapGridVec[i*m_RowCount+j].property.barrier==0){
                    if(m_MapGridVec[i*m_RowCount+j].property.show==1){//打印寻路路线
                        if(m_MapGridVec[i*m_RowCount+j].property.startPost==1){ //起点
                            std::cout<<"& ";
                        }else if(m_MapGridVec[i*m_RowCount+j].property.dstPost==1){//终点
                            std::cout<<"? ";
                        }else{//路线
                            std::cout<<"@ ";
                        }
                    }else{
                        std::cout<<"* ";//可以通行
                    }
                } else{
                    std::cout<<"#"<<" ";//障碍物
                }
            }
            std::cout<<std::endl;
        }
    }

    void PrintMap(std::vector<Vector2i>& path){
        for(auto& it : path){
            auto& curGrid = m_MapGridVec[it.m_y*m_ColCount + it.m_x];
            curGrid.property.show =1;
        }
        PrintMap();
    }

    //... 其他函数

private:
    /*计算出pos点周围的9宫格格子索引
     * 参数:
     * pos:9宫格中心点格子坐标点
     * 返回值:
     * 9宫格格子索引
     * */
    set<int> GetAll9Grid(const Vector2i& pos){
        int curIndex = pos.m_y * m_ColCount + pos.m_x;      //当前索引值
        int curColIndexMax = (pos.m_y+1) * m_ColCount -1;   //当前行最大索引值
        int curColIndexMin = pos.m_y * m_ColCount ;       //当前行最小索引值

        set<int> setIndex;
        setIndex.emplace(curIndex); //中间格子

        int leftIndex = curIndex-1 ; //左边格子索引
        if(leftIndex>=0 && leftIndex >=curColIndexMin){
            setIndex.emplace(leftIndex);
        }
        int rightIndex = (curIndex+1)<=curColIndexMax?(curIndex+1):curColIndexMax;//右边格子索引
        if(rightIndex<=m_MaxIndex-1){
            setIndex.emplace(rightIndex);
        }

        int midUpIndex = curIndex+m_ColCount;//中上格子索引
        if(midUpIndex<=m_MaxIndex-1){
            setIndex.emplace(midUpIndex);
        }

        int midDownIndex = curIndex-m_ColCount; //中下格子索引
        if(midDownIndex>=0){
            setIndex.emplace(midDownIndex);
        }

        int leftUpIndex = midUpIndex-1; //左上格子索引
        if(leftUpIndex>=0  && (leftUpIndex>= curColIndexMin + m_ColCount && leftUpIndex<=m_MaxIndex-1)){
            setIndex.emplace(leftUpIndex);
        }
        int rightUpIndex = (midUpIndex+1)<=(curColIndexMax+m_ColCount)?(midUpIndex+1):(curColIndexMax+m_ColCount);//右上格子索引
        if(rightUpIndex<=m_MaxIndex-1){
            setIndex.emplace(rightUpIndex);
        }

        int leftDownIndex = midDownIndex-1; //左下格子索引
        if(leftDownIndex>=0 && leftDownIndex>=curColIndexMin-m_ColCount){
            setIndex.emplace(leftDownIndex);
        }
        int rightDownIndex = (midDownIndex+1)<=(curColIndexMax-m_ColCount)?(midDownIndex+1):(curColIndexMax-m_ColCount);//右下格子索引
        if(rightDownIndex>=0){
            setIndex.emplace(rightDownIndex);
        }
        return setIndex;
    }

private:
    void Print(const set<int>& set){
        std::cout<<"(";
        for(auto it : set){
            std::cout<<it<<" ";
        }
        std::cout<<")"<<std::endl;
    }

public://不考虑封装了
    int m_GridSize {0};
    int m_MapWidth {0};
    int m_MapHeight {0};
    int m_ColCount {0};
    int m_RowCount {0};
    int m_MaxIndex {0};
    std::vector<MapGrid> m_MapGridVec;//格子对象数据
};


#endif //__MAP_HPP_H__