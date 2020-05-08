#ifndef __STACK_USE2__H__
#define __STACK_USE2__H__

#include <iostream>
#include <string>
#include <chrono>
#include <stack>
using namespace std;

/* 栈-----由后缀表达式构建一颗表达式树
 *
 * 算法思想:
 *
 *
 * */

//树节点
struct Node{
    Node()=default;
    explicit Node(char ch1):ch(ch1){}

    char ch = ' ';
    Node* lc = nullptr;
    Node* rc= nullptr;
};

void PrintTree(Node* root){
    if(root== nullptr){
        return ;
    }
    std::cout<<root->ch<<" ";
    PrintTree(root->lc);
    PrintTree(root->rc);
}

//由后缀表达式构建一颗表达式树
Node* CreateExprTree(const std::string& suffix){
    std::stack<Node*> stack;

    for(auto& ch : suffix){
        if(ch == ' '){
            continue;
        }
        if((65<=ch&&ch<=90)||(97<=ch&&ch<=122)||(48<=ch&&ch<=57)){//A-Z a-z 0-9 字母或者数字
            Node* node = new Node{ch};
            stack.push(node);
            continue;
        }

        //如果是操作符
        if(stack.size()<2){//有错误
            return nullptr;
        }

        auto rc = stack.top();
        stack.pop();
        auto lc = stack.top();
        stack.pop();

        Node* root = new Node{ch};
        root->lc = lc;
        root->rc = rc;
        stack.push(root);
    }

    return stack.top();
}

int TestStackUse2(){
    auto start = std::chrono::steady_clock::now();

    const std::string suffixStr = "a b + c d e + * *";
    Node* root = CreateExprTree(suffixStr);
    PrintTree(root);
    std::cout<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;
    return 0;
}


#endif //__STACK_USE2__H__