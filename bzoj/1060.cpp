// Problem Name: 时态同步
// Source: [ZJOI2007]

#include <cstdio>

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
	ll maxdis;
}V[500010];

struct edge
{
	int endp, next, w;
}E[1000010];

int n, s, ec = 2;
ll ans;

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

inline void check_max(ll &x, ll y)
{
	if (y > x) x = y;
}

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void dfs(int u, int fa)
{
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			dfs(E[cur].endp, u);
			check_max(V[u].maxdis, V[E[cur].endp].maxdis + E[cur].w);
		}
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			ans += V[u].maxdis - V[E[cur].endp].maxdis - E[cur].w;
		}
	}
}

int main()
{
	scanf("%d%d", &n, &s);
	int u, v, w;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs(s, 0);
	printf("%lld\n", ans);
	return 0;
}
