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

//二叉树---二叉搜索树第K层节点个数
int BTreeKNodeNum(TreeNode* root,int k){
    if(root== nullptr || k<1){//这里是判断上一个层(K-1)层有无左右子树(也就是第K层节点数统计)
        return 0;
    }

    if(k==1){       //先序处理
        return 1;
    }

    int leftNum = BTreeKNodeNum(root->lc,k-1);
    int rightNum = BTreeKNodeNum(root->rc,k-1);

    return (leftNum+rightNum);
}

int TestBTreeKNodeNum(){
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

    int k=0;
    std::cout<<"请输入第K层:";
    std::cin>>k;

    int tmp = BTreeKNodeNum(&root,k);
    std::cout<<tmp<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}
#endif //__BTREE_NODE_NUM_KTH_LEVEL__H__