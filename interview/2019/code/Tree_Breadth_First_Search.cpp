#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>

using namespace std;

//二叉树结点 二叉链表
typedef struct BinaryTreeNode {
	char ch;
	struct BinaryTreeNode* lchild;
	struct BinaryTreeNode* rchild;
}BinaryTreeNode;

//广度优先搜索
void BreathFirstSearch(BinaryTreeNode* root) {
	queue<BinaryTreeNode*> binaryTreeQueue;
	binaryTreeQueue.push(root);
	while (!binaryTreeQueue.empty()) {
		BinaryTreeNode* root = binaryTreeQueue.front();
		binaryTreeQueue.pop();
		cout << root->ch << " ";
		if(root->lchild!=NULL) binaryTreeQueue.push(root->lchild);
		if(root->rchild!=NULL) binaryTreeQueue.push(root->rchild);
	}
	return;
}

//测试
void test() {

	//创建结点
	BinaryTreeNode node1, node2, node3, node4, node5, node6;
	node1.ch = '1'; node1.lchild = NULL; node1.rchild = NULL;
	node2.ch = '2'; node2.lchild = NULL; node2.rchild = NULL;
	node3.ch = '3';	node3.lchild = NULL; node3.rchild = NULL;
	node4.ch = '4';	node4.lchild = NULL; node4.rchild = NULL;
	node5.ch = '5';	node5.lchild = NULL; node5.rchild = NULL;
	node6.ch = '6';	node6.lchild = NULL; node6.rchild = NULL;

	//建立结点关系
	node1.lchild = &node2;
	node1.rchild = &node3;

	node2.lchild = NULL;
	node2.rchild = &node4;

	node3.lchild = &node5;
	node3.rchild = NULL;

	node5.lchild = NULL;
	node5.rchild = &node6;

	//二叉树分层遍历(广度优先搜索)
	BreathFirstSearch(&node1);
}



int main() {
	test();
	cout << endl;
	system("pause");
	return EXIT_SUCCESS;
}