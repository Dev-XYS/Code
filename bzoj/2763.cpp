// Problem Name: 飞行路线
// Source: [JLOI2011]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis[11];
}V[10010];

struct edge
{
	int endp, next, c;
}E[100010];

struct queue_node
{
	int u, k;
	queue_node(int _u, int _k) : u(_u), k(_k) { }
};

int n, m, k, s, t, ec = 2;

inline void add_edge(int u, int v, int c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].c = c;
	ec++;
}

void init_single_source()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			V[i].dis[j] = INF;
		}
	}
	for (int j = 0; j <= k; j++)
	{
		V[s].dis[j] = 0;
	}
}

void spfa()
{
	init_single_source();
	queue<queue_node> Q;
	static bool inq[10010][11];
	memset(inq, 0, sizeof(inq));
	for (int i = 0; i <= k; i++)
	{
		Q.push(queue_node(s, i));
		inq[s][i] = true;
	}
	while (!Q.empty())
	{
		queue_node u = Q.front();
		Q.pop(), inq[u.u][u.k] = false;
		for (int cur = V[u.u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u.u].dis[u.k] + E[cur].c;
			if (newdis < V[E[cur].endp].dis[u.k])
			{
				V[E[cur].endp].dis[u.k] = newdis;
				if (inq[E[cur].endp][u.k] == false) Q.push(queue_node(E[cur].endp, u.k)), inq[E[cur].endp][u.k] = true;
			}
			if (u.k < k && V[u.u].dis[u.k] < V[E[cur].endp].dis[u.k + 1])
			{
				V[E[cur].endp].dis[u.k + 1] = V[u.u].dis[u.k];
				if (inq[E[cur].endp][u.k + 1] == false) Q.push(queue_node(E[cur].endp, u.k + 1)), inq[E[cur].endp][u.k + 1] = true;
			}
		}
	}
}

int main()
{
	int u, v, c;
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, c);
		add_edge(v, u, c);
	}
	spfa();
	int ans = INF;
	for (int i = 0; i <= k; i++)
	{
		if (V[t].dis[i] < ans) ans = V[t].dis[i];
	}
	printf("%d\n", ans);
	return 0;
}
