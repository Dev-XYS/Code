#include <cstdio>
#include <cstring>

#define INF 1000000000
#define SOURCE 1005
#define SINK 1006
#define VERTEX_COUNT 1010
#define EDGE_COUNT 22010

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

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init_graph()
{
	src = SOURCE;
	sink = SINK;
	memset(V, 0, sizeof(V));
	memset(gap, 0, sizeof(gap));
	gap[0] = n * 2 + 2;
	ec = 2;
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
	int totalf = 0, mindis = n * 2 + 2;
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
			V[src].dis = n * 2 + 2;
		}
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < n * 2 + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

int main()
{
	int x, y;
	while (scanf("%d%d", &n, &m) > 0)
	{
		init_graph();
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &x, &y);
			add_edge(x, y + n, 10000);
			add_edge(y + n, x, 0);
		}
		for (int i = 1; i <= n; i++)
		{
			add_edge(src, i, 1);
			add_edge(i, src, 0);
			add_edge(i + n, sink, 1);
			add_edge(sink, i + n, 0);
		}
		printf("%d\n", max_flow());
	}
	return 0;
}
