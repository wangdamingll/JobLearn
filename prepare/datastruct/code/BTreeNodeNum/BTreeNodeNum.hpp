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
 * 1. 既然要递归求节点个数,当然要知道当前节点的左右子树节点各是多少,所以要用后序处理统计了
 * */

namespace BTree1{

//二叉树结点 二叉链表
struct TreeNode {
    int val =0;
    struct TreeNode* lc = nullptr;//左孩子节点
    struct TreeNode* rc = nullptr;//右孩子节点
};

void BTreeEach(TreeNode* root){
    if(root == nullptr){
        return;
    }
    BTreeEach(root->lc);
    std::cout<<root->val<<" ";
    BTreeEach(root->rc);
}

//二叉树---计算二叉树节点个数(深度优先)
int BTreeNodeNumDFS(TreeNode* root){
    if(root== nullptr){
        return 0;
    }
    int leftNum = BTreeNodeNumDFS(root->lc);
    int rightNum = BTreeNodeNumDFS(root->rc);
    return (leftNum+rightNum+1); //后序处理:左子树节点数 + 右子树节点数 + 当前节点
}

//二叉树---计算二叉树节点个数(广度优先)
int BTreeNodeNumBFS(TreeNode* root){
    if(root == nullptr){
        return 0;
    }

    int num=0;
    std::queue<TreeNode*> queue;
    queue.push(root);
    num++;

    while(!queue.empty()){
        TreeNode* node = queue.front();
        queue.pop();
        if(node->lc!= nullptr){
            queue.push(node->lc);
            num++;
        }
        if(node->rc!= nullptr){
            queue.push(node->rc);
            num++;
        }
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

    int num = BTreeNodeNumDFS(&root); //深度优先
    std::cout<<"node num(dfs):"<<num<<std::endl;

    num = BTreeNodeNumBFS(&root); //广度优先
    std::cout<<"node num(bfs):"<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_NODE_NUM__H__
