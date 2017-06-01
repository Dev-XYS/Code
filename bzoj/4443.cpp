// Problem Name: 小凸玩矩阵
// Source: [SCOI2015]

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[510];

struct edge
{
	int endp, next, flow;
}E[126010];

const int src = 505, sink = 506;
int n, m, k, s[255][255], ec = 2, ns[62510];

inline void _add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void add_empty_edge(int u, int v)
{
	_add_edge(u, v, 0);
	_add_edge(v, u, 0);
}

bool bfs()
{
	queue<int> Q;
	static bool vis[1010];
	memset(vis, 0, sizeof(vis));
	V[sink].dis = 0, Q.push(sink), vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (vis[E[cur].endp] == false && E[cur ^ 1].flow > 0)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), vis[E[cur].endp] = true;
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
	if (totalf == 0) V[u].dis = -1;
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

void build_graph()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			add_empty_edge(i, j + n);
		}
	}
	for (int i = 0; i < n; i++)
	{
		add_empty_edge(src, i);
	}
	for (int j = 0; j < m; j++)
	{
		add_empty_edge(j + n, sink);
	}
}

void fill(int x)
{
	int p = 2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (s[i][j] <= x)
			{
				E[p].flow = 1;
				E[p + 1].flow = 0;
			}
			else
			{
				E[p].flow = 0;
				E[p + 1].flow = 0;
			}
			p += 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		E[p].flow = 1;
		E[p + 1].flow = 0;
		p += 2;
	}
	for (int j = 0; j < m; j++)
	{
		E[p].flow = 1;
		E[p + 1].flow = 0;
		p += 2;
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int p = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &s[i][j]);
			ns[p++] = s[i][j];
		}
	}
	build_graph();
	sort(ns, ns + p);
	int l = 0, r = p - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		fill(ns[mid]);
		if (dinic() >= n - k + 1) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", ns[l]);
	return 0;
}
