#include <cstdio>

#define INF 1000000000
#define VERTEX_COUNT 410
#define EDGE_COUNT 40410

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow;
}E[EDGE_COUNT];

int n, f, d, src, sink, ec = 2, gap[VERTEX_COUNT];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	src = 405;
	sink = 406;
	gap[0] = f + n * 2 + d + 2;
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
	int totalf = 0, mindis = f + d + 2;
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
			V[src].dis = f + d + 2;
		}
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < f + d + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

int main()
{
	int fi, di, td, tf;
	scanf("%d%d%d", &n, &f, &d);
	init();
	for (int i = 1; i <= f; i++)
	{
		add_edge(src, i, 1);
		add_edge(i, src, 0);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &fi, &di);
		for (int j = 0; j < fi; j++)
		{
			scanf("%d", &tf);
			add_edge(tf, i + f, 1);
			add_edge(i + f, tf, 0);
		}
		for (int j = 0; j < di; j++)
		{
			scanf("%d", &td);
			add_edge(f + n + i, f + n * 2 + td, 1);
			add_edge(f + n * 2 + td, f + n + i, 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(f + i, f + n + i, 1);
		add_edge(f + n + i, f + i, 0);
	}
	for (int i = 1; i <= d; i++)
	{
		add_edge(f + n * 2 + i, sink, 1);
		add_edge(sink, f + n * 2 + i, 0);
	}
	printf("%d", max_flow());
	return 0;
}
