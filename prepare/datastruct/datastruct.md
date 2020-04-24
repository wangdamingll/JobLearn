# 数据结构
---  
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

### 二叉搜索树的第K大节点 
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

### 求二叉树第K层节点数 
* 算法思想  
1. 递归思想  
* 算法特点  
1. 求第K层的节点数,也就是要求第K-1层有无左右子树,存在就统计  
2. 第K-1层先序判断处理  
* 示例代码  
[求二叉树第K层节点数](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BTreeNodeNumKthLevel)   




---