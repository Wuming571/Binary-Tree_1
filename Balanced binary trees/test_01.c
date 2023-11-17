#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b)((a>b)?a:b)

typedef struct node {
	struct node* left, * right;
	int data;
	int height;//存储该结点子树的深度
}avlnode,*avltree;
//创建结点
avlnode* creata_node(int key, avlnode* left, avlnode* right) {
	avlnode* node = (avlnode*)malloc(sizeof(avlnode));
	node->data = key;
	node->left = left;
	node->right = right;
	node->height = 0;
	return node;
}
//得到树的深度
int get_height(avlnode* node) {
	if (node == NULL)
		return 0;
	else
		return node->height;
}
//LL左孩子的左子树失衡，右旋
avltree left_left_rotation(avltree tree) {
	avlnode* k = tree->left;
	tree->left = k->right;
	k->right = tree;//顺序不能变
	//树的高度发生了改变，更新改变后的结点深度
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	//一个节点的高度等于其左子树和右子树中较高的那个的高度加1
	return k;
}
//RR右孩子的右子树失衡，左旋
avltree right_right_rotation(avltree tree) {
	avlnode* k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	//一个节点的高度等于其左子树和右子树中较高的那个的高度加1
	return k;
}
//LR左孩子的右子树失衡，左孩子先左旋，tree再右旋
avltree left_right_rotation(avltree tree) {
	avlnode* k = tree->left;
	k = right_right_rotation(k);
	tree = left_left_rotation(tree);
	return tree;
}
//RL右孩子的左子树失衡，右孩子先右旋，tree再左旋
avltree right_left_rotation(avltree tree) {
	avlnode* k = tree->right;
	k = left_left_rotation(k);
	tree = right_right_rotation(tree);
	return tree;
}

avltree avltree_insertNode(avltree tree, int key) {
	if (tree == NULL) {
		avlnode* node = creata_node(key, NULL, NULL);
		tree = node;
	}
	else if(key<tree->data){//往左子树插入
		//递归寻找插入的结点位置
		tree->left = avltree_insertNode(tree->left, key);
		//如果平衡因子等于2，进行旋转操作
		if (get_height(tree->left) - get_height(tree->right) == 2) {
			//往左子树插入一定是左边高度大于右边高度
			//判断是LL还是LR
			if (key < tree->left->data) {//LL
				tree = left_left_rotation(tree);
			}
			else if (key > tree->left->data) {//LR
				tree = left_right_rotation(tree);
			}
		}
	}
	else if (key > tree->data) {//往tree的右子树进行插入
		tree->right = avltree_insertNode(tree->right, key);
		if (get_height(tree->right) - get_height(tree->left) == 2) {
			if (key > tree->right->data) {//RR
				tree = right_right_rotation(tree);
			}
			else if (key < tree->right->data) {//RL
				tree = right_left_rotation(tree);
			}
		}
	}
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	return tree;
}

avlnode* mininum_node(avltree tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->left) {
		tree = tree->left;
	}
	return tree;
}

avltree avlnode_deleteNode(avltree tree, int key) {
	if (tree == NULL) {
		return tree;
	}
	if (key < tree->data) {//要删除的是左子树
		tree->left = avlnode_deleteNode(tree->left,key);
		//删完之后一定要检查平衡因子
		if (get_height(tree->right) - get_height(tree->left) == 2) {
			//删除的在左子树，所以右子树深度一定大于左子树，只能是RR RL
			avlnode* tmp = tree->right;
			if (get_height(tmp->left) - get_height(tmp->right)>0) {
				//RL
				tree = right_left_rotation(tree);
			}
			else {
				//RR 包括tree右子树两边相等的情况
				tree = right_right_rotation(tree);
			}
		}
	}
	else if (key > tree->data) {//要删除的是右子树
		tree->right = avlnode_deleteNode(tree->right, key);
		//删除完检查平衡操作
		if (get_height(tree->left) - get_height(tree->right) == 2) {
			avlnode* tmp = tree->left;
			if (get_height(tmp->right) - get_height(tmp->left) > 0) {
				//LR
				tree = left_right_rotation(tree);
			}
			else {
				//LL 包括tree左子树两边相等的情况
				tree = left_left_rotation(tree);
			}
		}
	}
	else {//找到要删除的结点，按照二叉排序树的方式进行删除
		if (tree->left && tree->right) {//两个孩子的情况，让右子树最小的结点代替根节点
			avlnode* min_node = mininum_node(tree->right);
			tree->data = min_node->data;
			//让右子树最小的结点代替根节点，转换为删除右子树最小的结点的问题
			tree->right = avlnode_deleteNode(tree->right, min_node->data);
		}
		else {
			//删除一个孩子或者没有孩子结点
			avlnode* n = tree;
			if (tree->left) {
				tree = tree->left;
			}
			else {
				tree = tree->right;
			}
			free(n);
			n = NULL;
			return tree;
		}
	}//调整高度
	if (tree) {
		tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	}
	return tree;
}

void in_order(avltree tree)
{ // 中序遍历输出
	if (tree)
	{
		in_order(tree->left);
		printf("%d", tree->data);
		in_order(tree->right);
	}
}

//void in_order(avltree tree) {
//	if (tree) {
//		if (tree->left) {
//			tree = tree->left;
//			in_order(tree);
//		}
//		printf("%d", tree->data);
//		if (tree->right) {
//			tree = tree->right;
//			in_order(tree);
//		}
//	}
//}

int main() {
	avltree tree = NULL;
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	// int length = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < 9; i++)
	{
		tree = avltree_insertNode(tree, a[i]);
	}
	printf("\n");
	in_order(tree);
	printf("\n");
	tree = avlnode_deleteNode(tree, 7);
	tree = avlnode_deleteNode(tree, 2);
	tree = avlnode_deleteNode(tree, 4);
	printf("\n");
	in_order(tree);
}
