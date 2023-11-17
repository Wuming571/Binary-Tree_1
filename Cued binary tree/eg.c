#include <stdlib.h>
#include <stdio.h>
# include <string.h>
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

//先序遍历 
void perOrder(BTNode* node) {
	if (node) {
		visitBTNode(node);
		if (node->ltag == 0)
		{
			perOrder(node->left);
		}
		if (node->rtag == 0)
		{
			perOrder(node->right);
		}

	}
}

void perOrderBTree(BinaryTree* tree) {
	if (tree->root) {
		perOrder(tree->root);
	}
}

//后序遍历 
void postOrder(BTNode* node) {
	if (node) {
		postOrder(node->left);
		postOrder(node->right);
		visitBTNode(node);
	}
}
void postOrderBTree(BinaryTree* tree) {
	if (tree->root) {
		postOrder(tree->root);
	}
}
//初始化一棵具体的树 
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
	return tree;
}


//找中序遍历的后继节点
BTNode* nextNodeM(BTNode* x)
{
	if (x->rtag == 1)
	{
		return x->right;

	}
	else
	{
		BTNode* p = x->right;
		while (p->ltag == 0)
		{
			p = p->left;
		}
		return p;

	}
}
//找前驱节点 
BTNode* nextNodeF(BTNode* x)
{
	if (x->ltag == 1)
	{
		return x->left;

	}
	else
	{
		BTNode* p = x->left;
		while (p->rtag == 0)
		{
			p = p->right;
		}
		return p;

	}
}


int main() {
	BinaryTree* treeF = initBTree();
	printf("\n前:\n");
	perOrderBTree(treeF);

	BinaryTree* treeM = initBTree();
	printf("\n中:\n");
	inOrderBTree(treeM);

	BinaryTree* treeB = initBTree();
	printf("\n后\n");
	postOrderBTree(treeB);


	return 0;
}

