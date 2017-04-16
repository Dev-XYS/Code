// Problem Name: 超级英雄 Hero
// Source: [HNOI2006]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
	bool vis;
}V[2010];

struct edge
{
	int endp, next, flow;
}E[8010];

const int src = 2005, sink = 2006;
int n, m, ec = 2;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline void _add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void add_edge(int u, int v, int f)
{
	_add_edge(u, v, f);
	_add_edge(v, u, 0);
}

namespace Dinic
{
	bool bfs()
	{
		queue<int> Q;
		static bool vis[2010];
		memset(vis, 0, sizeof(vis));
		Q.push(sink), vis[sink] = true;
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int cur = V[u].first; cur != 0; cur = E[cur].next)
			{
				if (vis[E[cur].endp] == false && E[cur ^ 1].flow > 0)
				{
					V[E[cur].endp].dis = V[u].dis + 1;
					Q.push(E[cur].endp), vis[E[cur].endp] = true;;
				}
			}
		}
		return vis[src];
	}

	int dfs(int u, int curf)
	{
		if (u == sink) return curf;
		int totalf = 0;
		for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].flow > 0)
			{
				int f = dfs(E[cur].endp, min(E[cur].flow, curf - totalf));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
		}
		return totalf;
	}

	int dinic()
	{
		int res = 0;
		while (bfs() == true)
		{
			int f;
			do
			{
				f = dfs(src, INF);
				res += f;
			} while (f > 0);
		}
		return res;
	}
}

int dfs(int u)
{
	if (u == src) return 0;
	if (u == sink) return 1;
	if (V[u].vis == true) return 0;
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (dfs(E[cur].endp) > 0)
			{
				E[cur].flow--;
				E[cur ^ 1].flow++;
				return 1;
			}
		}
	}
	return 0;
}

int match()
{
	int res = 0;
	for (int cur = V[src].first; cur != 0; cur = E[cur].next)
	{
		for (int i = 0; i < n + m; i++)
		{
			V[i].vis = false;
		}
		if (dfs(E[cur].endp) > 0)
		{
			E[cur].flow--;
			E[cur ^ 1].flow++;
			res++;
		}
		else break;
	}
	return res;
}

int main()
{
	int a, b;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &a, &b);
		add_edge(i + n, a, 1);
		add_edge(i + n, b, 1);
	}
	for (int i = m - 1; i >= 0; i--)
	{
		add_edge(src, i + n, 1);
	}
	for (int i = 0; i < n; i++)
	{
		add_edge(i, sink, 1);
	}
	printf("%d", match());
	return 0;
}
