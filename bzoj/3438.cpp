// Problem Name: 小M的作物
// Source: Kpmcup#0 By Greens

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 10000000000000000LL

typedef long long ll;

using namespace std;

struct vertex
{
	int first, dis;
}V[3010];

struct edge
{
	int endp, next;
	ll flow;
}E[4008010];

const int src = 3005, sink = 3006;
int n, m, ec = 2;

inline ll min(ll x, ll y)
{
	return x < y ? x : y;
}

inline void _add_edge(int u, int v, ll f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void add_edge(int u, int v, ll f)
{
	_add_edge(u, v, f);
	_add_edge(v, u, 0);
}

bool bfs()
{
	queue<int> Q;
	static bool vis[3010];
	memset(vis, 0, sizeof(vis));
	V[sink].dis = 0, Q.push(sink), vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (vis[E[cur].endp] == false && E[cur ^ 1].flow > 0)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), vis[E[cur].endp] = true;;
			}
		}
	}
	return vis[src];
}

int dfs(int u, ll curf)
{
	if (u == sink) return curf;
	ll totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].flow > 0)
		{
			int f = dfs(E[cur].endp, min(E[cur].flow, curf - totalf));
			E[cur].flow -= f;
			E[cur ^ 1].flow += f;
			totalf += f;
		}
	}
	return totalf;
}

ll dinic()
{
	ll res = 0;
	while (bfs() == true)
	{
		ll f;
		do
		{
			f = dfs(src, INF);
			res += f;
		} while (f > 0);
	}
	return res;
}

/* Algorithm ISAP begins */
/* Author : Dev-XYS */

int gap[3010];

ll isap(int u, ll curf)
{
	if (u == sink) return curf;
	ll totalf = 0;
	int mindis = n + m * 2 + 2;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[E[cur].endp].dis + 1 == V[u].dis)
			{
				int f = isap(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
			if (V[E[cur].endp].dis < mindis) mindis = V[E[cur].endp].dis;
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0)
		{
			V[src].dis = n + m * 2 + 2;
			return 0;
		}
		gap[V[u].dis = mindis + 1]++;
	}
	return totalf;
}

ll max_flow()
{
	gap[0] = n + m * 2 + 2;
	ll res = 0;
	while (V[src].dis < n + m * 2 + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

/* Algorithm ISAP ends */

int main()
{
	ll total = 0;
	int x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		add_edge(src, i, x);
		total += x;
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		add_edge(i, sink, x);
		total += x;
	}
	int k;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &k);
		scanf("%d", &x);
		add_edge(src, i + n, x);
		total += x;
		scanf("%d", &x);
		add_edge(i + n + m, sink, x);
		total += x;
		for (int j = 0; j < k; j++)
		{
			scanf("%d", &x);
			add_edge(i + n, x, INF);
			add_edge(x, i + n + m, INF);
		}
	}
	printf("%lld\n", total - max_flow());
	return 0;
}
