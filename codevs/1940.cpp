// Problem Name: 海拔
// Source: [NOI2010]

#include <cstdio>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
	bool vis;
}V[250010];

struct edge
{
	int endp, next, w;
}E[1002010];

struct queue_node
{
	int u, dis;
	queue_node(int _u = 0, int _dis = 0) : u(_u), dis(_dis) { }
	inline bool operator < (const queue_node &x) const { return dis > x.dis; }
};

const int src = 250005, sink = 250006;
int n, ec = 1;

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void init_single_source()
{
	for (int i = 1; i <= n * n; i++)
	{
		V[i].dis = INF;
	}
	V[sink].dis = INF;
}

int dijkstra()
{
	init_single_source();
	priority_queue<queue_node> Q;
	Q.push(src);
	while (true)
	{
		queue_node u = Q.top();
		Q.pop();
		if (V[u.u].vis == true) continue;
		if (u.u == sink) break;
		V[u.u].vis = true;
		for (int cur = V[u.u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u.u].dis + E[cur].w;
			if (newdis < V[E[cur].endp].dis) V[E[cur].endp].dis = newdis, Q.push(queue_node(E[cur].endp, V[E[cur].endp].dis));
		}
	}
	return V[sink].dis;
}

inline int id(int i, int j)
{
	return i * n + j;
}

int main()
{
	scanf("%d", &n);
	int f;
	for (int j = 1; j <= n; j++)
	{
		scanf("%d", &f);
		add_edge(id(0, j), sink, f);
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &f);
			add_edge(id(i, j), id(i - 1, j), f);
		}
	}
	for (int j = 1; j <= n; j++)
	{
		scanf("%d", &f);
		add_edge(src, id(n - 1, j), f);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &f);
		add_edge(src, id(i, 1), f);
		for (int j = 1; j < n; j++)
		{
			scanf("%d", &f);
			add_edge(id(i, j), id(i, j + 1), f);
		}
		scanf("%d", &f);
		add_edge(id(i, n), sink, f);
	}
	for (int j = 1; j <= n; j++)
	{
		scanf("%d", &f);
		add_edge(sink, id(0, j), f);
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &f);
			add_edge(id(i - 1, j), id(i, j), f);
		}
	}
	for (int j = 1; j <= n; j++)
	{
		scanf("%d", &f);
		add_edge(id(n - 1, j), src, f);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &f);
		add_edge(id(i, 1), src, f);
		for (int j = 1; j < n; j++)
		{
			scanf("%d", &f);
			add_edge(id(i, j + 1), id(i, j), f);
		}
		scanf("%d", &f);
		add_edge(sink, id(i, n), f);
	}
	printf("%d\n", dijkstra());
	return 0;
}
