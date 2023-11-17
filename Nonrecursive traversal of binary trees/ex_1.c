#include <stdlib.h>
#include <stdio.h>
# include <string.h>
typedef struct BTNode { //二叉树结点     
	char show;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

typedef struct {//二叉树 
	BTNode* root;
	int count;//结点数目 
}BinaryTree;

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
void visitBTNode(BTNode* node) {
	if (node) {
		printf("%c ", node->show);
	}
}
//栈
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
//入栈
void pushArrayStack(listack s, BTNode* k) {
	sstack* p = (sstack*)malloc(sizeof(sstack));
	memset(p, 0, sizeof(sstack));
	p->data = k;
	p->next = s->next;
	s->next = p;
}

//出栈
BTNode* pop(listack s) {
	if (s->next == NULL) {
		printf("空栈");
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

//取栈顶值
BTNode* get(listack s) {
	if (s->next == NULL) {
		printf("空栈");
		return NULL;
	}
	else {
		BTNode* x;
		x = s->next->data;
		return x;
	}
}

//判断栈是否为空
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
//先序遍历
void perOrderBTree(BinaryTree* tree) {
	BTNode* node;
	if (tree->root) {
		ArrayStack* stack = initArrayStack();
		pushArrayStack(stack,tree->root);

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
//中序遍历
void inOrderBTree(BinaryTree* tree) {
	BTNode* node;
	if (tree->root) {
		ArrayStack* stack = initArrayStack();
		node = tree->root;
		while (node||isEmptyArrayStack(stack)) {
			if (node) {
				pushArrayStack(stack, node);
				node = node->left;
			}
			else {
				node=pop(stack);
				visitBTNode(node);
				node = node->right;
			}
		}

	}
}
//后序遍历（双栈）
void post1(BinaryTree* tree) {
	if (tree->root) {
		BTNode* node;
		ArrayStack* s1 = initArrayStack();
		ArrayStack* s2 = initArrayStack();
		pushArrayStack(s1, tree->root);
		while (isEmptyArrayStack(s1)) {
			node = get(s1);
			if (node) {
				pushArrayStack(s2, node);
				pop(s1);
				if (node->left) {
					pushArrayStack(s1, node->left);
				}
				if (node->right) {
					pushArrayStack(s1, node->right);
				}
				node = node->right;
			}
			else {
				pop(s1);
				node = get(s1);
			}
		}
		while (isEmptyArrayStack(s2)) {
			node=get(s2);
			pop(s2);
			visitBTNode(node);
		}
	}
}

//void post1(BinaryTree* tree) {
//	if (tree->root) {
//		ArrayStack* s1 = initArrayStack();
//		ArrayStack* s2 = initArrayStack();
//		BTNode* node;
//		pushArrayStack(s1, tree->root);
//		while (isEmptyArrayStack(s1)) {
//			node = get(s1);
//			pop(s1);
//			pushArrayStack(s2, node);
//			if (node->left) {
//				pushArrayStack(s1, node->left);
//			}
//			if (node->right) {
//				pushArrayStack(s1, node->right);
//			}
//		}
//		while (isEmptyArrayStack(s2)){
//			node = get(s2);
//			pop(s2);
//			visitBTNode(node);
//		}
//	}
//}

//后序遍历（单栈）
void post2(BinaryTree* tree) {
	if (tree->root) {
		ArrayStack* s = initArrayStack();
		BTNode* node=tree->root;
		BTNode* r=NULL;
		while (isEmptyArrayStack(s) || node) {
			if (node!=NULL) {
				pushArrayStack(s, node);
				node = node->left;
			}
			else {
				node = get(s);
				if (node->right && node->right!=r) {
					node=node->right;
				}
				else {
					pop(s);
					visitBTNode(node);
					r = node;
					node = NULL;//方便返回if(node!=NULL)
				}
			}
		}

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

int main() {
	BinaryTree* tree = initBTree();

	printf("\n前序遍历:\n");
	perOrderBTree(tree);
	printf("\n中序遍历:\n");
	inOrderBTree(tree);
	printf("\n后序遍历:\n");
	post1(tree);
	printf("\n后序遍历:\n");
	post2(tree);
	return 0;
}