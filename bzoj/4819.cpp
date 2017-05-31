// Problem Name: 新生舞会
// Source: [SDOI2017]

#include <cstdio>
#include <cstring>
#include <queue>

#define INFF 1e10
#define INF 1000000000

using namespace std;

struct vertex
{
	int first, pre;
	double dis;
}V[210];

struct edge
{
	int endp, next, flow;
	double cost;
}E[20410];

const int src = 205, sink = 206;
int n, ec = 2, A[105][105], B[105][105];

inline void _add_empty_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

inline void add_empty_edge(int u, int v)
{
	_add_empty_edge(u, v);
	_add_empty_edge(v, u);
}

inline void _add_edge(int u, int v, int f, double c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].cost = c;
	ec++;
}

inline void add_edge(int u, int v, int f, double c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].cost = c;
	ec++;
	
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].flow = 0;
	E[ec].cost = -c;
	ec++;
}

void init_single_source()
{
	for (int i = n * 2; i >= 1; i--)
	{
		V[i].dis = -INFF;
	}
	V[sink].dis = -INFF;
	V[sink].pre = 0;
}

bool spfa()
{
	init_single_source();
	queue<int> Q;
	static bool inq[210];
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
				double newdis = V[u].dis + E[cur].cost;
				if (newdis > V[E[cur].endp].dis)
				{
					V[E[cur].endp].dis = newdis;
					V[E[cur].endp].pre = cur;
					if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
				}
			}
		}
	}
	return V[sink].pre != 0;
}

double max_cost_max_flow()
{
	double res = 0;
	while (spfa() == true)
	{
		int flow = INF;
		for (int u = sink; u != src; u = E[V[u].pre ^ 1].endp)
		{
			if (E[V[u].pre].flow < flow) flow = E[V[u].pre].flow;
		}
		for (int u = sink; u != src; u = E[V[u].pre ^ 1].endp)
		{
			E[V[u].pre].flow -= flow;
			E[V[u].pre ^ 1].flow += flow;
		}
		res += V[sink].dis * flow;
	}
	return res;
}

void fill(double C)
{
	int p = 2;
	for (int i = 1; i <= n; i++, p += 2)
	{
		E[p].flow = 1;
		E[p + 1].flow = 0;
		p += 2;
		E[p].flow = 1;
		E[p + 1].flow = 0;
	}
	for (int i = 1; i <= n; i++)
	{
  		for (int j = 1; j <= n; j++, p += 2)
		{
			E[p].flow = 1;
			E[p + 1].flow = 0;
			E[p].cost = (double)A[i][j] - (double)B[i][j] * C;
			E[p + 1].cost = -E[p].cost;
		}
	}
}

void build_graph(double C)
{
	ec = 2;
	for (int i = n * 2; i >= 1; i--)
	{
		V[i].first = 0;
	}
	V[src].first = V[sink].first = 0;
	for (int i = 1; i <= n; i++)
	{
		add_edge(src, i, 1, 0);
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(i + n, sink, 1, 0);
	}
	for (int i = 1; i <= n; i++)
	{
  		for (int j = 1; j <= n; j++)
		{
			add_edge(i, j + n, 1, (double)A[i][j] - B[i][j] * C);
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &A[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &B[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_empty_edge(src, i);
		add_empty_edge(i + n, sink);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			add_empty_edge(i, j + n);
		}
	}
	double l = 0, r = 10000;
	while (r - l >= 1e-7)
	{
		double mid = (l + r) / 2;
		fill(mid);
		//build_graph(mid);
		if (max_cost_max_flow() >= 0) l = mid;
		else r = mid;
	}
	printf("%.6lf\n", l);
	return 0;
}
