# 数据结构
---  
## 栈  
### 1. 栈模型  
* 栈是后进先出的数据模型  
### 2. 栈的实现  
* 可以用数组和链表模拟实现  
### 3. 栈的应用  
* 平衡符号  
可以用来检查语法是否有错误  
* 中缀表达式转后缀表达式(逆波兰记法)   
例如中缀表达式a + b * c + (d * e + f) * g 转换成后缀表达式: a b c * + d e * f + g * + 
* 用后缀表达式计算结果(后缀表达式其实是中缀表达式的一个表现形式)    
例如后缀表达式:6 5 2 3 + 8 * + 3 + * ,其结果为:288  
* 函数调用  
* 由后缀表达式构造一颗表达式树  
### 4. 示例代码  
[栈的应用](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/StackUse)      


## 哈希表(散列表)  
### 1. 定义  
* 散列表的实现常常叫作散列(hashing),散列是一种用于以常数平均时间执行插入,删除和查找的技术.但是,那些需要元素间任何序信息的树操作在这里将不会得到有效的支持.  
* 注意:表的大小(tablesize)一般是素数,这样产生冲突的时候会有更多的备选空间,更好的散列分布    
### 2. 散列表解决冲突的方法  
* 拉链法  
1. hash(x)=x mod tablesize  
2. 装填因子a约等于1(tablesize应该为素数)  
3. 产生冲突时,元素应插入对应链表的前端,因为不仅方便,而且这个元素最有可能不久又被访问  
* 开发地址法(线性探测法、平方探测法)  
1. 线性探测法  
(1)hi(x) = ( hash(x) + f(i)) mod tablesize,且f(0)=0;f(i)=i;  
(2)装填因子a必须要小于等于0.5  
(3)惰性删除  
1. 平方探测法  
(1)hi(x) = ( hash(x) + f(i)) mod tablesize,且f(0)=0;f(i)=i^2;  
(2)装填因子a必须要小于等于0.5,并且tablesize必须为素数.因为这样的话,表至少有一半为空时,产生冲突时,平方探测法总能够插入成功   
(3)惰性删除  
* 双散列    
f(i)=i*hash2(x)    
hash2(x) = R -(x mod R),R为小于tablesize的素数  
hi(x) = (hash(x) + f(i)) mod tablesize = (hash(x) + i*hash2(x)) mod tablesize  
### 示例代码
* [哈希表介绍(CSDN)](https://blog.csdn.net/wangdamingll/article/details/104198484)  
* [基于哈希表简单实现HashMap(拉链法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap1.cpp)  
* [基于哈希表简单实现HashMap(线性探查法.二次探查法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap2.cpp)  

## 树  
## 树的分类  
#### 1. 二叉搜索树  
* 定义  
左子树值比父亲值小,右子树值比父亲值大    
* 时间复杂度  
在没有删除或者惰性删除的情况下,所有操作的时间复杂度平均为O(logN)  
* [示例代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BinarySearchTree)    
* [具体介绍](https://blog.csdn.net/wangdamingll/article/details/106077585)  

#### 2. AVL树(平衡二叉搜索树)  
* 定义  
在二叉搜索树的基础上增加平衡条件的树  
* 时间复杂度  
O(logN)  
* 平衡方式  
必须平衡的节点称为a,a的两颗子树的高度差为2  
1) 单旋转  
对a的左儿子的左子树进行一次插入  
对a的右儿子的右子树进行一次插入  
2) 双旋转  
对a的左儿子的右子树进行一次插入  
对a的右儿子的左子树进行一次插入  
* [示例代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/AVLTree)  
* [具体介绍](https://blog.csdn.net/wangdamingll/article/details/106078459)    
  
#### 3. 伸展树  
* 定义  
在二叉搜索树基础上允许树有任意的深度,但是在每次操作之后要使用一个调整规则进行调整,使得后面的操作效率要高,属于自调整类数据结构.  
* 时间复杂度  
任意连续M次操作在最坏的情形下花费时间O(MlogN),所以每次操作的摊还代价是O(logN)    
* 展开方法  
1) 之字形:执行AVL那样双旋转  
2) 一字型:类似AVL的单旋转
* [示例代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/SplayTree)  
* [具体介绍](https://blog.csdn.net/wangdamingll/article/details/106080019)  

#### 4. B树
* 定义  
类似二叉搜索树且带有一系列限制使其平衡的M阶树,树的高度比AVL其他树小,多用于数据存储    
* 插入和删除操作   
1) 插入操作会导致节点分裂  
2) 删除操作会导致节点领养  
* [具体介绍](https://blog.csdn.net/wangdamingll/article/details/106080496)

#### 5. 红黑树  
* 暂略  


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