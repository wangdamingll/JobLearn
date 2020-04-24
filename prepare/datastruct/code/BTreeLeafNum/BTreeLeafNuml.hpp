#ifndef __BTREE_LEAF_NUM__H__
#define __BTREE_LEAF_NUM__H__

#include <iostream>
#include <chrono>
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

//二叉树---计算二叉树叶子节点个数
void BTreeKNodeNum(TreeNode* root,int& k){
    if(root== nullptr){
        return ;
    }
    if(root->lc== nullptr&& root->rc== nullptr){
        k++;
    }
    BTreeKNodeNum(root->lc,k);
    BTreeKNodeNum(root->rc,k);
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
    BTreeKNodeNum(&root,num);
    std::cout<<"leaf:"<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_LEAF_NUM__H__