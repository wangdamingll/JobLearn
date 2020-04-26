#include <iostream>
#include <random>
#include <chrono>
#include "Map.hpp"
#include "AStar.hpp"
using namespace std;

constexpr int MAP_WIDTH = 5;
constexpr int MAP_HEIGHT = 5;
constexpr int MAP_GRID_SIZE = 1;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> disBarrier(0,5);
std::uniform_real_distribution<> dis(0, MAP_WIDTH);

float GetPos(){
    return dis(gen);
}

int main() {
    //初始化地图及地图属性
    Map map;
    map.InitMap(MAP_WIDTH,MAP_HEIGHT,MAP_GRID_SIZE);

    //随机设置障碍物
    std::vector<MapGrid>& mapV = map.GetMap();
    for(auto& it:mapV){
        it.property.barrier = disBarrier(gen)==0?1:0;//1是障碍物
    }

    //打印地图
    map.PrintMap();

    //起点和终点坐标及格子
    float fromPosX = GetPos();
    float fromPosY = GetPos();
    std::cout<<"fromPost:("<<fromPosX<<","<<fromPosY<<")"<<std::endl;

    float dstPosX = GetPos();
    float dstPosY = GetPos();
    std::cout<<"dstPost:("<<dstPosX<<","<<dstPosY<<")"<<std::endl;

    Vector2i from = map.ComputerGrid(fromPosX,fromPosY);
    Vector2i dst = map.ComputerGrid(dstPosX, dstPosY);

    int fromIndex = map.ComputerGridIndex(from.m_x,from.m_y);
    int dstIndex = map.ComputerGridIndex(dst.m_x,dst.m_y);
    std::cout<<"fromIndex:"<<fromIndex<<"->"<<dstIndex<<std::endl;

    if(from == dst){
        std::cout<<"same grid"<<std::endl;
        return 0;
    }

    //A* 寻路算法
    AStar aStar(&map);
    std::vector<Vector2i> path = aStar.AStarAlgorithm(from,dst);

    //打印路线
    int size = path.size();
    for(int i=size-1;i>=0;i--){
        if(i==size-1){
            std::cout<<"("<<path[i].m_x<<","<<path[i].m_y<<")";
        }else {
            std::cout << "->(" << path[i].m_x << "," << path[i].m_y << ")";
        }
    }
    std::cout<<std::endl;

    //打印寻路结果
    map.PrintMap(path);

    return 0;
}
