#ifndef __BTREE_EACH__H__
#define __BTREE_EACH__H__

#include <iostream>
#include <chrono>
using namespace std;

/* 二叉树-----递归遍历
 *
 * 算法思想:
 * 1. 递归思想
 *
 * 算法特点:
 * 1. 每个节点会访问三次
 * 2. 二叉搜索树中序遍历是一个升序数列
 * */

namespace BTreeEach1{

//二叉树结点 二叉链表
struct TreeNode {
    int val =0;
    struct TreeNode* lc = nullptr;//左孩子节点
    struct TreeNode* rc = nullptr;//右孩子节点
};


//二叉树---递归遍历
void BTreeEach(TreeNode* root){
    if(root == nullptr){
        return ;
    }
    //std::cout<<root->val<<std::endl; 先序:根左右
    BTreeEach(root->lc);
    std::cout<<root->val<<" ";//中序(左节点回溯时访问):左根右
    BTreeEach(root->rc);
    //std::cout<<root->val<<std::endl;//后序(右节点回溯的时访问):左右根
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
    BTreeEach(&root);//二叉树---递归遍历
    std::cout << std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_EACH__H__