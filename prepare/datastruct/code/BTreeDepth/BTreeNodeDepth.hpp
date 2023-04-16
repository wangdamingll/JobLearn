#ifndef __BTREE_DEPTH__H__
#define __BTREE_DEPTH__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;

/* 二叉树-----计算二叉树深度
 *
 * 算法思想:
 * 1. 深度优先思想(递归)
 * 2. 广度优先思想
 *
 * 算法特点:
 * 1. 深度优先借助递归
 * 2. 广度优先借助队列
 *
 * 思考:
 * 1. 既然要递归求树的深度,当然要知道当前节点的左右子树的深度各是多少,然后取最大值,然后+1,所以要后序处理
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

void BTreeEach(TreeNode* root)
{
    if(root == nullptr){
        return;
    }
    BTreeEach(root->lc);
    std::cout<<root->val<<" ";
    BTreeEach(root->rc);
}

//二叉树---计算二叉树深度(深度优先)
int BTreeDepthDFS(TreeNode* root)
{
    if(root== nullptr)
    {
        return 0;
    }
    int leftDepth = BTreeDepthDFS(root->lc);
    int rightDepth = BTreeDepthDFS(root->rc);
    return (std::max(leftDepth,rightDepth) + 1); //后序处理:选取最大值
}

//二叉树---计算二叉树深度(广度优先)
int BTreeDepthBFS(TreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }

    int lDepth=0;//左子树深度
    int rDepth =0;//右子树深度
    std::queue<TreeNode*> queue;
    queue.push(root);
    while(!queue.empty())
    {
        TreeNode* node = queue.front();
        queue.pop();
        if(node->lc!= nullptr)
        {
            queue.push(node->lc);
            lDepth++;
        }
        if(node->rc!= nullptr)
        {
            queue.push(node->rc);
            rDepth++;
        }
    }
    return std::max(lDepth,rDepth);
}

int TestBTreeDepth()
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
    //node2.rc = &node6;
    node4.lc = &node6;

    BTreeEach(&root);
    std::cout<<std::endl;

    int depth = BTreeDepthDFS(&root); //深度优先
    std::cout<<"tree depth(dfs):"<<depth<<std::endl;

    depth = BTreeDepthBFS(&root); //广度优先
    std::cout<<"tree depth(bfs):"<<depth<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_DEPTH__H__