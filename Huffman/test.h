//������ģ������������ÿ����㺢�Ӽ�˫�׽����±� 
typedef struct {
	int weight;//Ȩֵ
	int lChild, rChild;
	int parent;
}HuffmanNode,*HuffmanTree;

typedef char* HuffmanCode;//���������룬��0 1����ʾ

static void selectNode(HuffmanTree tree, int n, int* s1, int* s2) {
	int min = 0;
	//�ҵ�������С�ĸ��ڵ�
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0) {
			min = 1;
			break;
		}
	}
	//����ȫ�����
	for (int i = 1; i <= n; ++i) {//�ҵ���С�ĸ��ڵ�
		if (tree[i].parent == 0) {
			if (tree[i].weight < tree[min].weight) {
				min = i;
			}
		}
	}
	*s1 = min;//?
	for (int i = 1; i <= n; ++i) {//�ҵ��ڶ�С�Ľ��
		if (tree[i].parent == 0 && i != *s1) {
			min = i;
			break;
		}
	}
	//����ȫ�����
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0 && i != *s1) {
			if (tree[i].weight < tree[min].weight) {
				min = i;
			}
		}
	}
	*s2 = min;
}

HuffmanTree createHuffmanTree(const int* w, int n) {
	HuffmanTree tree;
	int m = 2 * n - 1;
	//������Ҷ�ӽڵ�Ϊn������Ϊ2�Ľ��Ϊn-1���ܽ�����Ϊ2n-1��
	tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));
	//�±�0��λ����Ϊ��ʼ���Ľ��
	//��ʼ�����е����н��
	for (int i = 1; i <= m; ++i) {
		tree[i].parent = tree[i].lChild = tree[i].rChild = 0;
		tree[i].weight = 0;
	}
	//�����Ľ����г�ʼ��Ȩֵ
	for (int i = 1; i <= n; ++i) {
		tree[i].weight = w[i - 1];
	}
	//�ϲ�����Ȩֵ��С�Ľ��
	int s1, s2;//����Ȩֵ��С�Ľ��
	for (int i = n + 1; i <= m; ++i) {
		selectNode(tree, i - 1, &s1, &s2);
		tree[s1].parent = tree[s2].parent = i;
		tree[i].lChild = s1;
		tree[i].rChild = s2;
		tree[i].weight = tree[s1].weight + tree[s2].weight;
	}
	return tree;
}

void my_strcpy(char* dest, char* target)
{

	while (*target != '\0')
	{
		*dest = *target;
		dest++;
		target++;
	}*dest = *target;

}

//����Ϊ�����������룬��Ҷ�ӽ�㵽���ڵ� ������ÿ��Ҷ�ӵı���
HuffmanCode* createHuffmanCode(HuffmanTree tree, int n) {
	//��ÿ��������ʱ����temp������
	char* temp = (char*)malloc(sizeof(char) * n);//һά����
	//����n�������ͷָ��
	HuffmanCode* codes = (HuffmanCode*)malloc(sizeof(HuffmanCode) * n);//��ʱcodeΪһά����
	memset(codes, 0, (sizeof(HuffmanCode) * n));

	int start;//���ȷŵ�λ��
	int p;//i��˫�׽��
	int pos;//i���

	for (int i = 1; i <= n; ++i) {
		start = n - 1;//�����һ�����Ϊn����
		temp = '\0';//���Ƚ��������Ž�ȥ
		pos = i;//i���
		p = tree[i].parent;
		while (p) {
			--start;
			printf("1");
			temp[start] = ((tree[p].lChild == pos) ? '0' : '1');
			pos = p;
			p = tree[p].parent;
		}
		codes[i - 1] = (HuffmanCode)malloc(sizeof(char) * (n - start));
		//strcpy_s(codes[i - 1],sizeof(HuffmanCode)*n, &temp[start]);
		my_strcpy(codes[i - 1], &temp[start]);//��ʱcodesΪ��ά���� 
	}
	free(temp);
	return codes;
}

