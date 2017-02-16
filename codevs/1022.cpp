#include <cstdio>

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
const int dx[] = { 1, 0 }, dy[] = { 0, 1 };
int n, m, k, ivc, vc, ec = 2, gap[10010];
bool map[110][110];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	ivc = n * m;
	vc = ivc + 2;
	gap[0] = vc;
}

inline void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void network_add_edge(int u, int v, int f)
{
	add_edge(u, v, f);
	add_edge(v, u, 0);
}

int isap(int u, int curf)
{
	if (u == sink) return curf;
	int totalf = 0, mindis = vc;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0) V[src].dis = vc;
		gap[V[u].dis = mindis + 1]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < vc) res += isap(src, INF);
	return res;
}

int main()
{
	int x, y;
	scanf("%d%d%d", &n, &m, &k);
	while (k--)
	{
		scanf("%d%d", &x, &y);
		map[x][y] = true;
	}
	for (int i = 0; i <= n + 1; i++)
	{
		map[i][0] = map[i][m + 1] = true;
	}
	for (int i = 0; i <= m + 1; i++)
	{
		map[0][i] = map[n + 1][i] = true;
	}
	init();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == false)
			{
				for (int p = 0; p < 2; p++)
				{
					if (map[i + dx[p]][j + dy[p]] == false)
					{
						if (((i + j) & 1) == 0) network_add_edge(i + (j - 1) * n, (i + dx[p]) + (j + dy[p] - 1) * n, 1);
						else network_add_edge((i + dx[p]) + (j + dy[p] - 1) * n, i + (j - 1) * n, 1);
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (((i + j) & 1) == 0) network_add_edge(src, i + (j - 1) * n, 1);
			else network_add_edge(i + (j - 1) * n, sink, 1);
		}
	}
	printf("%d", max_flow());
	return 0;
}
