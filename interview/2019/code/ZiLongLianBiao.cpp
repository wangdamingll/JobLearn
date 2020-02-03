#include <iostream>
#include <cstdio>
using namespace std;

//题目:1->2->...->m...->n->...,将m->...->n部分翻转
//思路:翻转链表采用透插法(带头链表)
//然后将 1->m m->n n->.. 连接起来

struct LIST_NODE {
	LIST_NODE() {
		value = -1;
		next = nullptr;
	}
	LIST_NODE(int value) {
		this->value = value;
		next = nullptr;
	}
	int value;
	LIST_NODE* next;
};
using ListNode = LIST_NODE;

void PrintList(ListNode* head) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	ListNode* cur = head->next;
	while (cur != nullptr) {
		cout << cur->value << " ";
		cur = cur->next;
	}
	cout << endl;
}

int main()
{
	ListNode* head = new ListNode();
	ListNode* node1 = new ListNode(1);
	ListNode* node2 = new ListNode(2); //m
	ListNode* node3 = new ListNode(3);
	ListNode* node4 = new ListNode(4); //n
	ListNode* node5 = new ListNode(5);
	head->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	PrintList(head);

	//这里简单不考虑 链表数量 m n的影响 和内存泄漏影响
	int index = 1;
	int m = 2;
	int n = 4;
	ListNode* pre = nullptr;
	ListNode* back = nullptr;
	ListNode* operHead = new ListNode();
	ListNode* operBack = nullptr;
	ListNode* cur = head->next;
	while (cur != nullptr) {
		if (index == m - 1) {  //保存原链表最前一个节点(需要变换的节点的前一个节点)
			pre = cur;
			cur = cur->next;
			index++;
			continue;
		}
		if (index == n + 1) {  //保存原链表最后一个节点(需要变换的节点的后一个节点)
			break;
		}

		ListNode* tmp = new ListNode();
		*tmp = *cur;
		tmp->next = operHead->next;
		operHead->next = tmp;
		if (index == m) {  //保存需要变换的节点的最后一个节点)
			operBack = tmp;
		}
		cur = cur->next;
		index++;
	}
	PrintList(operHead);

	//拼接及会造成原来链表的对应部分内存泄漏，当然可以不采用new的方式
	pre->next = operHead->next;
	operBack->next = cur;
	PrintList(head);

	return 0;
}