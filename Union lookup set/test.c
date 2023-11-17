#include <stdio.h>
//#include <stdlib.h>

int f[10];

void init(int n) {
	for (int i=1; i <= n; i++) {
		f[i] = i;//建立起n个元素的集合
	}
}
//这种查找会形成一个类似链表，O(n)
int find(int x) {
	while (f[x] != x) {
		x = f[x];
	}
	return x;
}
//不如find2有归并操作，两个集合合并后仍然有不同的根节点
int find1(int x) {
	//递归
	if (f[x] != x) {
		return find1(f[x]);
	}
	return x;
}

//优化压缩路径，找到x的根节点
int find2(int x) {
	//递归
	if (f[x] != x) {//当x的头结点为自己时，就找到根了
		return f[x] = find2(f[x]);
	}
	return x;
}

void unionn(int x, int y) {
	int ax = find2(x);
	int ay = find2(y);
	f[ay] = ax;//合并
}

int main() {
	init(6);
	int m, x, y;//m:m对关系；x：元素，y:元素；
	printf("共有m对关系\n");
	scanf_s("%d", &m);
	for (int i = 1; i <= m; i++) {
		printf("输入谁和谁有关系");
		scanf_s("%d %d", &x, &y);
		unionn(x, y);//建立起关系,谁跟谁有关系
	}
	printf("输入共有几个查询");
	scanf_s("%d", &m);//有m个查询
	for (int i = 1; i <= m; i++) {
		printf("查询二者之间的关系\n");
		scanf_s("%d %d", &x, &y);
		int ax = find2(x);
		int ay = find2(y);
		if (ax == ay) {
			printf("有关系\n");
		}
		else {
			printf("没关系\n");
		}
	}

	return 0;
}