// Problem Name: 寿司餐厅
// Source: [LNOI2017]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[6160];

struct edge
{
	int endp, next, flow;
}E[32710];

const int src = 6155, sink = 6156;
int n, m, a[110], d[110][110], ec = 2, rangec;

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

inline int sum(int l, int r)
{
	return (l + r) * (r - l + 1) / 2;
}

inline int range(int l, int r)
{
	return sum(n + 2 - l, n) + (r - l + 1);
}

inline int item(int x)
{
	return rangec + x;
}

inline int id(int x)
{
	return rangec + n + x;
}

bool bfs()
{
	queue<int> Q;
	static bool vis[6160];
	memset(vis, 0, sizeof(vis));
	Q.push(sink);
	vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur ^ 1].flow > 0 && vis[E[cur].endp] == false)
			{
				Q.push(E[cur].endp), vis[E[cur].endp] = true;
				V[E[cur].endp].dis = V[u].dis + 1;
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
		if (E[cur].flow > 0 && V[u].dis == V[E[cur].endp].dis + 1)
		{
			int f = dfs(E[cur].endp, min(curf - totalf, E[cur].flow));
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


int main()
{
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			scanf("%d", &d[i][j]);
		}
	}
	rangec = n * (n + 1) / 2;
	for (int i = 1; i <= n; i++)
	{
		add_edge(range(i, i), item(i), INF);
		for (int j = i + 1; j <= n; j++)
		{
			add_edge(range(i, j), range(i + 1, j), INF);
			add_edge(range(i, j), range(i, j - 1), INF);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(item(i), id(a[i]), INF);
	}
	int total = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			if (d[i][j] > 0) add_edge(src, range(i, j), d[i][j]), total += d[i][j];
			else add_edge(range(i, j), sink, -d[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(item(i), sink, a[i]);
	}
	for (int i = 1; i <= 1000; i++)
	{
		add_edge(id(i), sink, m * i * i);
	}
	printf("%d\n", total - dinic());
	return 0;
}
