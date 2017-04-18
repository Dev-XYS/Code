// Problem Name: 人员雇佣 employ
// Source: [2009国家集训队]
// Problem Author: 林衍凯

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 10000000000000000LL

typedef long long ll;

using namespace std;

struct vertex
{
	int first, dis;
	bool vis;
}V[1010];

struct edge
{
	int endp, next;
	ll flow;
}E[2004010];

const int src = 1005, sink = 1006;
int n, k, ec = 2;

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
	static bool vis[2010];
	memset(vis, 0, sizeof(vis));
	Q.push(sink), vis[sink] = true;
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

int main()
{
	int a;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		add_edge(i, sink, a);
	}
	int e;
	ll total = 0;
	for (int i = 1; i <= n; i++)
	{
		ll sum = 0;
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &e);
			add_edge(i, j, (ll)e * 2);
			sum += e;
		}
		add_edge(src, i, sum);
		total += sum;
	}
	printf("%lld\n", total - dinic());
	return 0;
}
