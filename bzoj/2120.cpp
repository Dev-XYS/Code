// Problem Name: 数颜色

#include <cstdio>

using namespace std;

int n, m, col[10010], mark[11010], hc, map[1000010];

int main()
{
	char op[10];
	int a, b;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		if (map[col[i]] == false) map[col[i]] = ++hc;
		col[i] = map[col[i]];
	}
	for (int t = 1; t <= m; t++)
	{
		scanf("%s%d%d", op, &a, &b);
		if (op[0] == 'R')
		{
			if (map[b] == 0) map[b] = ++hc;
			col[a] = map[b];
		}
		else
		{
			int ans = 0;
			for (int i = a; i <= b; i++)
			{
				if (mark[col[i]] != t) mark[col[i]] = t, ans++;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
