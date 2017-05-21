// Problem Name: 圈地计划

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

const int src = 10005, sink = 10006;
int n, m, ec = 2, C[110][110];

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
	static bool vis[10010];
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
	{printf("res = %d\n", res);
		int f;
		do
		{
			f = dfs(src, INF);
			res += f;
		} while (f > 0);
	}
	return res;
}

/* Algorithm ISAP begins */
/* Author : Dev-XYS */

int gap[10010];

int isap(int u, int curf)
{
	if (u == sink) return curf;
	int totalf = 0;
	int mindis = n + m * 2 + 2;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[E[cur].endp].dis + 1 == V[u].dis)
			{
				int f = isap(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
			if (V[E[cur].endp].dis < mindis) mindis = V[E[cur].endp].dis;
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0)
		{
			V[src].dis = n + m * 2 + 2;
			return 0;
		}
		gap[V[u].dis = mindis + 1]++;
	}
	return totalf;
}

int max_flow()
{
	gap[0] = n + m * 2 + 2;
	int res = 0;
	while (V[src].dis < n + m * 2 + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

/* Algorithm ISAP ends */

inline int id(int x, int y)
{
	return x * m + y;
}

int main()
{
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int c;
	int total = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &c);
			if (((i + j) & 1) == 0) add_edge(src, id(i, j), c);
			else add_edge(id(i, j), sink, c);
			total += c;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &c);
			if (((i + j) & 1) == 0) add_edge(id(i, j), sink, c);
			else add_edge(src, id(i, j), c);
			total += c;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &C[i][j]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = ((i & 1) == 0 ? 1 : 2); j <= m; j += 2)
		{
			if (i > 0) _add_edge(id(i, j), id(i - 1, j), C[i][j] + C[i - 1][j]), _add_edge(id(i - 1, j), id(i, j), C[i][j] + C[i - 1][j]), total += C[i][j] + C[i - 1][j];
			if (i < n - 1) _add_edge(id(i, j), id(i + 1, j), C[i][j] + C[i + 1][j]), _add_edge(id(i + 1, j), id(i, j), C[i][j] + C[i + 1][j]), total += C[i][j] + C[i + 1][j];
			if (j > 1) _add_edge(id(i, j), id(i, j - 1), C[i][j] + C[i][j - 1]), _add_edge(id(i, j - 1), id(i, j), C[i][j] + C[i][j - 1]), total += C[i][j] + C[i][j - 1];
			if (j < m) _add_edge(id(i, j), id(i, j + 1), C[i][j] + C[i][j + 1]), _add_edge(id(i, j + 1), id(i, j), C[i][j] + C[i][j + 1]), total += C[i][j] + C[i][j + 1];
		}
	}
	printf("%d\n", total - max_flow());
	return 0;
}
