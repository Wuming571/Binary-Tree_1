#include<stdio.h>
#include<stdlib.h>
/*�����������������ʵ��*/
/*���ݽṹ*/
typedef struct SortTree {
	struct SortTree* left, * right;
	int key;//�������
}Node;
/*ȫ�ֱ���*/
Node* root = NULL;

/*��ʼ��һ�����ڵ�*/
void Init(int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = key;
	root->left = NULL;
	root->right = NULL;
}

/*
�����������Ĳ��� ��Զ�ǲ�����Ҷ��
Ҫ���ҵ�Ӧ�����ĸ����ĺ��ӽ��в���
Ȼ���ж�������������ӻ����Һ���
*/
void insert(int key)
{
	Node* temp = root;//����һ����ʱָ�� �����ƶ�
	Node* prev = NULL;//ָ��temp��ǰһ�����
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
/*���һ��nodeû�к��ӣ���Ҷ�ӽ��
	��1��node ���Ǹ��ڵ㣬ֱ�Ӱ�nodeɾ������node���׶�Ӧ�ĺ���ָ���ÿ�
	��2��node�Ǹ��ڵ㣬ֱ��ɾ�����Ѹ�ָ���ÿ�
�������nodeֻ��һ�����ӽ��
	��1��node���Ǹ��ڵ㣬����nodeֻ��һ�����ӣ�����������ӽ�㶥��node��λ�ã�Ҳ����node��parent��ָ��node��ָ�룬Ҫȥָ��ú���
  ��д����ʱҪע���������ң�
	��2��node�Ǹ��ڵ㣬�ø�ָ��ֱ��ָ��node��Ψһ�ĺ��Ӽ��ɣ�
�������node���������ӡ�
��1����node�����������е�ֵ����x������滻node����ֵ��
ת��Ϊɾ��x�����x��Ҷ�ӽ��ת��Ϊ���һ�����x����Ҷ�ӽ��ת��Ϊ�������xֻ�����ӣ�   x����node���������ұߵĽ��
*/
void delet(int k)
{
	Node* node = root;//ȥ��k���ڵĽ��node 
	Node* prev = NULL;//��node�ĸ��׽�� 
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
	{//���һ nodeû�к��� 
		if (prev == NULL)//node�ĸ���Ϊ�� ��nodeΪ���ڵ� 
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
	{//�������nodeֻ������
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
	{//�������nodeֻ���Һ���
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
		//�������node���������ӣ����Һ��Ӷ��У� 
		Node* x = node->left;
		Node* prex = node;//prex��x�ĸ��� 
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

