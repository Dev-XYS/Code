// Problem Name: 公路修建问题
// Source: [HNOI2006]

#include <cstdio>

using namespace std;

struct raw_edge
{
	int u, v, c1, c2;
	raw_edge(int _u = 0, int _v = 0, int _c1 = 0, int _c2 = 0) : u(_u), v(_v), c1(_c1), c2(_c2) { }
}R[20010];

int n, k, m, fa[10010], size[10010];

void init_dsu()
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = getrt(fa[x]);
}

int merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty) return 0;
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
	return 1;
}

bool check(int maxw)
{
	int ec = 0;
	init_dsu();
	for (int i = 1; i < m; i++)
	{
		if (R[i].c1 <= maxw) ec += merge(R[i].u, R[i].v);
	}
	if (ec < k) return false;
	for (int i = 1; i < m; i++)
	{
		if (R[i].c2 <= maxw) ec += merge(R[i].u, R[i].v);
	}
	if (ec < n - 1) return false;
	return true;
}

int main()
{
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 1; i < m; i++)
	{
		scanf("%d%d%d%d", &R[i].u, &R[i].v, &R[i].c1, &R[i].c2);
	}
	int l = 0, r = 30000;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid) == true) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
