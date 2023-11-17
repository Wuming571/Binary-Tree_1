#include <stdlib.h>
#include <stdio.h>
# include <string.h>
typedef struct BTNode { //���������     
	char show;
	struct BTNode* left;
	struct BTNode* right;
	int ltag;
	int rtag;
}BTNode;

typedef struct {//������ 
	BTNode* root;
	int count;//�����Ŀ 
}BinaryTree;
BTNode* pre = NULL;
//������� 
BTNode* createBTNode(char show) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}
//��ʼ��������� 
void initBTreeRoot(BinaryTree* tree, BTNode* node) {
	tree->count = 1;
	tree->root = node;
}
//������ 
BinaryTree* createBTree(BTNode* root) {
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (root) {//�ǿ� 
		initBTreeRoot(tree, root);
	}
	else {//���� 
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}

//������  �����в���newNode��㣬�ý���˫�׽��Ϊparent�� 
//flag==1�ý��Ϊ���ӣ� flag==0�ý��Ϊ�Һ��� 
void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newNode, int flag) {
	if (flag == 1) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	tree->count++;
}

//����һ�����
//���������� 
void visitBTNode(BTNode* node) {
	if (node)
	{
		printf("%c ", node->show);
	}

	if (node->left == NULL)
	{
		node->left = pre;
		node->ltag = 1;//ָ��ǰ������	
	}
	if (pre != NULL && pre->right == NULL)
	{
		pre->right = node;
		pre->rtag = 1;//ָ�������� 
	}
	pre = node; //

}
//������� 
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

//������� 
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

//������� 
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
//��ʼ��һ�þ������ 
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


//����������ĺ�̽ڵ�
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
//��ǰ���ڵ� 
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
	printf("\nǰ:\n");
	perOrderBTree(treeF);

	BinaryTree* treeM = initBTree();
	printf("\n��:\n");
	inOrderBTree(treeM);

	BinaryTree* treeB = initBTree();
	printf("\n��\n");
	postOrderBTree(treeB);


	return 0;
}

