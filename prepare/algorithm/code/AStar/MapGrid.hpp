#ifndef __MAP_GRID__H_
#define __MAP_GRID__H_

#include <unordered_map>
#include "Vector2i.hpp"

//格子中存储的对象
struct ObjBase{
public:
    ObjBase() = default;
    virtual ~ObjBase() = default;

public:
    inline void SetPosX(int posX){
        pos.m_x = posX;
    }
    inline void SetPosY(int posY){
        pos.m_y = posY;
    }

    inline int GetPosX() const{
        return pos.m_x;
    }
    inline int GetPosY() const{
        return pos.m_y;
    }

    uint64_t GetId()const{
        return m_id;
    }
private:
    uint64_t m_id {0};
    Vector2i pos;
};

//描述地图格子属性
struct GridProperty{
public:
    GridProperty()= default;

public:
    int show {0};//打印最终路线显示
    int dstPost{0};//是否是终点
    int barrier{0};//该格子是否是障碍物:0 不是   1 是
    int fCost {0};//总消耗:F = G + H
    int gCost {0};//G
    int hCost {0};//H
    int index {0};//在地图中的index
    int fIndex{0};//寻路过程中负父节点索引
    Vector2i pos; //坐标
};


//地图格子类 容纳角色和NPC等等
class MapGrid{
public:
    MapGrid() = default;

public:
    void AddObj(const ObjBase& obj){
        m_Obj.emplace(obj.GetId(),obj); //举个例子
    }

    void RemoveObj(const uint64_t& uid){
        auto it = m_Obj.find(uid);
        if(it == m_Obj.end()){
            std::cout<<"ERROR"<<std::endl;
            return;
        }
        m_Obj.erase(it);
    }

    bool operator>(const MapGrid& another)const{
        if(property.fCost == another.property.fCost){
            return index>another.index;
        }
        return property.fCost > another.property.fCost;
    }

    //.... 其他函数

public://不考虑封装性了
    int index {0};//表示加入openList的顺序
    GridProperty property;
private:
    std::unordered_map<uint64_t,ObjBase> m_Obj; //简单举个例子 可以用内存池等等
};

#endif //__MAP_GRID__H_