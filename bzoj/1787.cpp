// Problem Name: 紧急集合 Meet
// Source: [AHOI2008]

#include <cstdio>

using namespace std;

struct vertex
{
	int first, fa[21], depth;
}V[500010];

struct edge
{
	int endp, next;
}E[1000010];

int ivc, m, ec = 2;

inline void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u, int fa, int depth)
{
	V[u].fa[0] = fa;
	V[u].depth = depth;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa) dfs(E[cur].endp, u, depth + 1);
	}
}

void init()
{
	for (int k = 1; (1 << k) < ivc; k++)
	{
		for (int i = 1; i <= ivc; i++)
		{
			V[i].fa[k] = V[V[i].fa[k - 1]].fa[k - 1];
		}
	}
}

int lca(int x, int y)
{
	if (V[x].depth < V[y].depth) swap(x, y);
	for (int i = 20; i >= 0; i--)
	{
		if (V[V[x].fa[i]].depth >= V[y].depth) x = V[x].fa[i];
	}
	if (x == y) return x;
	for (int i = 20; i >= 0; i--)
	{
		if (V[x].fa[i] != V[y].fa[i]) x = V[x].fa[i], y = V[y].fa[i];
	}
	return V[x].fa[0];
}

void solve(int x, int y, int z)
{
	int a1 = lca(x, y), a2 = lca(y, z), a3 = lca(z, x);
	if (V[a1].depth >= V[a2].depth && V[a1].depth >= V[a3].depth)
	{
		int ta = lca(a1, z);
		printf("%d %d\n", a1, (V[x].depth - V[a1].depth) + (V[y].depth - V[a1].depth) + ((V[a1].depth - V[ta].depth) + (V[z].depth - V[ta].depth)));
	}
	else if (V[a2].depth >= V[a1].depth && V[a2].depth >= V[a3].depth)
	{
		int ta = lca(a2, x);
		printf("%d %d\n", a2, (V[y].depth - V[a2].depth) + (V[z].depth - V[a2].depth) + ((V[a2].depth - V[ta].depth) + (V[x].depth - V[ta].depth)));
	}
	else
	{
		int ta = lca(a3, y);
		printf("%d %d\n", a3, (V[z].depth - V[a3].depth) + (V[x].depth - V[a3].depth) + ((V[a3].depth - V[ta].depth) + (V[y].depth - V[ta].depth)));
	}
}

int main()
{
	int u, v, x, y, z;
	scanf("%d%d", &ivc, &m);
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0, 1);
	init();
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		solve(x, y, z);
	}
	return 0;
}
