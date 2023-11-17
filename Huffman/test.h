//用数组模拟树，标记清楚每个结点孩子及双亲结点的下标 
typedef struct {
	int weight;//权值
	int lChild, rChild;
	int parent;
}HuffmanNode,*HuffmanTree;

typedef char* HuffmanCode;//哈夫曼编码，用0 1来表示

static void selectNode(HuffmanTree tree, int n, int* s1, int* s2) {
	int min = 0;
	//找到两个最小的根节点
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0) {
			min = 1;
			break;
		}
	}
	//遍历全部结点
	for (int i = 1; i <= n; ++i) {//找到最小的根节点
		if (tree[i].parent == 0) {
			if (tree[i].weight < tree[min].weight) {
				min = i;
			}
		}
	}
	*s1 = min;//?
	for (int i = 1; i <= n; ++i) {//找到第二小的结点
		if (tree[i].parent == 0 && i != *s1) {
			min = i;
			break;
		}
	}
	//遍历全部结点
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
	//给定的叶子节点为n个，度为2的结点为n-1（总结点个数为2n-1）
	tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));
	//下标0的位置作为初始化的结点
	//初始化树中的所有结点
	for (int i = 1; i <= m; ++i) {
		tree[i].parent = tree[i].lChild = tree[i].rChild = 0;
		tree[i].weight = 0;
	}
	//给定的结点进行初始化权值
	for (int i = 1; i <= n; ++i) {
		tree[i].weight = w[i - 1];
	}
	//合并两个权值最小的结点
	int s1, s2;//两个权值最小的结点
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

//以树为基础构建编码，从叶子结点到根节点 逆向求每个叶子的编码
HuffmanCode* createHuffmanCode(HuffmanTree tree, int n) {
	//把每个编码临时存在temp数组中
	char* temp = (char*)malloc(sizeof(char) * n);//一维数组
	//分配n个编码的头指针
	HuffmanCode* codes = (HuffmanCode*)malloc(sizeof(HuffmanCode) * n);//此时code为一维数组
	memset(codes, 0, (sizeof(HuffmanCode) * n));

	int start;//最先放的位置
	int p;//i的双亲结点
	int pos;//i结点

	for (int i = 1; i <= n; ++i) {
		start = n - 1;//最多是一个深度为n的树
		temp = '\0';//首先将结束符放进去
		pos = i;//i结点
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
		my_strcpy(codes[i - 1], &temp[start]);//此时codes为二维数组 
	}
	free(temp);
	return codes;
}

