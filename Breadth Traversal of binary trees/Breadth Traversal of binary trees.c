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

BTNode* creatBTNode(char* show) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}

void initBTreeRoot(BinaryTree* tree,BTNode* node) {
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

void insertBTNode(BinaryTree* tree, BTNode* parent, BTNode* newnode, int falg) {
	if (falg == 1) {
		parent->left = newnode;
	}
	if (falg == 0) {
		parent->right = newnode;
	}
	tree->count++;
}

void visitBTNode(BTNode* node) {
	printf("%c", node->show);
}

//队列链表
typedef struct qnode {
	BTNode* data;
	struct qnode* next;
}qnode,*lqueue;

typedef struct linkqueue {
	lqueue front, rear;
}linkqueue;

linkqueue* initqueue() {
	linkqueue* q = (linkqueue*)malloc(sizeof(linkqueue));
	q->front = q->rear = (lqueue)malloc(sizeof(qnode));
	q->front->next = NULL;
	return q;
}

void enqueue(linkqueue* q, BTNode* x) {
	lqueue s = (lqueue)malloc(sizeof(lqueue));
	s->data = x;
	s->next = NULL;
	q->rear->next = s;
	q->rear = s;
}

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
			q->front = q->rear = NULL;
		free(p);
		return x;
	}
}

int empty(linkqueue* q) {
	if (q->front->next==NULL) {
		return 0;
	}
	else {
		return 1;
	}
}
//层次遍历
void levelOrderBTree(BinaryTree* tree) {
	linkqueue* que = initqueue();
	enqueue(que, tree->root);
	while (empty(que)!=0) {
		BTNode* node = dequeue(que);
		visitBTNode(node);
		if (node->left != 0) {
			enqueue(que, node->left);
		}
		if (node->right != 0) {
			enqueue(que, node->right);
		}
	}
}

//先序遍历
void perOrder(BTNode* node) {
	if (node != 0) {
		visitBTNode(node);
		perOrder(node->left);
		perOrder(node->right);
	}
}

void perOrderBTree(BinaryTree* tree) {
	if (tree->root != 0) {
		perOrder(tree->root);
	}
}

//中序遍历
void inOrder(BTNode* node) {
	if (node != 0) {
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

//后序遍历
void postOrder(BTNode* node) {
	if (node != 0) {
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

BinaryTree* initBTree() {
	BTNode* a = creatBTNode('A');
	BTNode* b = creatBTNode('B');
	BTNode* c = creatBTNode('C');
	BTNode* d = creatBTNode('D');
	BTNode* e = creatBTNode('E');
	BTNode* f = creatBTNode('F');
	BTNode* g = creatBTNode('G');
	BTNode* h = creatBTNode('H');
	BTNode* k = creatBTNode('K');

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