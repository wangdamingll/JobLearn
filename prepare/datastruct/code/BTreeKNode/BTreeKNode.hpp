#ifndef __BTREE_EACH__H__
#define __BTREE_EACH__H__

#include <iostream>
#include <chrono>
using namespace std;

/* 二叉树-----寻找二叉搜索树的第K大/小节点
 *
 * 算法思想:
 * 1. 递归思想
 * 2. 递归左节点回溯的时候判断是否是第K大/小节点
 * 3. 二叉搜索树深度优先遍历,如果是中序遍历,则输出的序列是升序序列
 *
 * 算法特点:
 * 1. 每个节点会访问三次
 * 2. 递归左节点回溯的时候判断是否是第K大/小节点
 * 3. 右左节点回溯,一旦找到第K大/小节点,便不能再次递归进入右节点
 * */

namespace BTreeKNode
{

//二叉树结点 二叉链表
struct TreeNode
{
    int val =0;
    struct TreeNode* lc = nullptr;//左孩子节点
    struct TreeNode* rc = nullptr;//右孩子节点
};

void BTreeEach(TreeNode* node)
{
    if(node == nullptr)
    {
        return ;
    }
    //std::cout<<node->val<<","; //先序:根左右
    BTreeEach(node->lc);
    std::cout<<node->val<<" ";//中序(左节点回溯时访问):左根右
    BTreeEach(node->rc);
    //std::cout<<node->val<<",";//后序(右节点回溯的时访问):左右根
}

TreeNode* BTreeKNode(TreeNode* root, int32_t& k)
{
    if(root == nullptr|| k == 0)
    {
        return nullptr;
    }

    TreeNode* res = BTreeKNode(root->lc,k);//递归左子树
    if(k == 1)
    {
        res = root; //这里真正赋值
    }

    k--;//计数

    if(k > 0) //找到了第K大节点,则不需要再递归右子树
    {
        res = BTreeKNode(root->rc,k);
    }
    return  res;
}

int TestBTreeKNode()
{
    auto start = std::chrono::steady_clock::now();

    //创建结点
    TreeNode root,node1, node2, node3, node4, node5, node6;
    root.val = 5;
    node1.val = 3;
    node2.val = 7;
    node3.val = 2;
    node4.val = 4;
    node5.val = 6;
    node6.val = 8;

    //建立结点关系
    root.lc = &node1;
    root.rc = &node2;
    node1.lc = &node3;
    node1.rc = &node4;
    node2.lc = &node5;
    node2.rc = &node6;

    BTreeEach(&root);
    std::cout<<std::endl;

    int k = 0;
    std::cout<<"请输入第K小节点:";
    std::cin>>k;
    TreeNode* kNode = BTreeKNode(&root,k);//二叉树搜索树寻找第K小节点
    std::cout <<kNode->val<< std::endl;

    std::cout<<"请输入第K大节点:";
    std::cin>>k;
    if(k >= 7)
    {
        std::cout<<"k is less 7"<<std::endl;
    }
    k = 7 - k + 1; //比如第1大就是第7小
    kNode = BTreeKNode(&root,k);//二叉树搜索树寻找第K大节点
    std::cout <<kNode->val<< std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_EACH__H__