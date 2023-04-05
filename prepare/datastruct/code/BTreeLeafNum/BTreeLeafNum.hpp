#ifndef __BTREE_LEAF_NUM__H__
#define __BTREE_LEAF_NUM__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;

/* 二叉树-----计算二叉树叶子节点个数
 *
 * 算法思想:
 * 1. 递归思想
 *
 * 算法特点:
 * 1. 节点无左右子树就是叶子节点
 * 2. 先序处理(节点会被访问三次,先序 中序 后序处理都可以)
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
        return ;
    }
    //std::cout<<root->val<<","; //先序:根左右
    BTreeEach(root->lc);
    std::cout<<root->val<<" ";//中序(左节点回溯时访问):左根右
    BTreeEach(root->rc);
    //std::cout<<root->val<<",";//后序(右节点回溯的时访问):左右根
}

//二叉树---计算二叉树叶子节点个数
void BTreeLeafNum(TreeNode* root,int& k)
{
    if(root== nullptr)
    {
        return ;
    }
    if(root->lc== nullptr&& root->rc== nullptr)
    {
        k++;
    }
    BTreeLeafNum(root->lc,k);
    BTreeLeafNum(root->rc,k);
}

int32_t BTreeLeafNumDFSPre(TreeNode* root)
{
    if(root == nullptr) return 0;
    if(root->lc == nullptr && root->rc == nullptr) return 1; //先序判断

    int32_t leftNum = 0;
    int32_t rightNum = 0;
    leftNum += BTreeLeafNumDFSPre(root->lc);
    rightNum += BTreeLeafNumDFSPre(root->rc);

    return (leftNum + rightNum);  //后序累加
}


int32_t BTreeLeafNumDFSInOrder(TreeNode* root)
{
    if(root == nullptr) return 0;

    int32_t num = 0;
    num += BTreeLeafNumDFSInOrder(root->lc);
    if(root->lc == nullptr && root->rc == nullptr)  //中序判断
    {
        num++;
    }
    num += BTreeLeafNumDFSInOrder(root->rc);
    return num;
}


int32_t BTreeLeafNumDFSPost(TreeNode* root)
{
    if(root == nullptr) return 0;

    int32_t num = 0;
    num += BTreeLeafNumDFSPost(root->lc);
    num += BTreeLeafNumDFSPost(root->rc);

    if(root->lc == nullptr && root->rc == nullptr) //后序判断
    {
        num++;
    }
    return  num;
}

int32_t BTreeLeafNumBFS(TreeNode* root)
{
    std::queue<TreeNode*> queue;
    queue.push(root);

    int32_t num = 0;
    while(!queue.empty())
    {
        TreeNode* node = queue.front();
        queue.pop();

        if(node->lc == nullptr && node->rc == nullptr) num++;
        if(node->lc != nullptr) queue.push(node->lc);
        if(node->rc != nullptr) queue.push(node->rc);
    }
    return num;
}


int TestBTreeLeafNum(){
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

    int num =0;
    BTreeLeafNum(&root,num);
    std::cout<<"tree leaf num(dfs pre):"<<num<<std::endl; //深度优先 --- 先序判断

    num = BTreeLeafNumDFSPre(&root); //深度优先 --- 先序判断
    std::cout<<"tree leaf num(dfs pre):"<<num<<std::endl;

    num = BTreeLeafNumDFSInOrder(&root); //深度优先 --- 中序判断
    std::cout<<"tree leaf num(dfs inorder):"<<num<<std::endl;

    num = BTreeLeafNumDFSPost(&root); //深度优先 --- 后序判断
    std::cout<<"tree leaf num(dfs post):"<<num<<std::endl;

    num = BTreeLeafNumBFS(&root); //深度优先 --- 后序判断
    std::cout<<"tree leaf num(bfs):"<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_LEAF_NUM__H__