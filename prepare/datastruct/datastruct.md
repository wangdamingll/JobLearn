# 数据结构
---  
## 哈希表  
* [哈希表介绍(CSDN)](https://blog.csdn.net/wangdamingll/article/details/104198484)  
* [基于哈希表简单实现HashMap(拉链法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap1.cpp)  
* [基于哈希表简单实现HashMap(线性探查法.二次探查法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap2.cpp)  

## 树  
### 树的遍历  
#### 1. 树的深度优先遍历
* 算法思想  
递归思想  
* 算法特点  
每个节点会访问三次  
* 示例代码  
[树的深度优先遍历](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeEach)  
#### 2. 树的广度优先遍历
* 算法思想  
广度优先思想  
* 算法特点  
1. 借助队列方式  
2. 每个节点被访问一次  
* 示例代码  
[树的广度优先遍历](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeEach)  

### 树的常见习题  
#### 1. 二叉搜索树的第K大节点 
* 算法思想  
1. 递归思想  
2. 递归左节点回溯的时候判断是否是第K大节点  
3. 二叉搜索树深度优先遍历,如果是中序遍历,则输出的序列是升序序列  
* 算法特点  
1. 每个节点会访问三次  
2. 递归左节点回溯的时候判断是否是第K大节点  
3. 右左节点回溯,一旦找到第K大节点,便不能再次递归进入右节点  
* 示例代码  
[二叉搜索树的第K大节点](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeKNode)   

#### 2. 求二叉树第K层节点数 
* 算法思想  
1. 递归思想  
* 算法特点  
1. 求第K层的节点数,也就是要求第K-1层有无左右子树,存在就统计  
2. 第K-1层先序判断处理  
* 示例代码  
[求二叉树第K层节点数](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeNodeNumKthLevel)   

#### 3. 求二叉树叶子节点个数  
* 算法思想  
1. 递归思想  
* 算法特点  
1. 节点无左右子树就是叶子节点  
2. 先序处理(节点会被访问三次,先序 中序 后序处理都可以)  
* 示例代码  
[求二叉树叶子节点个数](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeLeafNum)   

#### 4. 求二叉树节点个数  
* 算法思想  
1. 深度优先思想(递归)  
2. 广度优先思想   
* 算法特点  
1. 深度优先借助递归  
2. 广度优先借助队列  
* 示例代码  
[求二叉树节点个数](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeNodeNum)   

#### 5. 求二叉树深度
* 算法思想  
1. 深度优先思想(递归)
2. 广度优先思想
* 算法特点  
1. 深度优先借助递归  
2. 广度优先借助队列  
* 示例代码  
[求二叉树深度](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeDepth)   





---