// Problem Name: 支线剧情
// Source: [AHOI2014]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, isum, osum, dis, pre;
}V[310];

struct edge
{
	int endp, next, flow, cost;
}E[11210];

const int end = 304, src = 305, sink = 306;
int n, ec = 2;

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
{//printf("edge : %d -> %d, flow = %d, cost = %d\n", u, v, f, c);
	_add_edge(u, v, f, c);
	_add_edge(v, u, 0, -c);
}

void init_single_source()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].dis = INF;
	}
	V[end].dis = INF;
	V[sink].dis = INF;
}

bool spfa()
{//printf("spfa->\n");
	init_single_source();
	queue<int> Q;
	static bool inq[310];
	memset(inq, 0, sizeof(inq));
	Q.push(src), inq[src] = true;
	while (!Q.empty())
	{
		int u = Q.front();//printf("d[%d] = %d\n", u, V[u].dis);
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow > 0)
			{
				int newdis = V[u].dis + E[cur].cost;
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

int min_cost_max_flow()
{
	int res = 0;
	while (spfa() == true)
	{//printf("while (spfa())\n");
		int flow = INF;
		for (int u = sink; u != src; u = E[V[u].pre ^ 1].endp)
		{
			if (E[V[u].pre].flow < flow) flow = E[V[u].pre].flow;
		}
		for (int u = sink; u != src; u = E[V[u].pre ^ 1].endp)
		{
			res += E[V[u].pre].cost * flow;
			E[V[u].pre].flow -= flow;
			E[V[u].pre ^ 1].flow += flow;
		}
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	int k, u, t, ans = 0;
	for (int i = 1; i <= n; i++)
	{//printf("i = %d\n", i);
		scanf("%d", &k);
		while (k--)
		{
			scanf("%d%d", &u, &t);
			add_edge(i, u, INF, t);
			V[i].osum++;
			V[u].isum++;
			ans += t;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].isum - V[i].osum > 0)
		{
			add_edge(src, i, V[i].isum - V[i].osum, 0);
		}
		else if (V[i].osum - V[i].isum > 0)
		{
			add_edge(i, sink, V[i].osum - V[i].isum, 0);
		}
		add_edge(i, end, INF, 0);
	}
	add_edge(end, 1, INF, 0);
	printf("%d\n", ans + min_cost_max_flow());
	return 0;
}
