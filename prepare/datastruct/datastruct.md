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
* 开放地址法(线性探测法、平方探测法)  
1. 线性探测法  
(1)hi(x) = ( hash(x) + f(i) ) mod tablesize,且f(0)=0;f(i)=i;  
(2)装填因子a必须要小于等于0.5  
(3)惰性删除  
1. 平方探测法  
(1)hi(x) = ( hash(x) + f(i) ) mod tablesize,且f(0)=0;f(i)=i^2;  
(2)装填因子a必须要小于等于0.5,并且tablesize必须为素数.因为这样的话,表至少有一半为空时,产生冲突时,平方探测法总能够插入成功   
(3)惰性删除  
* 双散列    
f(i)=i * hash2(x)    
hash2(x) = R -(x mod R),R为小于tablesize的素数  
hi(x) = (hash(x) + f(i)) mod tablesize = (hash(x) + i * hash2(x)) mod tablesize  
### 3. 以最坏情形O(1)访问的散列表  
* 完美散列  
* 杜鹃散列(布谷鸟散列)  
1. 常用较小的填装因子(小于0.5不包括0.5)且多于两个散列函数实现  
2. [示例代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/CuckooHashTable)  
* 跳房子散列  
1. 尝试改进线性探测算法  
2. 定义:通过预先确定的、在计算机结构体系的基础上优化的常数,来为探测序列的最大长度定界.  
### 示例代码
* [哈希表介绍(CSDN)](https://blog.csdn.net/wangdamingll/article/details/104198484)  
* [基于哈希表简单实现HashMap(拉链法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap1.cpp)  
* [基于哈希表简单实现HashMap(线性探查法.二次探查法)](https://github.com/wangdamingll/JobLearn/blob/master/interview/2019/code/HashMap2.cpp)  


## 堆  
### 堆的分类  
#### 1. 二叉堆(堆)  
* 定义  
二叉堆是完全二叉树或者是近似完全二叉树.
* 时间复杂度  
平均O(logN)  
* 二叉堆特性  
1. 结构特性:是一颗完全二叉树  
2. 堆序特性:父节点大于或等于其各子节点(最大堆);父节点小于或等于其各子节点(最小堆)    
* 堆常用操作  
1. 建堆:
(1)将N项插入堆中:执行N次插入操作  
(2)将N项任意放入一颗空树中:放入完成后,从最后一个非叶子节点开始执行下浮操作  
2. 插入:在尾部插入,采用上浮策略  
3. 删除最值:删除根节点,将最后一个节点放到根节点位置,采用下浮策略  
* 堆其他操作(以最小堆为例)  
1. 降低关键字的值:采用上浮策略  
2. 增加关键字的值:采用下浮策略  
3. 删除除堆中的某个关键字:先执行1,降低无穷大的差值,再执行删除最值操作    
* [二叉堆代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BinaryHeap)  

#### 2. d堆  
* 定义  
d堆是二叉堆的简单推广,像一个二叉堆,只是所有节点有d个儿子  
* 使用场景  
用法与B树用法相似,d堆高度低,适用于主存存不下的情况    

#### 3. 左式堆  
* 定义  
又称作最左堆、左倾堆,是堆的一种,保留了堆的结构性和堆序性  
* 时间复杂度  
插入 删除 合并: O(logN)  
* 特点  
1. 结构性:任一节点的零路径长比它的诸儿子节点的零路径长的最小值多1. 不再是一棵完全二叉树(Complete tree),而且是一棵极不平衡的树  
2. 堆序性:任意结点的值比其子树任意结点值均小(最小堆的特性)    
* 使用场景  
适用于合并(merge)较多的场景  
* [左式堆代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/LeftistHeap)  

#### 4. 斜堆  
* 定义   
是左式堆的自调节形式,是具有堆序的二叉树,不存在对树的结构性的限制  
* 时间复杂度  
对任意M次连续操作,总的最坏情形运行时间是O(MlogN),摊还开销为O(logN)   
* 特点    
堆序性:任意结点的值比其子树任意结点值均小(最小堆的特性)    
* 使用场景  
适用于合并(merge)较多的场景    

#### 5. 二项队列  
* 定义  
二项队列不同于左式堆和二叉堆等优先队列的实现之处在于,一个二项队列不是一棵堆序的树,而是堆序树的集合,即森林.堆序树中的每棵树都是由约束形式的,叫做二项树.  
* 时间复杂度  
合并 插入 删除:最坏的时间复杂度O(logN), 但是插入的平均时间复杂度O(1)    
* 使用场景  
适用于合并(merge)和插入较多的场景  
* [二项队列代码](https://github.com/wangdamingll/JobLearn/tree/master/prepare/datastruct/code/BinomialQueue)    


## 树  
### 树的分类  
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