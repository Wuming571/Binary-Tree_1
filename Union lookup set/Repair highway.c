#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hh
{
    int x, y, t;
} a[200000];

int f[200000], n, m;

int cmp(const void* a, const void* b)
{
    return ((struct hh*)a)->t - ((struct hh*)b)->t;
}

int find(int x)
{
    return f[x] == x ? x : (f[x] = find(f[x]));
}

int getin()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - 48, ch = getchar();
    return x;
}

int main()
{
    n = getin(), m = getin();
    if (n == 1)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= m; i++)
        a[i].x = getin(), a[i].y = getin(), a[i].t = getin();

    qsort(a + 1, m, sizeof(struct hh), cmp);

    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int fx = find(a[i].x), fy = find(a[i].y);
        if (fx != fy)
            f[fx] = fy, n--;
        if (n == 1)
        {
            printf("%d", a[i].t);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
