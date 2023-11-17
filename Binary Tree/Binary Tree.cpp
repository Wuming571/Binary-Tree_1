#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 定义二叉树节点结构体
typedef struct BTNode {
	char show;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

// 定义二叉树结构体
typedef struct {
	BTNode* root;
	int count;
}BinaryTree;

// 创建一个新的二叉树节点
BTNode* creatBTNode(char show) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}

// 初始化二叉树的根节点
void initBTreeRoot(BinaryTree* tree, BTNode* node) {
	tree->count = 1;
	tree->root = node;
}

// 创建一个新的二叉树
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

// 在二叉树中插入一个新的节点
void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newnode, int falg) {
	if (falg == 1) {
		parent->left = newnode;
	}
	if (falg == 0) {
		parent->right = newnode;
	}
	tree->count++;
}

// 访问二叉树节点
void visitBTNode(BTNode* node) {
	printf("%c", node->show);
}

// 定义队列节点结构体
typedef struct qnode {
	BTNode* data;
	struct qnode* next;
}qnode, * lqueue;

// 定义链式队列结构体
typedef struct linkqueue {
	lqueue front, rear;
}linkqueue;

// 初始化队列
linkqueue* initqueue() {
	linkqueue* q = (linkqueue*)malloc(sizeof(linkqueue));
	q->front = q->rear = (lqueue)malloc(sizeof(qnode));
	q->front->next = NULL;
	return q;
}

// 入队操作
void enqueue(linkqueue* q, BTNode* x) {
	lqueue s = (lqueue)malloc(sizeof(lqueue));
	s->data = x;
	s->next = NULL;
	q->rear->next = s;
	q->rear = s;
}

// 出队操作
BTNode* dequeue(linkqueue* q) {
	BTNode* x;
	if (q->front->next == NULL) {
		printf("队空\n");
		return NULL;
	}
	else {
		lqueue p = q->front->next;
		x = p->data;
		q->front->next = p->next;
		if (q->rear == p)
			q->front = q->rear;
		free(p);
		return x;
	}
}

// 检查队列是否为空
int empty(linkqueue* q) {
	if (q->front->next == NULL) {
		return 0; // 队列为空，返回0
	}
	else {
		return 1; // 队列非空，返回1
	}
}

// 层次遍历二叉树
void levelOrderBTree(BinaryTree* tree) {
	linkqueue* que = initqueue();
	enqueue(que, tree->root);
	while (empty(que) != 0) { // 当队列非空时，继续遍历
		BTNode* node = dequeue(que);
		visitBTNode(node);
		if (node->left != 0) { // 如果左子节点非空，则入队
			enqueue(que, node->left);
		}
		if (node->right != 0) { // 如果右子节点非空，则入队
			enqueue(que, node->right);
		}
	}
}

// 先序遍历二叉树
void perOrder(BTNode* node) {
	if (node != 0) { // 当节点非空时，继续遍历
		visitBTNode(node); // 访问当前节点
		perOrder(node->left); // 遍历左子树
		perOrder(node->right); // 遍历右子树
	}
}

void perOrderBTree(BinaryTree* tree) {
	if (tree->root != 0) { // 当根节点非空时，开始遍历
		perOrder(tree->root);
	}
}

// 中序遍历二叉树
void inOrder(BTNode* node) {
	if (node != 0) { // 当节点非空时，继续遍历
		inOrder(node->left); // 遍历左子树
		visitBTNode(node); // 访问当前节点
		inOrder(node->right); // 遍历右子树
	}
}

void inOrderBTree(BinaryTree* tree) {
	if (tree->root) { // 当根节点非空时，开始遍历
		inOrder(tree->root);
	}
}

// 后序遍历二叉树
void postOrder(BTNode* node) {
	if (node != 0) { // 当节点非空时，继续遍历
		postOrder(node->left); // 遍历左子树
		postOrder(node->right); // 遍历右子树
		visitBTNode(node); // 访问当前节点
	}
}

void postOrderBTree(BinaryTree* tree) {
	if (tree->root) { // 当根节点非空时，开始遍历
		postOrder(tree->root);
	}
}

// 初始化一棵具体的二叉树
BinaryTree* initBTree() {
	BTNode* a = creatBTNode('A');
	BTNode* b = creatBTNode('B');
	BTNode* c = creatBTNode('c');
	BTNode* d = creatBTNode('d');
	BTNode* e = creatBTNode('E');
	BTNode* f = creatBTNode('F');
	BTNode* g = creatBTNode('G');
	BTNode* h = creatBTNode('H');
	BTNode* k = creatBTNode('k');

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

int main() {
	BinaryTree* tree = initBTree();

	levelOrderBTree(tree);
	printf("层次遍历\n");

	printf("\n前序遍历:\n");
	perOrderBTree(tree);
	printf("\n中序遍历:\n");
	inOrderBTree(tree);
	printf("\n后序遍历:\n");
	postOrderBTree(tree);
	return 0;
}