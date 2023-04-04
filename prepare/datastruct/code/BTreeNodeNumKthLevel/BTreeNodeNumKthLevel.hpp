#ifndef __BTREE_NODE_NUM_KTH_LEVEL__H__
#define __BTREE_NODE_NUM_KTH_LEVEL__H__

#include <iostream>
#include <chrono>
using namespace std;

/* 二叉树-----二叉树第K层节点个数
 *
 * 算法思想:
 * 1. 递归思想
 *
 * 算法特点:
 * 1. 求第K层的节点数,也就是要求第K-1层有无左右子树,存在就统计
 * 2. 第K-1层先序判断处理
 * */

namespace BTree1
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

int32_t BTreeKNode(TreeNode* root, int32_t k)
{
    if(root == nullptr || k < 1) //root == nullptr判断上一层父节点有无子节点  k < 1 是k的合法性判断
    {
        return 0;
    }

    if(k == 1) return 1; //说明父节点有此节点

    int32_t leftNum = BTreeKNode(root->lc, k - 1); //比如求第2层节点数 就是求第1层有无左节点
    int32_t rightNum = BTreeKNode(root->rc, k - 1);//比如求第2层节点数 就是求第1层有无右节点

    return (leftNum + rightNum);
}

//看上去不太优雅
int32_t BTreeKNode1(TreeNode* root, int32_t k, int32_t depth)
{
    if(root == nullptr)
    {
        return 0;
    }
    if(k == 1) return 1;

    int32_t tmp = 0;
    if(depth == k - 1) //k层节点数 就是 k - 1层有无左右子树
    {
        if(root->lc != nullptr)
        {
            tmp++;
        }
        if(root->rc != nullptr)
        {
            tmp++;
        }
        return tmp;
    }
    tmp += BTreeKNode1(root->lc, k, depth + 1);
    tmp += BTreeKNode1(root->rc, k, depth + 1);
    return tmp;
}

int TestBTreeKNodeNum()
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
    std::cout<<"请输入第K层:";
    std::cin >> k;
    int32_t total = BTreeKNode(&root,k);//二叉树搜索树寻找第K层节点数
//    int32_t depth = 1;
//    int32_t total = BTreeKNode1(&root,k, depth);//二叉树搜索树寻找第K层节点数
    std::cout <<"第"<<k<<"层节点数:"<<total<< std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_NODE_NUM_KTH_LEVEL__H__