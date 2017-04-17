// Problem Name: 跳舞 dance
// Source: [CQOI2009]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
	bool vis;
}V[210];

struct edge
{
	int endp, next, flow;
}E[5410];

const int src = 205, sink = 206;
int n, k, ec;
char like[60][60];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init_graph()
{
	ec = 2;
	for (int i = n * 4 - 1; i >= 0; i--)
	{
		V[i].first = 0;
	}
	V[src].first = 0;
	V[sink].first = 0;
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

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", like[i]);
	}
	int flow;
	for (flow = 1; flow <= n; flow++)
	{
		init_graph();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (like[i][j] == 'Y') add_edge(i, j + n * 2, 1);
				else add_edge(i + n, j + n * 3, 1);
			}
		}
		for (int i = 0; i < n; i++)
		{
			add_edge(src, i, flow);
			add_edge(i, i + n, k);
			add_edge(i + n * 2, sink, flow);
			add_edge(i + n * 3, i + n * 2, k);
		}
		if (dinic() < flow * n) break;
	}
	printf("%d", flow - 1);
	return 0;
}
