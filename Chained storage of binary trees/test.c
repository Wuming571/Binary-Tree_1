#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BTNode {
	char show;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

typedef struct {
	BTNode* root;
	int count;
}BinaryTree;

BTNode* createBTNode(char show) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
}

void initBTreeRoot(BinaryTree* tree, BTNode* node) {
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

void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newnode,int falg) {
	if (falg == 1) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}
	tree->count++;
}

int main() {
	// 创建根节点
	BTNode* root = createBTNode('A');

	// 创建二叉树
	BinaryTree* tree = createBTree(root);

	// 创建其他节点
	BTNode* nodeB = createBTNode(2);
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
