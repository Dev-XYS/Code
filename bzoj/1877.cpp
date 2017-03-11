// Problem Name: 晨跑
// Source: [SDOI2009]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1e9

using namespace std;

struct vertex
{
	int first, dis, pre;
}V[410];

struct edge
{
	int endp, next, flow, w;
}E[40410];

int ivc, iec, k, ec = 2, ansflow, anscost;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v, int f, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].w = w;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].flow = 0;
	E[ec].w = -w;
	ec++;
}

void init_single_source(int src, int sink)
{
	for (int i = 1; i <= ivc * 2; i++)
	{
		V[i].dis = INF;
	}
	V[src].dis = 0;
}

bool spfa(int src, int sink)
{
	queue<int> Q;
	static bool inq[410];
	memset(inq, false, sizeof(inq));
	init_single_source(src, sink);
	Q.push(src), inq[src] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow > 0)
			{
				int newdis = V[u].dis + E[cur].w;
				if (newdis < V[E[cur].endp].dis)
				{
					V[E[cur].endp].dis = newdis;
					V[E[cur].endp].pre = cur;
					if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
				}
			}
		}
	}
	return V[sink].dis < INF;
}

void min_cost_max_flow(int src, int sink)
{
	while (spfa(src, sink) == true)
	{
		int flow = INF, cost = 0, u = sink;
		while (u != src)
		{
			flow = min(flow, E[V[u].pre].flow);
			u = E[V[u].pre ^ 1].endp;
		}
		u = sink;
		while (u != src)
		{
			cost += E[V[u].pre].w;
			E[V[u].pre].flow -= flow;
			E[V[u].pre ^ 1].flow += flow;
			u = E[V[u].pre ^ 1].endp;
		}
		ansflow += flow;
		anscost += flow * cost;
	}
}

int main()
{
	int u, v, w;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u + ivc, v, 1, w);
	}
	for (int i = 1; i <= ivc; i++)
	{
		add_edge(i, i + ivc, 1, 0);
	}
	min_cost_max_flow(1 + ivc, ivc);
	printf("%d %d", ansflow, anscost);
	return 0;
}
