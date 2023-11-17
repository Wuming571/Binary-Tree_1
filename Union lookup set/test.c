#include <stdio.h>
//#include <stdlib.h>

int f[10];

void init(int n) {
	for (int i=1; i <= n; i++) {
		f[i] = i;//������n��Ԫ�صļ���
	}
}
//���ֲ��һ��γ�һ����������O(n)
int find(int x) {
	while (f[x] != x) {
		x = f[x];
	}
	return x;
}
//����find2�й鲢�������������Ϻϲ�����Ȼ�в�ͬ�ĸ��ڵ�
int find1(int x) {
	//�ݹ�
	if (f[x] != x) {
		return find1(f[x]);
	}
	return x;
}

//�Ż�ѹ��·�����ҵ�x�ĸ��ڵ�
int find2(int x) {
	//�ݹ�
	if (f[x] != x) {//��x��ͷ���Ϊ�Լ�ʱ�����ҵ�����
		return f[x] = find2(f[x]);
	}
	return x;
}

void unionn(int x, int y) {
	int ax = find2(x);
	int ay = find2(y);
	f[ay] = ax;//�ϲ�
}

int main() {
	init(6);
	int m, x, y;//m:m�Թ�ϵ��x��Ԫ�أ�y:Ԫ�أ�
	printf("����m�Թ�ϵ\n");
	scanf_s("%d", &m);
	for (int i = 1; i <= m; i++) {
		printf("����˭��˭�й�ϵ");
		scanf_s("%d %d", &x, &y);
		unionn(x, y);//�������ϵ,˭��˭�й�ϵ
	}
	printf("���빲�м�����ѯ");
	scanf_s("%d", &m);//��m����ѯ
	for (int i = 1; i <= m; i++) {
		printf("��ѯ����֮��Ĺ�ϵ\n");
		scanf_s("%d %d", &x, &y);
		int ax = find2(x);
		int ay = find2(y);
		if (ax == ay) {
			printf("�й�ϵ\n");
		}
		else {
			printf("û��ϵ\n");
		}
	}

	return 0;
}