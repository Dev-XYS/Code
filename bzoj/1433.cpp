#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[110];

struct edge
{
	int endp, next, flow;
}E[5210];

const int src = 105, sink = 106;
int T, n, student[60], gohome[60], rec[60][60], ec;

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

void init_graph()
{
	memset(V, 0, sizeof(V));
	ec = 2;
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
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &student[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &gohome[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				scanf("%d", &rec[i][j]);
			}
			rec[i][i] = 1;
		}
		init_graph();
		int need = 0;
		for (int i = 1; i <= n; i++)
		{
			if (student[i] == false || (student[i] == true && gohome[i] == false))
			{
				need++;
				for (int j = 1; j <= n; j++)
				{
					if ((rec[i][j] == 1 || rec[j][i] == 1) && student[j] == true)
					{
						add_edge(i, j + n, 1);
					}
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			add_edge(src, i, 1);
		}
		for (int i = 1; i <= n; i++)
		{
			add_edge(i + n, sink, 1);
		}
		printf("%s\n", dinic() == need ? "^_^" : "T_T");
	}
	return 0;
}
