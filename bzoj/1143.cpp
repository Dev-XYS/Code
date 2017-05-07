// Problem Name: 祭祀 river
// Source: [CTSC2008]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[210];

struct edge
{
	int endp, next, flow;
}E[20410];

const int src = 205, sink = 206;
int n, m, ec = 2;
bool has[110][110];

inline void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

void floyd()
{
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				has[i][j] = has[i][j] | (has[i][k] && has[k][j]);
			}
		}
	}
}

void build_graph()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (has[i][j] == true)
			{
				add_edge(i, j + n, 1);
				add_edge(j + n, i, 0);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(src, i, 1);
		add_edge(i, src, 0);
		add_edge(i + n, sink, 1);
		add_edge(sink, i + n, 0);
	}
}

bool bfs()
{
	queue<int> Q;
	static bool vis[210];
	memset(vis, 0, sizeof(vis));
	Q.push(sink), vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur ^ 1].flow > 0 && vis[E[cur].endp] == false)
			{
				Q.push(E[cur].endp), vis[E[cur].endp] = true, V[E[cur].endp].dis = V[u].dis + 1;
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

int main()
{
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		has[u][v] = true;
	}
	floyd();
	build_graph();
	printf("%d\n", n - dinic());
	return 0;
}
