#ifndef __BTREE_BROADCAST_EACH__H__
#define __BTREE_BROADCAST_EACH__H__

#include <iostream>
#include <chrono>
#include <queue>
using namespace std;

/* 二叉树-----广度优先遍历
 *
 * 算法思想:
 * 1. 广度优先思想
 *
 * 算法特点:
 * 1. 借助队列方式
 * 2. 每个节点被访问一次
 * */

namespace BTreeEach2{

//二叉树结点 二叉链表
struct TreeNode {
    int val =0;
    struct TreeNode* lc = nullptr;//左孩子节点
    struct TreeNode* rc = nullptr;//右孩子节点
};

//二叉树---广度优先遍历
void BTreeEach(TreeNode* root){
    std::queue<TreeNode*> queue;
    queue.push(root);
    while(!queue.empty()){
        TreeNode* node = queue.front();
        queue.pop();
        std::cout<<node->val<<" ";//访问
        if(node->lc!= nullptr) queue.push(node->lc);
        if(node->rc!= nullptr) queue.push(node->rc);
    }
}

int TestBTreeEach(){
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

    //遍历
    BTreeEach(&root);//二叉树---广度优先遍历
    std::cout << std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}

#endif //__BTREE_BROADCAST_EACH__H__