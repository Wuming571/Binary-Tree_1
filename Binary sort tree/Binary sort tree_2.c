#include<stdio.h>
#include<stdlib.h>
/*二叉排序树插入代码实现*/
/*数据结构*/
typedef struct SortTree {
	struct SortTree* left, * right;
	int key;//存放数据
}Node;
/*全局变量*/
Node* root = NULL;

/*初始化一个根节点*/
void Init(int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = key;
	root->left = NULL;
	root->right = NULL;
}

/*
二叉排序树的插入 永远是插入在叶子
要先找到应该在哪个结点的孩子进行插入
然后判断是这个结点的左孩子还是右孩子
*/
void insert(int key)
{
	Node* temp = root;//定义一个临时指针 方便移动
	Node* prev = NULL;//指向temp的前一个结点
	while (temp != NULL)
	{
		prev = temp;
		if (key < temp->key) {
			temp = temp->left;
		}
		else if (key > temp->key) {
			temp = temp->right;
		}

	}

	if (key < prev->key)
	{
		prev->left = (Node*)malloc(sizeof(Node));
		prev->left->key = key;
		prev->left->left = NULL;
		prev->left->right = NULL;
	}
	else
	{
		prev->right = (Node*)malloc(sizeof(Node));
		prev->right->key = key;
		prev->right->left = NULL;
		prev->right->right = NULL;
	}

}

void show(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->left != NULL)
	{
		show(root->left);
	}
	printf("%d", root->key);
	if (root->right != NULL)
	{
		show(root->right);
	}

}
/*情况一：node没有孩子，是叶子结点
	（1）node 不是根节点，直接把node删除，把node父亲对应的孩子指针置空
	（2）node是根节点，直接删除，把根指针置空
情况二：node只有一个孩子结点
	（1）node不是根节点，并且node只有一个孩子，就让这个孩子结点顶替node的位置，也就是node的parent的指向node的指针，要去指向该孩子
  （写代码时要注意区分左右）
	（2）node是根节点，让根指针直接指向node的唯一的孩子即可，
情况三：node有两个孩子。
法1：让node结点的左子树中的值最大的x结点来替换node结点的值，
转化为删除x：如果x是叶子结点转化为情况一，如果x不是叶子结点转化为情况二（x只有左孩子）   x是最node左子树靠右边的结点
*/
void delet(int k)
{
	Node* node = root;//去找k所在的结点node 
	Node* prev = NULL;//找node的父亲结点 
	while (node->key != k)
	{
		prev = node;
		if (k < node->key)
		{
			node = node->left;
		}
		else if (k > node->key)
		{
			node = node->right;
		}
	}
	if (node->left == NULL && node->right == NULL)
	{//情况一 node没有孩子 
		if (prev == NULL)//node的父亲为空 ，node为根节点 
		{
			root = NULL;
			free(node);
			node = NULL;
		}
		else
		{
			if (prev->left == node)
			{
				prev->left = NULL;
				free(node);
				node = NULL;
			}
			else
			{
				prev->right = NULL;
				free(node);
				node = NULL;
			}
		}

	}
	else if (node->left != NULL && node->right == NULL)
	{//情况二：node只有左孩子
		if (prev == NULL)
		{
			root = node->left;
			node->left = NULL;
			free(node);
			node = NULL;
		}
		else {

			if (prev->left == node)
			{
				prev->left = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}
			else
			{
				prev->right = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}

		}


	}
	else if (node->left == NULL && node->right != NULL)
	{//情况二：node只有右孩子
		if (prev == NULL)
		{
			root = node->right;
			node->right = NULL;
			free(node);
			node = NULL;
		}
		else {

			if (prev->left == node)
			{
				prev->left = node->right;
				node->right = NULL;
				free(node);
				node = NULL;
			}
			else
			{
				prev->right = node->right;
				node->right = NULL;
				free(node);
				node = NULL;
			}

		}


	}
	else {
		//情况三：node有两个孩子（左右孩子都有） 
		Node* x = node->left;
		Node* prex = node;//prex是x的父亲 
		while (x->right != NULL)
		{
			prex = x;
			x = x->right;
		}
		node->key = x->key;
		if (prex == node)
		{
			node->left = x->left;
			free(x);
			x = NULL;
		}
		else
		{
			prex->right = NULL;
			free(x);
			x = NULL;

		}
	}
}
int main()
{
	Init(3);
	insert(1);
	insert(2);
	insert(6);
	insert(5);
	show(root);
	printf("\n");
	delet(6);
	show(root);
}

