#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct BTNode
{ // ���������
	char show;
	struct BTNode* left;
	struct BTNode* right;
} BTNode;

typedef struct
{ // ������
	BTNode* root;
	int count; // �����Ŀ
} BinaryTree;

// �������
BTNode* createBTNode(char* show)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}
// ��ʼ���������
void initBTreeRoot(BinaryTree* tree, BTNode* node)
{
	tree->count = 1;
	tree->root = node;
}
// ������
BinaryTree* createBTree(BTNode* root)
{
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (root)
	{ // �ǿ�
		initBTreeRoot(tree, root);
	}
	else
	{ // ����
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}

// ������  �����в���newNode��㣬�ý���˫�׽��Ϊparent��
// flag==1�ý��Ϊ���ӣ� flag==0�ý��Ϊ�Һ���
void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newNode, int flag){
	if (flag == 1)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}
	tree->count++;
}

// ����һ�����
void visitBTNode(BTNode* node)
{
	if (node)
	{
		printf("%c ", node->show);
	}
}
// �������м����������
/// ��ʽ����//
typedef struct qnode
{						// ��ʽ���н��
	BTNode* data;		// ����Ԫ�������еĽ��
	struct qnode* next; // ָ����һ������ָ��
} qnode, * lqueue;
typedef struct linkqueue
{						// ��ʽ����---��ѡ����д�ṹ�壬ֱ�Ӷ����ͷ��βָ��Ҳ��
	lqueue front, rear; // ��ͷ��βָ��,����ָ��������ͷ���
} linkqueue;
// ��ʼ��
linkqueue* initqueue(){
	linkqueue* q = (linkqueue*)malloc(sizeof(linkqueue));
	q->front = q->rear = (lqueue)malloc(sizeof(qnode));
	if (q->front == NULL){
		printf("����ʧ��\n");
	}
	else
	{
		q->front->next = NULL;
	}
	return q;
}
// ���
void enqueue(linkqueue* q, BTNode* x){
	lqueue s = (lqueue)malloc(sizeof(qnode));
	s->data = x;
	s->next = NULL; // �½ڵ���뵽��β
	q->rear->next = s;
	q->rear = s;
}
// ���ӣ�����ָ��������ͷ��� ��ɾ�����Ƕ���ָ�����һ������front->next
BTNode* dequeue(linkqueue* q)
{
	BTNode* x; // �������Ԫ��
	// ���пգ����ղ��ܳ�
	if (q->front->next == NULL){
		printf("��\n"); // �ӿգ�����
	}
	else
	{
		lqueue p = q->front->next;
		x = p->data;
		q->front->next = p->next;
		// ��ԭ����ֻ��һ������ˣ���ɾ���߿գ���Ҫ����βָ��
		if (q->rear == p)
			q->rear = q->front;
		free(p);
		return x;
	}
}
int empty(linkqueue* q)
{
	if (q->front->next == NULL)
	{
		return 0; // �ӿ�
	}
	else
		return 1; // �ǿ�
}
// ��������
void levelOrderBTree(BinaryTree* tree)
{
	linkqueue* que = initqueue();
	enqueue(que, tree->root); // ����������

	while (empty(que) == 1){

		BTNode* node = dequeue(que); // ȡ���׽�㣬����
		visitBTNode(node);			 // ���ʸýڵ�
		if (node->left != NULL){
			enqueue(que, node->left); // �ýڵ��������
		}
		if (node->right != NULL){

			enqueue(que, node->right); // �ýڵ��������
		}
	}
}

// �������
void perOrder(BTNode* node){
	if (node){
		visitBTNode(node);
		perOrder(node->left);
		perOrder(node->right);
	}
}

void perOrderBTree(BinaryTree* tree){
	if (tree->root){
		perOrder(tree->root);
	}
}
// �������
void inOrder(BTNode* node){
	if (node){
		inOrder(node->left);
		visitBTNode(node);
		inOrder(node->right);
	}
}
void inOrderBTree(BinaryTree* tree){
	if (tree->root){
		inOrder(tree->root);
	}
}
// �������
void postOrder(BTNode* node){
	if (node)
{
		postOrder(node->left);
		postOrder(node->right);
		visitBTNode(node);
	}
}
void postOrderBTree(BinaryTree* tree){
	if (tree->root)
	{
		postOrder(tree->root);
	}
}
// ��ʼ��һ�þ������
BinaryTree* initBTree(){
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
int main(){
	BinaryTree* tree = initBTree();
	levelOrderBTree(tree);
	printf("\n");

	printf("\nǰ:\n");
	perOrderBTree(tree);
	printf("\n��:\n");
	inOrderBTree(tree);
	printf("\n��\n");
	postOrderBTree(tree);

	return 0;
}
