#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BTNode { //二叉树结点     
	char show;
	struct BTNode* left;
	struct BTNode* right;
	int ltag;
	int rtag;
}BTNode;

typedef struct {//二叉树 
	BTNode* root;
	int count;//结点数目 
}BinaryTree;

BTNode* pre = NULL;

//创建结点 
BTNode* createBTNode(char show) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}
//初始化树根结点 
void initBTreeRoot(BinaryTree* tree, BTNode* node) {
	tree->count = 1;
	tree->root = node;
}
//创建树 
BinaryTree* createBTree(BTNode* root) {
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	memset(tree, 0, sizeof(BinaryTree));
	if (root) {//非空 
		initBTreeRoot(tree, root);
	}
	else {//空树 
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

//访问一个结点
//进行线索化
void visitBTNode(BTNode* node) {
	if (node)
	{
		printf("%c ", node->show);
	}

	if (node->left == NULL)
	{
		node->left = pre;
		node->ltag = 1;//指向前驱线索	
	}
	if (pre != NULL && pre->right == NULL)
	{
		pre->right = node;
		pre->rtag = 1;//指向后继线索 
	}
	pre = node; //

}

//中序遍历 
void inOrder(BTNode* node) {
	if (node) {
		inOrder(node->left);
		visitBTNode(node);
		inOrder(node->right);
	}
}
void inOrderBTree(BinaryTree* tree) {
	if (tree->root) {
		inOrder(tree->root);
	}
}

//中序遍历找后继结点
BTNode* nextNodeB(BTNode* x) {
	if (x->rtag) {
		return x->right;
	}
	else {
		BTNode* p = x->right;
		while (p->ltag==0) {
			p = p->left;
		}
		return p;
	}
}

//中序遍历找前驱结点
BTNode* nextNodeF(BTNode* x) {
	if (x->ltag) {
		return x->left;
	}
	else {
		BTNode* p = x->left;
		while (p->rtag==0) {
			p = p->right;
		}
		return p;
	}
}

// 查找具有给定 show 值的节点
BTNode* findNode(BTNode* node, char show) {
	if (node == NULL) {
		return NULL;
	}
	if (node->show == show) {
		return node;
	}
	BTNode* foundNode = findNode(node->left, show);
	if (foundNode == NULL) {
		foundNode = findNode(node->right, show);
	}
	return foundNode;
}

// 打印给定 show 值的节点的前驱和后继
void printPredecessorAndSuccessor(BinaryTree* tree, char show) {
	BTNode* node = findNode(tree->root, show);
	if (node == NULL) {
		printf("没有找到 show 值为 %c 的节点\n", show);
		return;
	}
	BTNode* predecessor = nextNodeF(node);
	BTNode* successor = nextNodeB(node);

	printf("给定节点：%c\n", node->show);
	if (predecessor != NULL) {
		printf("前驱：%c\n", predecessor->show);
	}
	else {
		printf("没有前驱\n");
	}
	if (successor != NULL) {
		printf("后继：%c\n", successor->show);
	}
	else {
		printf("没有后继\n");
	}
}


//创建一颗树
BinaryTree* initBTree() {
	BTNode* a = createBTNode('A');
	BTNode* b = createBTNode('B');
	BTNode* c = createBTNode('C');
	BTNode* d = createBTNode('D');
	BTNode* e = createBTNode('E');
	BTNode* f = createBTNode('F');
	BTNode* g = createBTNode('G');
	BTNode* h = createBTNode('H');
	BTNode* k = createBTNode('K');

	BinaryTree* tree = createBTree(a);

	insertBTNode(tree, a, b, 1);
	insertBTNode(tree, a, e, 0);
	insertBTNode(tree, b, c, 0);
	insertBTNode(tree, c, d, 1);
	insertBTNode(tree, e, f, 0);
	insertBTNode(tree, f, g, 1);
	insertBTNode(tree, g, h, 1);
	insertBTNode(tree, g, k, 0);
	return  tree;
}

//int main() {
//	BinaryTree* tree = initBTree();
//
//	printf("\n中序遍历:\n");
//	inOrderBTree(tree);
//
//	BTNode* node = tree->root->right; // 选择一个节点
//	BTNode* predecessor = nextNodeF(node);
//	BTNode* successor = nextNodeB(node);
//
//	printf("\n给定节点：%c", node->show);
//	if (predecessor != NULL) {
//		printf("\n前驱：%c", predecessor->show);
//	}
//	else {
//		printf("\n没有前驱");
//	}
//	if (successor != NULL) {
//		printf("\n后继：%c", successor->show);
//	}
//	else {
//		printf("\n没有后继");
//	}
//
//	return 0;
//}

int main() {
	BinaryTree* tree = initBTree();

	printf("\n中序遍历:\n");
	inOrderBTree(tree);

	printPredecessorAndSuccessor(tree, 'C'); // 打印 'C' 的前驱和后继

	return 0;
}
