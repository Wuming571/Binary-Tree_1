#include <stdio.h>
#include <stdlib.h>

typedef struct SortTree {
	struct SortTree* left, * right;
	int key;
}Node;

Node* root = NULL;

void Init(int key) {
	root = (Node*)malloc(sizeof(Node));
	root->key = key;
	root->left = root->right = NULL;
}

void insert(int key) {
	Node* prev = NULL;//指向寻找指针的父亲节点
	Node* temp = root;//寻找指针，临时指针

	while (temp != NULL) {
		prev = temp;
		
		if (key < temp->key) {
			temp=temp->left;
		}//这里必须是else if if会坚持（）内的条件，入伙temp->left的右孩子为空
		//temp的指针就为空，就会报错
		else if (key > temp->key) {
			temp=temp->right;
		}
	}

	if (key < prev->key) {
		prev->left = (Node*)malloc(sizeof(Node));
		prev->left->key = key;
		prev->left->left = prev->left->right = NULL;
	}
	if (key > prev->key) {
		prev->right = (Node*)malloc(sizeof(Node));
		prev->right->key = key;
		prev->right->left = prev->right->right = NULL;
	}

}

void show(Node* root) {
	Node* p = root;

	if (p == NULL) {

	}
	if (p->left != NULL) {
		show(p->left);
	}
	printf("%d", p->key);
	if (p->right != NULL) {
		show(p->right);
	}
}

void delet(int k) {//查找node
	Node* prve = NULL;
	Node* node = root;
	while (node->key != k) {
		prve = node;
		if (k < node->key) {
			node = node->left;
		}
		else if (k > node->key) {
			node = node->right;
		}
	}
	//第一种情况，叶子结点直接删
	if (node->left == NULL && node->right == NULL) {
		if (node == root) {//被删结点是根节点
			root = NULL;
			free(node);
			node = NULL;
		}
		else {
			if (prve->left == NULL) {
				prve->right = NULL;
				free(node);
				node = NULL;
			}
			else {
				prve->left = NULL;
				free(node);
				node = NULL;
			}
		}
	}
	//第二种情况，只有一个左孩子结点
	else if (node->left != NULL && node->right == NULL) {
		if (prve == NULL) {//node是根节点
			node = node->left;
			node->left = NULL;
			free(node);
			node = NULL;//?
		}
		else {
			if (prve->left != node) {//node是父亲结点的右孩子
				prve->right = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}
			else {//node是父亲结点的左孩子
				prve->left = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}
			/*if (prve->left == node) {
				prve->left = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}
			else {
				prve->right = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}*/

		}
	}

	//第三种情况，只有一个右孩子结点
	else if (node->left == NULL && node->right != NULL) {
		if (node == root) {//node是根节点
			root = node->right;
			free(node);
			node = NULL;//?
		}
		else {
			if (prve->left == NULL) {
				prve->right = node->right;
				node->right = NULL;
				free(node);
				node = NULL;
			}
			else {
				prve->left = node->right;
				node->right = NULL;
				free(node);
				node = NULL;
			}
		}
	}
	//第四种情况，有两个孩子结点，采用左子树最大值x覆盖node
	else {
		Node* x = node->left;//x来代表左子树最大值
		Node* prex = node;//x的父亲结点
		while (x->right != NULL) {//找到x（左子树的最大值）
			prex = x;
			x = x->right;
			}
		node->key = x->key;
		if (prex == node) {//要删除的x没有右孩子
			node->left = x->left;
			free(x);
			x = NULL;
		}
		else {//要删除的x是叶子结点
			prex->right = NULL;
			free(x);
			x = NULL;
		}
	}
}

int main() {
	Init(3);
	insert(1);
	insert(2);
	insert(6);
	insert(5);
	insert(0);
	show(root);
	printf("\n");
	delet(6);
	show(root);
	return 0;
}