// Problem Name: [ZJOI2010] 网络扩容 network

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1e9

using namespace std;

struct vertex
{
	int first, dis, pre;
}V[1010];

struct edge
{
	int endp, next, flow, w;
}E[20010];

int ivc, iec, k, ec = 2, _sink;

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

bool bfs(int src, int sink)
{
	queue<int> Q;
	static bool inq[1010];
	memset(inq, false, sizeof(inq));
	Q.push(sink), inq[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (inq[E[cur].endp] == false && E[cur].w == 0 && E[cur ^ 1].flow > 0)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
	return inq[src] == true;
}

int dfs(int u, int curf)
{
	if (u == _sink) return curf;
	int totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].w == 0 && E[cur].flow > 0)
		{
			int f = dfs(E[cur].endp, min(curf - totalf, E[cur].flow));
			E[cur].flow -= f;
			E[cur ^ 1].flow += f;
			totalf += f;
		}
	}
	return totalf;
}

int max_flow(int src, int sink)
{
	int res = 0;
	_sink = sink;
	while (bfs(src, sink) == true)
	{
		int f;
		do
		{
			f = dfs(src, INF);
			res += f;
		} while (f > 0);
	}
	return res;
}

void init_single_source(int src, int sink)
{
	for (int i = 1; i <= ivc; i++)
	{
		V[i].dis = INF;
	}
	V[sink].dis = INF;
	V[src].dis = 0;
}

bool spfa(int src, int sink)
{
	queue<int> Q;
	static bool inq[1010];
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

int min_cost_max_flow(int src, int sink)
{
	int res = 0;
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
		res += flow * cost;
	}
	return res;
}

int main()
{
	const int src = 1005, sink = 1006;
	int u, v, f, w;
	scanf("%d%d%d", &ivc, &iec, &k);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d%d", &u, &v, &f, &w);
		add_edge(u, v, f, 0);
		add_edge(u, v, INF, w);
	}
	add_edge(src, 1, k, 0);
	add_edge(ivc, sink, k, 0);
	int mf = max_flow(1, ivc);
	int mcmf = min_cost_max_flow(src, sink);
	printf("%d %d", mf, mcmf);
	return 0;
}
