#include <cstdio>

#define INF 1000000000
#define VERTEX_COUNT 1010
#define EDGE_COUNT 100010

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow;
}E[EDGE_COUNT];

int n, m, src, sink, ec = 2, gap[VERTEX_COUNT];
int cnt[1010], last[1010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	src = 1005;
	sink = 1006;
	gap[0] = m + 2;
	for (int i = 1; i <= n; i++)
	{
		last[i] = src;
	}
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

int isap(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	int totalf = 0, mindis = m + 2;
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
		if (gap[V[u].dis] == 0)
		{
			V[src].dis = m + 2;
		}
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < m + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

int main()
{
	int c, b, x;
	scanf("%d%d", &n, &m);
	init();
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &cnt[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &c);
		for (int j = 0; j < c; j++)
		{
			scanf("%d", &x);
			add_edge(last[x], i, last[x] == src ? cnt[x] : 1000000);
			add_edge(i, last[x], 0);
			last[x] = i;
		}
		scanf("%d", &b);
		add_edge(i, sink, b);
		add_edge(sink, i, 0);
	}
	printf("%d", max_flow());
	return 0;
}
