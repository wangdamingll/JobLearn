#include <iostream>
#include <string>

using namespace std;

//题目:1->2->...->m...->n->...,将m->...->n部分翻转

//思路
//1. 采用头插法: 1) 先保存特定区域的头一个节点 2) 翻转的部分采用头插法
//2. 采用容器法: 1) 先保存特定区域的头一个节点 2) 翻转的部分借助statck容器先进后出的特点
//3. 采用4指针法: 1) 2个指针保存特定区域的前一个和后一个节点 2)翻转部分采用双指针法

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

    Node head(0);
    Node* pTmpHead = nullptr;//保存特定目标区域的前一个节点
    Node* pCur = &node1;
    while(pCur != nullptr)
    {
        if(pCur->value < 2)
        {
            pTmpHead = pCur;
            pCur = pCur->next;
            continue;
        }

        if(pCur->value > 4)
        {
            //重新链接起来
            //1->2->3->4->5  ==> 1 -> 4 -> 3 -> 2 -> 5
            Node* pTmp = head.next;
            while (pTmp != nullptr)
            {
                pTmpHead->next = pTmp;
                pTmp = pTmp->next;
                pTmpHead = pTmpHead->next;
            }
            pTmpHead->next = pCur;
            break;
        } else
        {
            Node* tmp = pCur;   //保存当前节点
            pCur = pCur->next;  //更新下一个节点

            //头插法
            tmp->next = head.next;
            head.next = tmp;
        }
    }

    Print(&node1);
}