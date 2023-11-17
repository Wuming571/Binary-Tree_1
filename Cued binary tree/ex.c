#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

//��������Һ�̽��
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

//���������ǰ�����
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

// ���Ҿ��и��� show ֵ�Ľڵ�
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

// ��ӡ���� show ֵ�Ľڵ��ǰ���ͺ��
void printPredecessorAndSuccessor(BinaryTree* tree, char show) {
	BTNode* node = findNode(tree->root, show);
	if (node == NULL) {
		printf("û���ҵ� show ֵΪ %c �Ľڵ�\n", show);
		return;
	}
	BTNode* predecessor = nextNodeF(node);
	BTNode* successor = nextNodeB(node);

	printf("�����ڵ㣺%c\n", node->show);
	if (predecessor != NULL) {
		printf("ǰ����%c\n", predecessor->show);
	}
	else {
		printf("û��ǰ��\n");
	}
	if (successor != NULL) {
		printf("��̣�%c\n", successor->show);
	}
	else {
		printf("û�к��\n");
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

//int main() {
//	BinaryTree* tree = initBTree();
//
//	printf("\n�������:\n");
//	inOrderBTree(tree);
//
//	BTNode* node = tree->root->right; // ѡ��һ���ڵ�
//	BTNode* predecessor = nextNodeF(node);
//	BTNode* successor = nextNodeB(node);
//
//	printf("\n�����ڵ㣺%c", node->show);
//	if (predecessor != NULL) {
//		printf("\nǰ����%c", predecessor->show);
//	}
//	else {
//		printf("\nû��ǰ��");
//	}
//	if (successor != NULL) {
//		printf("\n��̣�%c", successor->show);
//	}
//	else {
//		printf("\nû�к��");
//	}
//
//	return 0;
//}

int main() {
	BinaryTree* tree = initBTree();

	printf("\n�������:\n");
	inOrderBTree(tree);

	printPredecessorAndSuccessor(tree, 'C'); // ��ӡ 'C' ��ǰ���ͺ��

	return 0;
}
