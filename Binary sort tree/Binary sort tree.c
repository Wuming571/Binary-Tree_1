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

int main()
{
	Init(3);
	insert(1);
	insert(2);
	insert(6);
	insert(5);
	show(root);

}

