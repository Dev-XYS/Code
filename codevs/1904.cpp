#include <cstdio>

#define INF 1000000000
#define SOURCE 100005
#define SINK 100006

using namespace std;

struct vertex
{
	int first, dis;
}V[100010];

struct edge
{
	int endp, next, flow;
}E[100010];

int ivc, iec, vc, ec = 2, gap[100010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	vc = ivc * 2 + 2;
	gap[0] = vc;
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].flow = 0;
	ec++;
}

int isap(int u, int curf)
{
	if (u == SINK) return curf;
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
		if (gap[V[u].dis] == 0) V[SOURCE].dis = vc;
		else
		{
			V[u].dis = mindis + 1;
			gap[V[u].dis]++;
		}
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[SOURCE].dis < vc)
	{
		res += isap(SOURCE, INF);
	}
	return res;
}

void build_graph()
{
	for (int i = 1; i <= ivc; i++)
	{
		add_edge(SOURCE, i, 1);
		add_edge(i + ivc, SINK, 1);
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v + ivc, 1);
	}
	build_graph();
	init();
	printf("%d", ivc - max_flow());
	return 0;
}
