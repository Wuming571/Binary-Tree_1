#include<stdio.h>
#include<stdlib.h>
#define MAX(a,b) ((a > b) ? (a) : (b))
typedef struct node {
	int data;//存储结点的值
	struct node* left;
	struct node* right;
	int height;//当前结点的深度
}avlnode, * avltree;

avlnode* creata_node(int key, avlnode* left, avlnode* right)
{
	avlnode* node = (avlnode*)malloc(sizeof(avlnode));
	//判断一下是否创建成功
	node->data = key;
	node->left = left;
	node->right = right;
	node->height = 0;
	return node;
}

//获取长度
int get_height(avlnode* node)
{

	if (node == NULL)
		return 0;
	else {
		return node->height;
	}
}
/*左孩子的左子树*/
avltree left_left_rotation(avltree tree)
{//传入的tree为子树根节点，同时也是失衡结点 
	//k就是我最终需
	avlnode* k = tree->left;
	tree->left = k->right;
	k->right = tree;
	//切记一点 所有旋转操作以后 需要调整树的高度 
	//这里是深度 一颗子树的深度 从这个结点的左右子树来判断他的深度
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(k->left), get_height(k->right)) + 1;
	return k;//此时k为根节点 
}
/*右孩子的右子树*/
avltree right_right_rotation(avltree tree)
{//传入的tree为子树根节点，同时也是失衡结点 
	avlnode* k = tree->right;
	tree->right = k->left;
	k->left = tree;
	//切记一点 所有旋转操作以后 需要调整树的高度
	//这里是深度 一颗子树的深度 从这个结点的左右子树来判断他的深度
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(k->left), get_height(k->right)) + 1;
	return k;//此时k为根节点 

}
/*左孩子得右子树的调整*/
avltree left_right_rotation(avltree tree)
{
	tree->left = right_right_rotation(tree->left);
	tree = left_left_rotation(tree);
	return tree;
}

/*右孩子的左子树的情况*/
avltree right_left_rotation(avltree tree)
{
	tree->right = left_left_rotation(tree->right);
	tree = right_right_rotation(tree);
	return tree;
}


avltree avltree_insertNode(avltree tree, int key)
{
	if (tree == NULL)
	{
		avlnode* node = creata_node(key, NULL, NULL);
		tree = node;
	}
	else if (key < tree->data)//往tree的左子树插入 
	{
		//递归寻找插入结点的位置
		tree->left = avltree_insertNode(tree->left, key);
		if (get_height(tree->left) - get_height(tree->right) == 2)
		{
			//在这里判断是LL还是LR
			if (key < tree->left->data)
			{
				tree = left_left_rotation(tree);
			}
			else
			{
				//LR旋转
				tree = left_right_rotation(tree);
			}
		}
	}
	else if (key > tree->data) //往tree的右子树插入 
	{
		tree->right = avltree_insertNode(tree->right, key);
		if (get_height(tree->right) - get_height(tree->left) == 2)
		{
			//RR
			if (key > tree->right->data)
			{
				tree = right_right_rotation(tree);
			}
			else
			{
				//RL
				tree = right_left_rotation(tree);
			}
		}
	}
	else
	{
		//报错，不允许插入相同的值
	}

	//重新调整二叉树的深度
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;

	return tree;

}

void in_order(avltree tree)
{//中序遍历输出 
	if (tree)
	{

		in_order(tree->left);
		printf("%d   ", tree->data);
		in_order(tree->right);
	}
}

int main()
{
	avltree tree = NULL;
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	for (int i = 0; i < 9; i++)
	{
		tree = avltree_insertNode(tree, a[i]);
	}


	in_order(tree);
	printf("\n");


}
