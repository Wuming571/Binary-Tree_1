#include <stdlib.h>
#include <stdio.h>
# include <string.h>
typedef struct BTNode { //二叉树结点     
	char show;         
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

typedef struct {//二叉树 
	BTNode *root;
	int count;//结点数目 
}BinaryTree;

//创建结点 
BTNode *createBTNode(char show) {
	BTNode *node = (BTNode *) malloc(sizeof(BTNode));
	memset(node, 0, sizeof(BTNode));
	node->show = show;
	return node;
}
//初始化树根结点 
void initBTreeRoot(BinaryTree *tree, BTNode *node) {
	tree->count = 1;
	tree->root = node;
}
//创建树 
BinaryTree *createBTree(BTNode *root) {
	BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
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
void insertBTNode(BinaryTree *tree, BTNode *parent, BTNode *newNode, int flag) {
	if (flag == 1) {
		parent->left = newNode;
	} else {
		parent->right = newNode;
	}
	tree->count++;
}

//访问一个结点
void visitBTNode(BTNode *node) {
	if (node) {
		printf("%c ", node->show);
	}
}
//————————————————————————————————————————————————————————————
//栈
typedef struct ArrayStack {
	BTNode** array;
	int size;
	int top;
} ArrayStack;

// 初始化栈
ArrayStack* initArrayStack() {
	ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
	stack->array = (BTNode**)malloc(sizeof(BTNode*) * 100);  // 假设栈的最大容量为100
	stack->size = 100;
	stack->top = -1;
	return stack;
}

// 入栈
void push(ArrayStack* stack, BTNode* node) {
	if (stack->top >= stack->size - 1) {
		// 栈满了，需要扩容
		stack->size *= 2;
		stack->array = (BTNode**)realloc(stack->array, sizeof(BTNode*) * stack->size);
	}
	stack->array[++stack->top] = node;
}

// 检查栈是否为空
int empty(ArrayStack* stack) {
	return stack->top == -1;
}

// 获取栈顶元素
BTNode* get(ArrayStack* stack) {
	if (empty(stack)) {
		return NULL;  // 栈为空，返回NULL
	}
	return stack->array[stack->top];
}

// 出栈
void pop(ArrayStack* stack) {
	if (!empty(stack)) {
		stack->top--;
	}
}

// 释放栈
void releaseArrayStack(ArrayStack* stack) {
	free(stack->array);
	free(stack);
}


//先 
void perOrderBTree(BinaryTree *tree) {
	BTNode *node;
	if (tree->root) {
		ArrayStack *stack = initArrayStack();
		push(stack, tree->root);
		        
		while (!empty(stack)) {
			node=get(stack); 
			pop(stack);
			visitBTNode(node);
			if (node->right) {
				push(stack, node->right);
			}
			if (node->left) {
				push(stack, node->left);
			}
		}
		releaseArrayStack(stack);
	}
}
//后 -双栈实现 
void postOrderBTree(BinaryTree *tree) {
	if (tree->root) {
		ArrayStack *stack1 = initArrayStack();
		ArrayStack *stack2 = initArrayStack();
		BTNode *node;
		push(stack1, tree->root);
		while (!empty(stack1)) {
			node=get(stack1); 
				pop(stack1);
			push(stack2, node);
			if (node->left) {
				push(stack1, node->left);
			}
			if (node->right) {
				push(stack1, node->right);
			}
		}
		while (!empty(stack2))
		{
			node=get(stack2); 
				pop(stack2);
			visitBTNode(node);
		}
		//releaseArrayStack(stack1);
		//releaseArrayStack(stack2);
	}
}
////后 -单栈实现 
void postOrderBTree2(BinaryTree *tree) {
	ArrayStack *stack = initArrayStack();

	BTNode *node=tree->root;
	BTNode *r=NULL;//访问过的前一个结点 
	while(node||empty(stack)==0)
	{
		if(node!=NULL)//非空就一直入栈，一直往左走，找到最左边结点 
		{
			push(stack,node);
			node=node->left;
		}
		else
		{
			node=get(stack); 	
			if(node->right&&node->right!=r)//右子树存在 且木有被访问过。先访问右子树 
			{
				node=node->right; 
			}
			else//否则，访问该结点 
			{
				pop(stack);
				visitBTNode(node);
				r=node;//node成为刚访问过的结点
				node=NULL;//以node为根的子树访问完成，赋空值，方便回到node的父节点 
			}	
		}	
	}


}


//中 
void inOrderBTree(BinaryTree *tree) {
	if (tree->root) {
		ArrayStack *stack = initArrayStack();
		BTNode *node = tree->root;
		while (!empty(stack) || node) {
			if (node) {
				push(stack, node);
				node = node->left;
			} else {
				//popArrayStack(stack, (void **)&node);
				node=get(stack); 
				pop(stack);
				visitBTNode(node);
				node = node->right;
			}
		}
		releaseArrayStack(stack);
	}
}

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
	postOrderBTree(tree);
	return 0;
}