// Problem Name: 巡逻
// Source: [APIO2010]

#include <cstdio>

using namespace std;

struct vertex
{
	int first, dis, mx1, mx2;
}V[100010];

struct edge
{
	int endp, next, w;
}E[200010];

int n, K, ec = 2, d1s, d1t, d2s, d2t;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = 1;
	ec++;
}

void dfs(int u, int pre, int dis)
{
	V[u].dis = dis;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != pre) dfs(E[cur].endp, u, dis + E[cur].w);
	}
}

int get_diametre(int &ds, int &dt)
{
	dfs(1, 0, 0);
	ds = 1;
	for (int i = 2; i <= n; i++)
	{
		if (V[i].dis > V[ds].dis) ds = i;
	}
	dfs(ds, 0, 0);
	dt = 1;
	for (int i = 2; i <= n; i++)
	{
		if (V[i].dis > V[dt].dis) dt = i;
	}
	return V[dt].dis;
}

int S[100010], sp;
bool found = false;
void dfs_find(int u, int pre, int tar)
{
	if (u == tar)
	{
		for (int i = 0; i < sp; i++)
		{
			E[S[i]].w = E[S[i] ^ 1].w = -1;
		}
		found = true;
		return;
	}
	for (int cur = V[u].first; cur != 0 && found == false; cur = E[cur].next)
	{
		if (E[cur].endp != pre)
		{
			S[sp++] = cur;
			dfs_find(E[cur].endp, u, tar);
			sp--;
		}
	}
}

void dfs_dp(int u, int pre)
{
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != pre)
		{
			dfs_dp(E[cur].endp, u);
			if (E[cur].w + V[E[cur].endp].mx1 >= V[u].mx1) V[u].mx2 = V[u].mx1, V[u].mx1 = E[cur].w + V[E[cur].endp].mx1;
			else if (E[cur].w + V[E[cur].endp].mx1 >= V[u].mx2) V[u].mx2 = E[cur].w + V[E[cur].endp].mx1;
		}
	}
}

int main()
{
	scanf("%d%d", &n, &K);
	int u, v;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	int len1 = get_diametre(d1s, d1t);
	if (K == 1)
	{
		printf("%d\n", (n - 1) * 2 - len1 + 1);
		return 0;
	}
	dfs_find(d1s, 0, d1t);
	dfs_dp(1, 0);
	int len2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (E[V[i].first].next == 0)
		{
			if (V[i].mx1 > len2) len2 = V[i].mx1;
		}
		else
		{
			if (V[i].mx1 + V[i].mx2 > len2) len2 = V[i].mx1 + V[i].mx2;
		}
	}
	printf("%d\n", (n - 1) * 2 - len1 - len2 + 2);
	return 0;
}
