#include <iostream>
#include <string>
#include <stack>

using namespace std;

//题目:1->2->...->m...->n->...,将m->...->n部分翻转

//思路
//1. 采用头插法: 1) 先保存特定区域的头一个节点 2) 翻转的部分采用头插法 注意在特殊区域时 先保存当前节点
//2. 采用容器法: 1) 先保存特定区域的头一个节点 2) 翻转的部分借助statck容器先进后出的特点
//3. 采用3指针法: 1) 1个指针保存特定区域的前一个节点 2)翻转部分采用双指针法

typedef struct Node
{
    Node(int value){this->value = value;}
    int value = 0;
    Node* next = nullptr;
}Node;

void Print(Node* node)
{
    Node* pCur = node;
    while (pCur != nullptr)
    {
        std::cout<<pCur->value<<"->";
        pCur = pCur->next;
    }
    std::cout<<std::endl;
}

int main()
{
    Node node1(1 );
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;

    Print(&node1);

    //采用3指针法
    Node* pOrHead = nullptr;//保存特定目标区域的前一个节点
    Node* pTmpPre = nullptr;//用于特定区域的双指针翻转
    Node* pCur = &node1;
    while(pCur != nullptr)
    {
        if(pCur->value < 2)
        {
            pOrHead = pCur;
            pTmpPre = pCur;
            pCur = pCur->next;
            continue;
        }

        if(pTmpPre->value >= 2)
        {
            //1->2->3->4->5  ==> 1 -> 4 -> 3 -> 2 -> 5
            //用双指针法:特定区域执行翻转
            while(pCur != nullptr && pTmpPre->value >= 2 && pCur->value <= 4)
            {
                Node* tmp = pCur->next; //保存当前节点下一个的节点
                pCur->next = pTmpPre; //翻转

                pTmpPre = pCur;
                pCur = tmp;
            }

            Node* pTmp = pOrHead->next;
            pOrHead->next = pTmpPre;
            pTmp->next = pCur;
            break;
        }

        pTmpPre = pCur;
        pCur = pCur->next;
    }

    Print(&node1);
}