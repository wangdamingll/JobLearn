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
1. 理解DFS的关键:DFS在于解决"当下该如何做"，至于"下一步如何做"和"当下该如何做"是一样的  
2. 实现的方法一般是递归调用自己
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
2. 迷宫问题(连通图问题)-----复杂度比较高
3. 图中独立子图个数(种子填充法)
* [代码示例](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/DFS)

### 3. 层层递进---广度优先搜索
* 算法思想:

* 算法应用:
1. 迷宫问题(连通图问题)
2. 
* [代码示例](https://github.com/wangdamingll/JobLearn/tree/master/prepare/algorithm/code/BFS)


---