// Problem Name: 订货
// Source: [HAOI2010]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis, u, d, pre;
}V[60];

struct edge
{
	int endp, next, flow, cost;
}E[320];

const int src = 55, sink = 56;
int n, m, S, ec = 2;

inline void _add_edge(int u, int v, int f, int c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].cost = c;
	ec++;
}

inline void add_edge(int u, int v, int f, int c)
{
	_add_edge(u, v, f, c);
	_add_edge(v, u, 0, -c);
}

void build_graph()
{
	for (int i = 1; i < n; i++)
	{
		add_edge(i, i + 1, S, m);
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(src, i, INF, V[i].d);
		add_edge(i, sink, V[i].u, 0);
	}
}

void init_single_source()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].dis = INF;
	}
	V[sink].dis = INF;
}

bool spfa()
{
	init_single_source();
	queue<int> Q;
	static bool inq[60];
	memset(inq, 0, sizeof(inq));
	Q.push(src), inq[src] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow > 0)
			{
				int newdis = V[u].dis + E[cur].cost;
				if (newdis < V[E[cur].endp].dis)
				{
					V[E[cur].endp].dis = newdis, V[E[cur].endp].pre = cur;
					if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
				}
			}
		}
	}
	return V[sink].dis < INF;
}

int max_flow_min_cost()
{
	int res = 0;
	while (spfa() == true)
	{
		int f = INF;
		int u = sink;
		while (u != src)
		{
			if (E[V[u].pre].flow < f) f = E[V[u].pre].flow;
			u = E[V[u].pre ^ 1].endp;
		}
		u = sink;
		while (u != src)
		{
			res += f * E[V[u].pre].cost;
			E[V[u].pre].flow -= f;
			E[V[u].pre ^ 1].flow += f;
			u = E[V[u].pre ^ 1].endp;
		}
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &S);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].u);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].d);
	}
	build_graph();
	printf("%d\n", max_flow_min_cost());
	return 0;
}
