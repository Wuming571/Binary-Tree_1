#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//用数组模拟树，标记清楚每个结点孩子及双亲结点的下标 
typedef struct
{
	int weight;//权值				
	int lChild, rChild;
	int parent;
}HuffmanNode, * HuffmanTree;

typedef char* HuffmanCode;//编码：0/1字符表示

static void selectNode(HuffmanTree tree, int n, int* s1, int* s2)
{

	int min = 0;
	//找两个根节点 
	for (int i = 1; i <= n; ++i)
	{
		//先找没双亲结点的那个
		if (tree[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	//遍历全部的结点
	for (int i = 1; i <= n; ++i)
	{
		//先找最小的根节点 
		if (tree[i].parent == 0)
		{
			if (tree[i].weight < tree[min].weight)
			{
				min = i;
			}
		}
	}

	*s1 = min;
	//找第二小的根节点 
	for (int i = 1; i <= n; ++i)
	{
		if (tree[i].parent == 0 && i != *s1)
		{
			min = i;
			break;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (tree[i].parent == 0 && i != *s1)
		{
			if (tree[i].weight < tree[min].weight)
			{
				min = i;
			}
		}
	}
	*s2 = min;
}

HuffmanTree createHuffmanTree(const int* w, int n)
{
	HuffmanTree tree;
	int m = 2 * n - 1;
	//叶子结点n个，木有度为1的结点，度为2的结点n-1(规律：n0=n2+1) 
	tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));//下标0位置不用，多开一个内存 
	//初始化树中结点 
	for (int i = 1; i <= m; ++i)
	{
		tree[i].parent = tree[i].lChild = tree[i].rChild = 0;
		tree[i].weight = 0;
	}

	for (int i = 1; i <= n; ++i)
	{
		tree[i].weight = w[i - 1];//权值 
	}

	int s1, s2;
	//建树 
	for (int i = n + 1; i <= m; ++i)
	{
		selectNode(tree, i - 1, &s1, &s2);//指针传递 找最小的两个根节点，则第i个结点是他俩的父亲 
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

//以树为基础构建编码 从叶子结点到根节点 逆向求每个叶子的编码
HuffmanCode* createHuffmanCode(HuffmanTree tree, int n)
{
	//具体的编码的工作空间--把编码放temp数组中 
	char* temp = (char*)malloc(sizeof(char) * n);//一维数组 
	//分配 n个编码的头指针
	HuffmanCode* codes = (HuffmanCode*)malloc(sizeof(HuffmanCode) * n);//此时codes为一维数组 

	memset(codes, 0, sizeof(HuffmanCode) * n);

	//编码空间的起始位置
	int start;
	int p;
	int pos;

	for (int i = 1; i <= n; ++i)
	{
		start = n - 1;//因为最多就是一条链，编码长度为n（下标0____n-1） 

		temp[start] = '\0';//字符串的结束符 \0，右往左逐位存放编码 首先就先放结束符

		pos = i;//i结点 

		p = tree[i].parent;//i结点的双亲结点 

		while (p)
		{
			--start;
			temp[start] = ((tree[p].lChild == pos) ? '0' : '1');
			pos = p;
			p = tree[p].parent;
		}

		codes[i - 1] = (HuffmanCode)malloc(sizeof(char) * (n - start));//(n - start)编码长度 

		my_strcpy(codes[i - 1], &temp[start]);//此时codes为二维数组 
	}
	free(temp);
	return codes;
}


int main()
{
	int w[] = { 5, 29, 7, 8,14, 23, 3, 11 };
	char show[] = { 'A', 'B', 'C', 'D','E', 'F', 'G', 'H' };
	HuffmanTree tree = createHuffmanTree(w, sizeof(w) / sizeof(w[0]));

	HuffmanCode* code = createHuffmanCode(tree, sizeof(w) / sizeof(w[0]));
	for (int i = 0; i < sizeof(w) / sizeof(w[0]); ++i)
	{
		printf("%c: %s\n", show[i], code[i]);
	}

	return 0;
}

