#include <cstdio>
#include <cstring>

#define INF 1000000000
#define SOURCE 205
#define SINK 206
#define VERTEX_COUNT 210
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first, dis, in, out;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, lower, upper, flow;
}E[EDGE_COUNT];

int ivc, iec, ec = 2, gap[VERTEX_COUNT], src, sink;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	ivc += 2;
	gap[0] = ivc;
}

void add_edge(int u, int v, int lower, int upper, int flow)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].lower = lower;
	E[ec].upper = upper;
	E[ec].flow = flow;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].lower = lower;
	E[ec].upper = upper;
	E[ec].flow = 0;
	ec++;
}

int isap(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	int totalf = 0, mindis = ivc;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(E[cur].flow, curf - totalf));
				totalf += f;
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0) V[src].dis = ivc;
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < ivc)
	{
		res += isap(src, INF);
	}
	return res;
}

int main()
{
	int g;
	int u, v, lower, upper;
	scanf("%d", &g);
	while (g--)
	{
		memset(V, 0, sizeof(V));
		memset(E, 0, sizeof(E));
		memset(gap, 0, sizeof(gap));
		ec = 2;
		scanf("%d%d", &ivc, &iec);
		for (int i = 0; i < iec; i++)
		{
			scanf("%d%d%d%d", &u, &v, &lower, &upper);
			add_edge(u, v, lower, upper, upper - lower);
			V[u].out += lower;
			V[v].in += lower;
		}
		src = SOURCE;
		sink = SINK;
		for (int i = 1; i <= ivc; i++)
		{
			int m = V[i].out - V[i].in;
			if (m >= 0) add_edge(i, sink, m, 0, m);
			else add_edge(src, i, -m, 0, -m);
		}
		init();
		max_flow();
		for (int cur = V[src].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur ^ 1].flow < E[cur].lower)
			{
				printf("NO\n");
				goto CASEEND;
			}
		}
		for (int cur = V[sink].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow < E[cur].lower)
			{
				printf("NO\n");
				goto CASEEND;
			}
		}
		printf("YES\n");
		for (int i = 3; i <= iec * 2 + 1; i += 2)
		{
			printf("%d\n", E[i].flow + E[i].lower);
		}
	CASEEND:
		printf("\n");
	}
	return 0;
}
