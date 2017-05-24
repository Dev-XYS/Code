// Problem Name: Network

#include <cstdio>
#include <algorithm>

using namespace std;

struct raw_edge
{
	int u, v, w;
	bool choose;
}R[30010];

struct vertex
{
	int first, depth;
}V[15010];

struct edge
{
	int endp, next, w;
}E[30010];

int n, m, k, ec = 2, fa[15010], size[15010], an[15010][15], mv[15010][15];

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

inline bool _raw_edge_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.w < y.w;
}

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
	return fa[x] == x ? x : (fa[x] = getrt(fa[x]));
}

bool merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty) return false;
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
	return true;
}

void kruskal()
{
	sort(R, R + m, _raw_edge_cmp_);
	init_dsu();
	for (int i = 0; i < m; i++)
	{
		if (merge(R[i].u, R[i].v) == true) R[i].choose = true;
	}
}

void build_graph()
{
	for (int i = 0; i < m; i++)
	{
		if (R[i].choose == true)
		{
			add_edge(R[i].u, R[i].v, R[i].w);
			add_edge(R[i].v, R[i].u, R[i].w);
		}
	}
}

void dfs(int u, int fae, int depth)
{
	an[u][0] = E[fae ^ 1].endp;
	mv[u][0] = E[fae].w;
	V[u].depth = depth;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if ((cur ^ fae) != 1) dfs(E[cur].endp, cur, depth + 1);
	}
}

void init_an()
{
	for (int i = 1; i <= n; i++)
	{
		if (an[i][0] == 0) dfs(i, 0, 0);
	}
	for (int k = 1; k < 15; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			an[i][k] = an[an[i][k - 1]][k - 1];
			mv[i][k] = max(mv[i][k - 1], mv[an[i][k - 1]][k - 1]);
		}
	}
}

int query(int u, int v)
{
	int res = 0;
	if (V[u].depth < V[v].depth) swap(u, v);
	for (int i = 15 - 1; i >= 0; i--)
	{
		if (V[u].depth - V[v].depth >= (1 << i))
		{
			res = max(res, mv[u][i]);
			u = an[u][i];
		}
	}
	if (u == v) return res;
	for (int i = 15 - 1; i >= 0; i--)
	{
		if (an[u][i] != an[v][i])
		{
			res = max(res, mv[u][i]);
			res = max(res, mv[v][i]);
			u = an[u][i];
			v = an[v][i];
		}
	}
	res = max(res, mv[u][0]);
	res = max(res, mv[v][0]);
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].w);
	}
	kruskal();
	build_graph();
	init_an();
	int u, v;
	while (k--)
	{
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
	return 0;
}
