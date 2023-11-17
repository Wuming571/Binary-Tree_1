#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b)((a>b)?a:b)

typedef struct node {
	struct node* left, * right;
	int data;
	int height;//�洢�ý�����������
}avlnode,*avltree;
//�������
avlnode* creata_node(int key, avlnode* left, avlnode* right) {
	avlnode* node = (avlnode*)malloc(sizeof(avlnode));
	node->data = key;
	node->left = left;
	node->right = right;
	node->height = 0;
	return node;
}
//�õ��������
int get_height(avlnode* node) {
	if (node == NULL)
		return 0;
	else
		return node->height;
}
//LL���ӵ�������ʧ�⣬����
avltree left_left_rotation(avltree tree) {
	avlnode* k = tree->left;
	tree->left = k->right;
	k->right = tree;//˳���ܱ�
	//���ĸ߶ȷ����˸ı䣬���¸ı��Ľ�����
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	//һ���ڵ�ĸ߶ȵ��������������������нϸߵ��Ǹ��ĸ߶ȼ�1
	return k;
}
//RR�Һ��ӵ�������ʧ�⣬����
avltree right_right_rotation(avltree tree) {
	avlnode* k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	k->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	//һ���ڵ�ĸ߶ȵ��������������������нϸߵ��Ǹ��ĸ߶ȼ�1
	return k;
}
//LR���ӵ�������ʧ�⣬������������tree������
avltree left_right_rotation(avltree tree) {
	avlnode* k = tree->left;
	k = right_right_rotation(k);
	tree = left_left_rotation(tree);
	return tree;
}
//RL�Һ��ӵ�������ʧ�⣬�Һ�����������tree������
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
	else if(key<tree->data){//������������
		//�ݹ�Ѱ�Ҳ���Ľ��λ��
		tree->left = avltree_insertNode(tree->left, key);
		//���ƽ�����ӵ���2��������ת����
		if (get_height(tree->left) - get_height(tree->right) == 2) {
			//������������һ������߸߶ȴ����ұ߸߶�
			//�ж���LL����LR
			if (key < tree->left->data) {//LL
				tree = left_left_rotation(tree);
			}
			else if (key > tree->left->data) {//LR
				tree = left_right_rotation(tree);
			}
		}
	}
	else if (key > tree->data) {//��tree�����������в���
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
	if (key < tree->data) {//Ҫɾ������������
		tree->left = avlnode_deleteNode(tree->left,key);
		//ɾ��֮��һ��Ҫ���ƽ������
		if (get_height(tree->right) - get_height(tree->left) == 2) {
			//ɾ���������������������������һ��������������ֻ����RR RL
			avlnode* tmp = tree->right;
			if (get_height(tmp->left) - get_height(tmp->right)>0) {
				//RL
				tree = right_left_rotation(tree);
			}
			else {
				//RR ����tree������������ȵ����
				tree = right_right_rotation(tree);
			}
		}
	}
	else if (key > tree->data) {//Ҫɾ������������
		tree->right = avlnode_deleteNode(tree->right, key);
		//ɾ������ƽ�����
		if (get_height(tree->left) - get_height(tree->right) == 2) {
			avlnode* tmp = tree->left;
			if (get_height(tmp->right) - get_height(tmp->left) > 0) {
				//LR
				tree = left_right_rotation(tree);
			}
			else {
				//LL ����tree������������ȵ����
				tree = left_left_rotation(tree);
			}
		}
	}
	else {//�ҵ�Ҫɾ���Ľ�㣬���ն����������ķ�ʽ����ɾ��
		if (tree->left && tree->right) {//�������ӵ����������������С�Ľ�������ڵ�
			avlnode* min_node = mininum_node(tree->right);
			tree->data = min_node->data;
			//����������С�Ľ�������ڵ㣬ת��Ϊɾ����������С�Ľ�������
			tree->right = avlnode_deleteNode(tree->right, min_node->data);
		}
		else {
			//ɾ��һ�����ӻ���û�к��ӽ��
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
	}//�����߶�
	if (tree) {
		tree->height = MAX(get_height(tree->left), get_height(tree->right)) + 1;
	}
	return tree;
}

void in_order(avltree tree)
{ // ����������
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
