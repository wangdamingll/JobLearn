#ifndef __BTREE_NODE_NUM__H__
#define __BTREE_NODE_NUM__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;

/* 二叉树-----计算二叉树节点个数
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
 * 1. 既然要递归求节点个数,只要当前节点不为空,就可以累加统计了,先序 中序 后序都可以
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
    if(root == nullptr)
    {
        return;
    }
    //std::cout<<root->val<<","; //先序:根左右
    BTreeEach(root->lc);
    std::cout<<root->val<<" ";//中序(左节点回溯时访问):左根右
    BTreeEach(root->rc);
    //std::cout<<root->val<<",";//后序(右节点回溯的时访问):左右根
}

int32_t BTreeLeafNumDFS(TreeNode* root, int32_t& k)
{
    if(root == nullptr) return 0;
    k++;  //先序累加
    BTreeLeafNumDFS(root->lc, k);
    //k++;  //中序累加
    BTreeLeafNumDFS(root->rc, k);
    //k++;  //后序累加
    return 0;
}

int32_t BTreeLeafNumDFSPre(TreeNode* root)
{
    if(root == nullptr) return 0;

    int32_t num = 0;
    num ++;

    num += BTreeLeafNumDFSPre(root->lc);
    num += BTreeLeafNumDFSPre(root->rc);

    return num;
}


int32_t BTreeLeafNumDFSInOrder(TreeNode* root)
{
    if(root == nullptr) return 0;

    int32_t num = 0;
    num += BTreeLeafNumDFSInOrder(root->lc);
    num++;
    num += BTreeLeafNumDFSInOrder(root->rc);
    return num;
}


int32_t BTreeLeafNumDFSPost(TreeNode* root)
{
    if(root == nullptr) return 0;

    int32_t num = 0;
    num += BTreeLeafNumDFSPost(root->lc);
    num += BTreeLeafNumDFSPost(root->rc);
    num++;
    return  num;
}

int32_t BTreeNodeNumBFS(TreeNode* root)
{
    std::queue<TreeNode*> queue;
    queue.push(root);

    int32_t num = 0;
    while(!queue.empty())
    {
        TreeNode* node = queue.front();
        queue.pop();
        
        num++;

        if(node->lc != nullptr) queue.push(node->lc);
        if(node->rc != nullptr) queue.push(node->rc);
    }
    return num;
}


int TestBTreeLeafNum()
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

    int32_t k = 0;
    BTreeLeafNumDFS(&root, k); //深度优先 --- 先序判断
    std::cout<<"tree node num(dfs pre):"<<k<<std::endl;

    int num = BTreeLeafNumDFSPre(&root); //深度优先 --- 先序判断
    std::cout<<"tree node num(dfs pre):"<<num<<std::endl;

    num = BTreeLeafNumDFSInOrder(&root); //深度优先 --- 中序判断
    std::cout<<"tree node num(dfs inorder):"<<num<<std::endl;

    num = BTreeLeafNumDFSPost(&root); //深度优先 --- 后序判断
    std::cout<<"tree node num(dfs post):"<<num<<std::endl;

    num = BTreeNodeNumBFS(&root); //深度优先 --- 后序判断
    std::cout<<"tree node num(bfs):"<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_NODE_NUM__H__
