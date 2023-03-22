#include <iostream>
using namespace std;

//题目:1->2->...->m...->n->...,将m->...->n部分翻转

//是否可以修改链表?
//是否是双向链表?

//------------------------
//如果可以修改链表

//如果是单向链表
//算法思路:一次遍历,用带头链表头插入的方式保存m->...->n的元素,然后拼接原m节点的前驱上,再拼接n的后驱链表即可

//如果是双向链表
//算法思路:采用双指针法,一次遍历定位到m 和 n , head指向m tail指向n, 利用双向链表特性,tail从n->...->m, head从m->....->n进行拼接即可
//代码实现

//------------------------

//------------------------
//如果不可以修改链表
//可以采用以空间换时间的思想,单独存储m->....->n的元素

//如果是单向链表m->...->n
//算法思路1:一次遍历即可,如果发现m,直接加入到栈容器,直到n结束,然后从stack依次取出即可.涉及到容器,看上去比较费时,虽然时间复杂度是O(N + 2(N-M))
//算法思路2:一次遍历,m->...->n,用另外一个带头链表采用头插入保存,保存结束后直接连接到新的链表上即可

//如果是双向链表,可以采用双指针法(因为可能m n 有重复),当然也可以单指针,直接指向n
//算法思路:也是一次遍历,head指向m tail指向n, 利用双向链表特性拼接n->....->m
//------------------------

typedef struct Node
{
    Node(int value){this->value = value;}
    int value = 0;
    Node* pre = nullptr;
    Node* next = nullptr;
}Node;

void PrintListNext(Node* head)
{
    Node* pCur = head;
    while(pCur != nullptr)
    {
        std::cout<<" "<<pCur->value<<" ";
        pCur = pCur->next;
    }
    std::cout<<std::endl;
}

void PrintListPre(Node* head)
{
    Node* pCur = head;
    while(pCur != nullptr)
    {
        std::cout<<" "<<pCur->value<<" ";
        pCur = pCur->pre;
    }
    std::cout<<std::endl;
}

int main()
{
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);

    node1->next = node2;
    node2->pre = node1;
    node2->next = node3;
    node3->pre = node2;
    node3->next = node4;
    node4->pre = node3;
    node4->next = node5;
    node5->pre = node4;

    //先打印一下双向链表
    PrintListNext(node1);
    PrintListPre(node5);

    int headValue = 2;
    int tailValue = 4;
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* cur = node1;
    int headPreValue = 0;
    while(cur != nullptr)
    {
        if(cur->value == headValue)
        {
            head = cur->pre;
            headPreValue = head->value;
        }else if(cur->value == tailValue)
        {
            tail = cur->next;

            //翻转合并
            while(cur->value != headPreValue)
            {
                Node* tmp = cur->pre;

                head->next = cur;
                cur->pre = head;

                head = head->next;
                cur = tmp;
            }

            //合并尾部
            while(tail != nullptr)
            {
                head->next = tail;
                tail->pre = head;

                tail = tail->next;
                head = head->next;
            }
            break;
        }
        cur = cur->next;
    }

    PrintListNext(node1);
    PrintListPre(node5);
    return 0;
}