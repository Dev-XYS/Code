// Problem Name: 滑雪与时间胶囊
// Source: [SCOI2012]

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
	bool vis;
}V[100010];

struct edge
{
	int endp, next, w;
}E[2000010];

struct raw_edge
{
	int u, v, w;
}R[1000010];

int n, m, ec = 1, height[100010], fa[100010], size[100010], cnt;
ll ans;

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
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
	if (fa[x] == x)
	{
		return x;
	}
	return fa[x] = getrt(fa[x]);
}

bool merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty)
	{
		return false;
	}
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

inline bool _raw_edge_cmp_(const raw_edge &x, const raw_edge &y)
{
	if (height[x.v] == height[y.v]) return x.w < y.w;
	return height[x.v] > height[y.v];
}

void dfs(int u)
{
	V[u].vis = true;
	cnt++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].vis == false)
		{
			dfs(E[cur].endp);
		}
	}
}

void kruskal()
{
	sort(R, R + m, _raw_edge_cmp_);
	init_dsu();
	for (int i = 0; i < m; i++)
	{
		if (V[R[i].u].vis == true && V[R[i].v].vis == true)
		{
			if (merge(R[i].u, R[i].v) == true)
			{
				ans += R[i].w;
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &height[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].w);
		if (height[R[i].u] >= height[R[i].v])
		{
			add_edge(R[i].u, R[i].v, R[i].w);
		}
		if (height[R[i].v] >= height[R[i].u])
		{
			add_edge(R[i].v, R[i].u, R[i].w);
			swap(R[i].u, R[i].v);
		}
	}
	dfs(1);
	kruskal();
	printf("%d %lld\n", cnt, ans);
	return 0;
}
