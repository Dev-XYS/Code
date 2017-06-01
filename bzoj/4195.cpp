#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

int n, a[100010], b[100010], w[100010], cnt, fa[200010], size[200010];
map<int, int> ord;

void init_map()
{
	ord.clear();
	cnt = 0;
}

void init_dsu()
{
	for (int i = 1; i <= cnt; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	else return fa[x] = getrt(fa[x]);
}

void merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (size[rtx] < size[rty])
	{
		fa[rtx] = rty;
		size[rty] += size[rtx];
	}
	else
	{
		fa[rty] = rtx;
		size[rtx] += size[rty];
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d", &a[i], &b[i], &w[i]);
		}
		init_map();
		for (int i = 0; i < n; i++)
		{
			if (ord[a[i]] == 0) ord[a[i]] = ++cnt;
			if (ord[b[i]] == 0) ord[b[i]] = ++cnt;
		}
		init_dsu();
		for (int i = 0; i < n; i++)
		{
			a[i] = ord[a[i]];
			b[i] = ord[b[i]];
		}
		for (int i = 0; i < n; i++)
		{
			if (w[i] == 1)
			{
				merge(a[i], b[i]);
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (w[i] == 0)
			{
				if (getrt(a[i]) == getrt(b[i]))
				{
					printf("NO\n");
					goto END;
				}
			}
		}
		printf("YES\n");
	END:;
	}
	return 0;
}
