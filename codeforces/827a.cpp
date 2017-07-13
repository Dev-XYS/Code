#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct interval
{
	int l, r, id;
	interval(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) { }
}d[1000010];

int n, ic;
char temp[1000010], *t[100010], ans[2000010];

inline bool _interval_cmp_(const interval &x, const interval &y)
{
	return x.l < y.l;
}

int main()
{
	scanf("%d", &n);
	int k, x;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", temp);
		int len = strlen(temp);
		t[i] = new char[len + 1];
		strcpy(t[i], temp);
		scanf("%d", &k);
		while (k--)
		{
			scanf("%d", &x);
			d[ic++] = interval(x, x + len - 1, i);
		}
	}
	sort(d, d + ic, _interval_cmp_);
	int right = 0;
	for (int i = 0; i < ic; i++)
	{
		for (int j = max(right + 1, d[i].l); j <= d[i].r; j++)
		{
			ans[j] = t[d[i].id][j - d[i].l];
		}
		right = max(right, d[i].r);
	}
	for (int i = 1; i <= right; i++)
	{
		if (ans[i] == 0)
		{
			ans[i] = 'a';
		}
	}
	printf("%s\n", ans + 1);
	return 0;
}
