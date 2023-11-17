#include <stdlib.h>
#include <stdio.h>
# include <string.h>
typedef struct BTNode { //���������     
	char show;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

typedef struct {//������ 
	BTNode* root;
	int count;//�����Ŀ 
}BinaryTree;

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
	memset(tree, 0, sizeof(BinaryTree));
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
void visitBTNode(BTNode* node) {
	if (node) {
		printf("%c ", node->show);
	}
}

//ջ
typedef struct listackNode {
	BTNode* data;
	struct listackNode* next;
}sstack, * listack, ArrayStack;

listack initArrayStack() {
	listack s = (listack)malloc(sizeof(sstack));
	memset(s, 0, sizeof(sstack));
	s->data = 0;
	return s;
}
//��ջ
void pushArrayStack(listack s, BTNode* k) {
	sstack* p = (sstack*)malloc(sizeof(sstack));
	//memset(p, 0, sizeof(sstack));
	p->data = k;
	p->next = s->next;
	s->next = p;
}


//��ջ
BTNode* pop(listack s) {
	if (s->next == NULL) {
		printf("��ջ");
		return NULL;
	}
	else {
		sstack* p = s->next;
		BTNode* data = p->data;
		s->next = p->next;
		free(p);
		return data;
	}
}

//ȡջ��ֵ
BTNode* get(listack s) {
	if (s->next == NULL) {
		printf("��ջ");
		return NULL;
	}
	else {
		BTNode* x;
		x = s->next->data;
		return x;
	}
}

//�ж�ջ�Ƿ�Ϊ��
int isEmptyArrayStack(ArrayStack* s) {
	if (s->next == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

void releaseArrayStack(ArrayStack* s) {

	free(s);
}

//�������
void perOrderBTree(BinaryTree* tree) {
	BTNode* node;
	if (tree->root) {
		ArrayStack* stack = initArrayStack();
		pushArrayStack(stack, tree->root);

		while (isEmptyArrayStack(stack)==1) {
			node = get(stack);
			pop(stack);
			visitBTNode(node);
			if (node->right) {
				pushArrayStack(stack, node->right);
			}
			if (node->left) {
				pushArrayStack(stack, node->left);
			}
		}
		releaseArrayStack(stack);
	}
}

//����һ����
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

int main() {
	BinaryTree* tree = initBTree();

	printf("\nǰ�����:\n");
	perOrderBTree(tree);
	//printf("\n�������:\n");
	//inOrderBTree(tree);
	//printf("\n�������:\n");
	//postOrderBTree(tree);
	return 0;
}