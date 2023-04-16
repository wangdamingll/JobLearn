#ifndef __BTREE_BROADCAST_EACH__H__
#define __BTREE_BROADCAST_EACH__H__

#include <iostream>
#include <chrono>
#include <queue>
#include <stack>
using namespace std;

/* 二叉树-----广度优先遍历
 * 算法思想:
 * 1. 层序遍历
 * 算法特点:
 * 1. 借助队列方式
 * 2. 每个节点被访问一次
 *
 * 二叉树-----非递归先序遍历
 * 算法思想:
 * 和递归遍历先序顺序相同
 * 算法特点:
 * 1. 借助栈的先入后出思想
 * 2. 在深入左子树的同时访问节点元素(入栈的时候访问)
 *
 * 二叉树-----非递归中序遍历
 * 算法思想:
 * 和递归遍历中序遍历的顺序相同
 * 算法特点:
 * 1. 借助栈的先入后出的特点
 * 2. 在深入左子树后 取元素的时候访问(出栈的时候访问)
 *
 * 二叉树-----非递归后序遍历
 * 算法思想:
 * 参考网址:
 * https://blog.csdn.net/MBuger/article/details/70186143?ydreferer=aHR0cHM6Ly93d3cuZ29vZ2xlLmNvbS5oay8%3D?ydreferer=aHR0cHM6Ly93d3cuZ29vZ2xlLmNvbS5oay8%3D
 * https://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html
 * 算法特点:
 * 1. 需要借助栈
 * 2. 一定要分析节点的访问时机,也就是说右子树必须要访问完才行
 * 方法分析:
 * BTreeEachPost1方法思路:
 * 要保证根结点在左孩子和右孩子访问之后才能访问，
 * 因此对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
 * 若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问
 *
 * BTreeEachPost2方法思路:
 * 对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，此时该结点出现在栈顶，但是此时不能将其出栈并访问，因此其右孩子还为被访问。
 * 所以接下来按照相同的规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。这样就保证了正确的访问顺序。
 * 可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。
 *
 * */

namespace BTreeEach2
{

//二叉树结点 二叉链表
struct TreeNode
{
    int val = 0;
    bool isFirst = true;//是否第一次出现在栈顶
    struct TreeNode* lc = nullptr;//左孩子节点
    struct TreeNode* rc = nullptr;//右孩子节点
};

//二叉树---深度优先遍历
void BTreeEachDFS(TreeNode* root)
{
    if(root == nullptr) return ;

//    std::cout<<root->val<<" "; //先序
    BTreeEachDFS(root->lc);
    std::cout<<root->val<<" ";  //中序
    BTreeEachDFS(root->rc);
//    std::cout<<root->val<<" ";  //后序
}

//二叉树---广度优先遍历
void BTreeEachBrodecast(TreeNode* root)
{
    std::queue<TreeNode*> queue;
    queue.push(root);
    while(!queue.empty())
    {
        TreeNode* node = queue.front();
        queue.pop();
        std::cout<<node->val<<" ";//访问
        if(node->lc!= nullptr) queue.push(node->lc);
        if(node->rc!= nullptr) queue.push(node->rc);
    }
}

//二叉树---先序遍历(非递归)
void BTreeEachPre(TreeNode* root)
{
    if(root == nullptr) return;
    std::stack<TreeNode*> st;

    while(!st.empty() || root != nullptr)
    {
        //一路查到最左节点
        while(root != nullptr)
        {
            std::cout<<root->val<<" ";//访问
            st.push(root);
            root = root->lc;
        }

        if(!st.empty())
        {
            root = st.top();
            st.pop();
            root = root->rc;
        }
    }
    std::cout<<std::endl;
}

//二叉树---中序遍历(非递归)
void BTreeEachMid(TreeNode* root)
{
    if(root == nullptr) return;
    std::stack<TreeNode*> st;

    while(!st.empty() || root != nullptr)
    {
        //一路查到最左节点
        while(root != nullptr)
        {
            st.push(root);
            root = root->lc;
        }

        if(!st.empty())
        {
            root = st.top();
            st.pop();
            std::cout<<root->val<<" ";//访问
            root = root->rc;
        }
    }
    std::cout<<std::endl;
}

//二叉树---后序遍历(非递归)
void BTreeEachPost1(TreeNode* root)
{
    if(root == nullptr) return ;
    std::stack<TreeNode*> st;
    st.push(root);

    TreeNode* pCur = nullptr;             //当前结点
    TreeNode* pPre = nullptr;             //前一次访问的结点

    while(!st.empty())
    {
        pCur = st.top();
        if((pCur->lc == nullptr && pCur->rc == nullptr) || (pPre != nullptr && (pPre == pCur->lc || pPre == pCur->rc)))
        {
            cout<< pCur->val <<" ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过
            st.pop();
            pPre = pCur;
        }
        else
        {
            if(pCur->rc != nullptr) st.push(pCur->rc);
            if(pCur->lc != nullptr) st.push(pCur->lc);
        }
    }
    std::cout<<std::endl;
}

//二叉树---后序遍历(非递归)
void BTreeEachPost2(TreeNode* root)
{
    if(root == nullptr) return ;
    std::stack<TreeNode*> st;
    TreeNode * pCur = root;
    TreeNode* temp = nullptr;

    while(pCur != nullptr || !st.empty())
    {
        while(pCur != nullptr)              //沿左子树一直往下搜索，直至出现没有左子树的结点
        {
            pCur->isFirst = true;
            st.push(pCur);
            pCur = pCur->lc;
        }

        if(!st.empty())
        {
            temp = st.top();
            st.pop();
            if(temp->isFirst)     //表示是第一次出现在栈顶
            {
                temp->isFirst = false;
                st.push(temp);
                pCur = temp->rc;
            }
            else   //第二次出现在栈顶
            {
                std::cout << temp->val <<" ";
                pCur = nullptr;
            }
        }
    }
    std::cout<<std::endl;
}

int TestBTreeEach()
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

    BTreeEachBrodecast(&root);//二叉树---广度优先遍历
    std::cout << std::endl;

    BTreeEachDFS(&root); //用于对照后面的写法是否有错误
    std::cout << std::endl;

    BTreeEachPre(&root);//二叉树---非递归-先序遍历
    std::cout << std::endl;

    BTreeEachMid(&root);//二叉树---非递归-中序遍历
    std::cout << std::endl;

    BTreeEachPost1(&root);//二叉树---非递归-后序遍历
    std::cout << std::endl;
    BTreeEachPost2(&root);//二叉树---非递归-后序遍历
    std::cout << std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;

    return 0;
}

}

#endif //__BTREE_BROADCAST_EACH__H__