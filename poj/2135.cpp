#include <cstdio>
#include <queue>

#define INF 1000000000
#define SOURCE 1005
#define SINK 1006
#define VERTEX_COUNT 1010
#define EDGE_COUNT 40010

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow, cost;
}E[EDGE_COUNT];

int ivc, iec, src, sink, ec = 2, ans;
queue<int> Q;
bool inq[VERTEX_COUNT];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	src = SOURCE;
	sink = SINK;
}

void add_edge(int u, int v, int f, int c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].cost = c;
	ec++;
}

void init_single_source()
{
	for (int i = 1; i <= ivc; i++)
	{
		V[i].dis = INF;
	}
	V[sink].dis = INF;
	V[src].dis = 0;
}

bool spfa()
{
	int u;
	init_single_source();
	Q.push(src), inq[src] = true;
	while (!Q.empty())
	{
		u = Q.front(), Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow > 0 && V[u].dis + E[cur].cost < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = V[u].dis + E[cur].cost;
				if (inq[E[cur].endp] == false)
				{
					Q.push(E[cur].endp), inq[E[cur].endp] = true;
				}
			}
		}
	}
	return V[sink].dis < INF;
}
		
int DFS(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (inq[E[cur].endp] == false && E[cur].flow > 0 && V[E[cur].endp].dis == V[u].dis + E[cur].cost)
		{
			inq[E[cur].endp] = true;
			int f = DFS(E[cur].endp, min(curf, E[cur].flow));
			inq[E[cur].endp] = false;
			if (f > 0)
			{
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				ans += E[cur].cost;
				return f;
			}
		}
	}
	return 0;
}

void max_flow()
{
	while (spfa() == true)
	{
		DFS(src, INF);
	}
}

int main()
{
	int u, v, c;
	scanf("%d%d", &ivc, &iec);
	init();
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, 1, c);
		add_edge(v, u, 0, -c);
		add_edge(v, u, 1, c);
		add_edge(u, v, 0, -c);
	}
	add_edge(src, 1, 2, 0);
	add_edge(1, src, 0, 0);
	add_edge(ivc, sink, 2, 0);
	add_edge(sink, ivc, 0, 0);
	max_flow();
	printf("%d", ans);
	return 0;
}
