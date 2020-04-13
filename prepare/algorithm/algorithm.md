# 算法
---

## 排序算法

### 1. 待完善

## 搜索算法

### 1. 枚举算法
* 算法思想:  
  有序的去尝试每一种可能
* 注意事项:  
1. 尽可能先做逻辑判断，减少枚举数字的范围和需要枚举的个数，从而降低整体的时间复杂度
* 枚举算法的应用:  
1. 全排列系列问题  
2. 火柴棍问题
3. ...
* [代码示例](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/enumeration)

### 2. 不撞南墙不回头-----深度优先搜索
* 算法(Depth First Search)的思想:  
1. 首先以一个未被访问过的顶点作为起始顶点,沿当前顶点的边走到未访问过的顶点;当没有未访问过的顶点时,则回到上一个顶点,继续试探访问别的顶点,直到所有的顶点都被访问过.
   显然，深度优先遍历是沿着某一条分支遍历直到末端,然后回溯,再沿着另一条进行同样的遍历,直到所有的顶点都被访问过为止.
2. 理解DFS的关键:DFS在于解决"当下该如何做"，至于"下一步如何做"和"当下该如何做"是一样的  
3. 实现的方法一般是递归调用自己  
* 时间复杂度  
  不涉及逻辑,纯算法时间复杂度O(N^2)
* DFS的基本模型
```C++
  void dfs(int step){
      //判断边界
      //满足条件则返回

       //尝试每一种可能
      for(int i=1;i<n;i++){
           //继续下一步
           dfs(step+1)
      }
     //返回
 }
```
* 算法的应用:    
1. 全排列问题
2. 迷宫问题(连通图问题)-----时间复杂度不止O(N^2)
3. 图中独立子图个数(种子填充法)
4. 图遍历-----(请查看下文图遍历算法)
* [代码示例](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/DFS)

### 3. 层层递进---广度优先搜索
* 算法思想:  
1. 首先以一个未被访问过的顶点作为起始顶点,访问其所有相邻的顶点,然后对每个相邻的顶点,再访问它们相邻的未被访问过的顶点，直到所有顶,点都被访问过,遍历结束.  
* 时间复杂度  
不涉及逻辑,纯算法时间复杂度O(N^2)
* 算法应用:
1. 迷宫问题(连通图问题)--------O(N^2)
2. 图遍历------适合边权一样的情况(请查看下文图遍历算法)
* [代码示例](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/BFS)


## 图
### 1. 图定义  
简单的说,图就是由一些小圆点(称为顶点)和连接这些小圆点的直线(称为边)组成的.
### 2. 图分类  
图可以分为无向图和有向图  
### 3. 图存储  
邻接矩阵存储法 邻接表存储法
### 4. 图遍历
#### 1. 深度优先搜索(DFS)
##### 图遍历DFS思想
首先以一个未被访问过的顶点作为起始顶点,沿当前顶点的边走到未访问过的顶点;当没有未访问过的顶点时,则回到上一个顶点,继续试探访问别的顶点,直到所有的顶点都被访问过.显然,深度优先遍历是沿着图的某一条分支遍历直到末端,然后回溯,再沿着另一条进行同样的遍历,直到所有的顶点都被访问过为止.
##### 代码地址
[图遍历DFS---无向图和有向图](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Map)
#### 2.广度优先搜索(BFS)
##### 图遍历BFS思想
首先以一个未被访问过的顶点作为起始顶点,访问其所有相邻的顶点,然后对每个相邻的顶点,再访问它们相邻的未被访问过的顶点,直到所有顶点都被访问过,遍历结束.
##### 代码地址
[图遍历BFS---无向图](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Map)

## 图最短路径
### 1. 深度优先搜索算法(DFS)  
* 解决问题  
求图中多源(全源)最短路问题  
* 时间复杂度  
纯算法时间复杂度O(N^2)
* 代码示例
[最短路径DFS---无向图和有向图](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Map)

### 2. 广度优先搜索算法(BFS)
* 解决问题  
求图中多源(全源)最短路问题  
* 时间复杂度  
纯算法时间复杂度O(N^2)
* 特点  
比深度优先算法块,更加适用于边权相同的情况  
* 代码示例  
[最短路径BFS---无向图](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Map)

### 3. Floyd-Warshall(弗洛伊德算法----只有五行的算法)  
* 解决问题  
求图中多源(全源)最短路问题  
* 时间复杂度  
O(N^3)
* 特点  
1. 非常简单,只有五行    
2. 可以求图中全源最短路问题
3. 也可以求单源最短路问题(指定一个顶点到其余各个顶点的最短路径)
4. 图中边权可以有负值,但是不可以含有负权循环  
* 代码示例  
[Floyd-Warshall](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Floyd-Warshall)  

### 3. Dijkstra  
* 解决问题  
求图中单源最短路问题  
* 时间复杂度  
1. 用一般的图的邻接矩阵法存的话,时间复杂度为O(N^2)
2. 对于稀疏图来说,用堆和邻接表存储法,可以将时间复杂度优化为O((M+N)logN),N为顶点数,M为边数.最坏的情况M等于N^2,那么O((M+N)logN)比O(N^2)大,但是一般来说边没有那么多,所以O((M+N)logN)比O(N^2)小很多
* 特点      
1. 可以求图中单源最短路问题
2. 时间复杂度为O(N^2),可以优化为O((M+N)logN),N为顶点数,M为边数
3. 图中边权不可以有负值
* 代码示例  
[图邻接表存储法](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Dijkstra)  
[Dijkstra](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/Dijkstra)

---