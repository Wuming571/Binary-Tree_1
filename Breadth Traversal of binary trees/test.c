#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct BTNode
{ // 二叉树结点
	char show;
	struct BTNode* left;
	struct BTNode* right;
} BTNode;

typedef struct
{ // 二叉树
	BTNode* root;
	int count; // 结点数目
} BinaryTree;

// 创建结点
BTNode* createBTNode(char* show)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}
// 初始化树根结点
void initBTreeRoot(BinaryTree* tree, BTNode* node)
{
	tree->count = 1;
	tree->root = node;
}
// 创建树
BinaryTree* createBTree(BTNode* root)
{
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (root)
	{ // 非空
		initBTreeRoot(tree, root);
	}
	else
	{ // 空树
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}

// 插入结点  在树中插入newNode结点，该结点的双亲结点为parent，
// flag==1该结点为左孩子， flag==0该结点为右孩子
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

// 访问一个结点
void visitBTNode(BTNode* node)
{
	if (node)
	{
		printf("%c ", node->show);
	}
}
// 声明队列及其操作函数
/// 链式队列//
typedef struct qnode
{						// 链式队列结点
	BTNode* data;		// 队列元素是树中的结点
	struct qnode* next; // 指向下一个结点的指针
} qnode, * lqueue;
typedef struct linkqueue
{						// 链式队列---可选，不写结构体，直接定义对头队尾指针也可
	lqueue front, rear; // 对头队尾指针,队首指针是链表头结点
} linkqueue;
// 初始化
linkqueue* initqueue(){
	linkqueue* q = (linkqueue*)malloc(sizeof(linkqueue));
	q->front = q->rear = (lqueue)malloc(sizeof(qnode));
	if (q->front == NULL){
		printf("分配失败\n");
	}
	else
	{
		q->front->next = NULL;
	}
	return q;
}
// 入队
void enqueue(linkqueue* q, BTNode* x){
	lqueue s = (lqueue)malloc(sizeof(qnode));
	s->data = x;
	s->next = NULL; // 新节点插入到链尾
	q->rear->next = s;
	q->rear = s;
}
// 出队，队首指针是链表头结点 ，删除的是队首指针的下一个，即front->next
BTNode* dequeue(linkqueue* q)
{
	BTNode* x; // 保存出队元素
	// 先判空，不空才能出
	if (q->front->next == NULL){
		printf("空\n"); // 队空，报错
	}
	else
	{
		lqueue p = q->front->next;
		x = p->data;
		q->front->next = p->next;
		// 若原队列只有一个结点了，则删除边空，需要处理尾指针
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
		return 0; // 队空
	}
	else
		return 1; // 非空
}
// 。。。。
void levelOrderBTree(BinaryTree* tree)
{
	linkqueue* que = initqueue();
	enqueue(que, tree->root); // 树根结点入队

	while (empty(que) == 1){

		BTNode* node = dequeue(que); // 取队首结点，出队
		visitBTNode(node);			 // 访问该节点
		if (node->left != NULL){
			enqueue(que, node->left); // 该节点左孩子入队
		}
		if (node->right != NULL){

			enqueue(que, node->right); // 该节点左孩子入队
		}
	}
}

// 先序遍历
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
// 中序遍历
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
// 后序遍历
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
// 初始化一棵具体的树
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

	printf("\n前:\n");
	perOrderBTree(tree);
	printf("\n中:\n");
	inOrderBTree(tree);
	printf("\n后\n");
	postOrderBTree(tree);

	return 0;
}
