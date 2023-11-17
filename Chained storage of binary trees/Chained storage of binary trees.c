#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BTNode {
	char show;//data
	struct BTNode* left;
	struct BTNode* right;
}BTNode;//一个指向左孩子一个指向右孩子，一个是存储的数据

typedef struct {
	BTNode* root;//指向根节点
	int count;//一共有多少个数据	
}BinaryTree;

BTNode* createBTNode(char show) {//创建结点
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));//使用 memset 函数将结构体中的所有成员都设置为零是一种保险措施，
	//可以确保程序运行时不会出现意外情况。
	node->show = show;//想要的值传入
	return node;
}

void initBTreeRoot(BinaryTree* tree, BTNode* node) {//初始化树根结点 
	tree->count = 1;
	tree->root = node;
}

BinaryTree* createBTree(BTNode* root) {
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (root) {
		initBTreeRoot(tree, root);
	}
	else {
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}

//插入结点  在树中插入newNode结点，该结点的双亲结点为parent， 
//flag==1该结点为左孩子， flag==0该结点为右孩子 
void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newNode, int flag) {
	if (flag == 1) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	tree->count++;
}

int main() {
	// 创建根节点
	BTNode* root = createBTNode('A');

	// 创建二叉树
	BinaryTree* tree = createBTree(root);

	// 创建其他节点
	BTNode* nodeB = createBTNode('B');
	BTNode* nodeC = createBTNode('C');
	BTNode* nodeD = createBTNode('D');
	BTNode* nodeE = createBTNode('E');

	// 插入节点
	insertBTNode(tree, root, nodeB, 1);
	insertBTNode(tree, root, nodeC, 0);
	insertBTNode(tree, nodeB, nodeD, 1);
	insertBTNode(tree, nodeB, nodeE, 0);

	return 0;
}
