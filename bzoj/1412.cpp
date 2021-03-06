#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[10010];

struct edge
{
	int endp, next, flow;
}E[80010];

const int src = 10005, sink = 10006, dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };
int n, m, map[110][110], ec = 2;

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

bool bfs()
{
	static bool vis[10010];
	memset(vis, 0, sizeof(vis));
	queue<int> Q;
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
				Q.push(E[cur].endp), vis[E[cur].endp] = true;
			}
		}
	}
	return vis[src] == true;
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
	while (bfs())
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
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 0; i <= n + 1; i++)
	{
		map[i][0] = -1;
		map[i][m + 1] = -1;
	}
	for (int i = 0; i <= m + 1; i++)
	{
		map[0][i] = -1;
		map[n + 1][i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == 1)
			{
				for (int k = 0; k < 4; k++)
				{
					if (map[i + dx[k]][j + dy[k]] == 0 || map[i + dx[k]][j + dy[k]] == 2)
					{
						add_edge((i - 1) * m + j, (i + dx[k] - 1) * m + j + dy[k], 1);
					}
				}
				add_edge(src, (i - 1) * m + j, INF);
			}
			else if (map[i][j] == 0)
			{
				for (int k = 0; k < 4; k++)
				{
					if (map[i + dx[k]][j + dy[k]] == 2 || map[i + dx[k]][j + dy[k]] == 0)
					{
						add_edge((i - 1) * m + j, (i + dx[k] - 1) * m + j + dy[k], 1);
					}
				}
			}
			else
			{
				add_edge((i - 1) * m + j, sink, INF);
			}
		}
	}
	printf("%d", dinic());
	return 0;
}
