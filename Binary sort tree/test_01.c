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
	Node* prev = NULL;//ָ��Ѱ��ָ��ĸ��׽ڵ�
	Node* temp = root;//Ѱ��ָ�룬��ʱָ��

	while (temp != NULL) {
		prev = temp;
		
		if (key < temp->key) {
			temp=temp->left;
		}//���������else if if���֣����ڵ����������temp->left���Һ���Ϊ��
		//temp��ָ���Ϊ�գ��ͻᱨ��
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

void delet(int k) {//����node
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
	//��һ�������Ҷ�ӽ��ֱ��ɾ
	if (node->left == NULL && node->right == NULL) {
		if (node == root) {//��ɾ����Ǹ��ڵ�
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
	//�ڶ��������ֻ��һ�����ӽ��
	else if (node->left != NULL && node->right == NULL) {
		if (prve == NULL) {//node�Ǹ��ڵ�
			node = node->left;
			node->left = NULL;
			free(node);
			node = NULL;//?
		}
		else {
			if (prve->left != node) {//node�Ǹ��׽����Һ���
				prve->right = node->left;
				node->left = NULL;
				free(node);
				node = NULL;
			}
			else {//node�Ǹ��׽�������
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

	//�����������ֻ��һ���Һ��ӽ��
	else if (node->left == NULL && node->right != NULL) {
		if (node == root) {//node�Ǹ��ڵ�
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
	//��������������������ӽ�㣬�������������ֵx����node
	else {
		Node* x = node->left;//x���������������ֵ
		Node* prex = node;//x�ĸ��׽��
		while (x->right != NULL) {//�ҵ�x�������������ֵ��
			prex = x;
			x = x->right;
			}
		node->key = x->key;
		if (prex == node) {//Ҫɾ����xû���Һ���
			node->left = x->left;
			free(x);
			x = NULL;
		}
		else {//Ҫɾ����x��Ҷ�ӽ��
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