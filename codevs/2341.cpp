// Problem Name: 善意的投票 Vote
// Source: [SHOI2007]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis, sleep;
}V[310];

struct edge
{
	int endp, next, flow;
}E[90910];

const int src = 305, sink = 306;
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

bool bfs()
{
	queue<int> Q;
	static bool vis[3010];
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
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].sleep);
	}
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		_add_edge(u, v, 1);
		_add_edge(v, u, 1);
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].sleep == 0) add_edge(src, i, 1);
		else add_edge(i, sink, 1);
	}
	printf("%d\n", dinic());
	return 0;
}
