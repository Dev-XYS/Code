// Problem Name: Xor
// Source: [WC2011]

#include <cstdio>

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
	bool vis;
	ll s;
}V[50010];

struct edge
{
	int endp, next;
	ll w;
}E[200010];

int ivc, iec, ec = 2, cc;
ll cycle[200010], base[100];

inline void add_edge(int u, int v, ll w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void dfs(int u)
{
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].vis == false) V[E[cur].endp].s = V[u].s ^ E[cur].w, dfs(E[cur].endp);
		else cycle[cc++] = V[u].s ^ E[cur].w ^ V[E[cur].endp].s;
	}
}

void linear_basis()
{
	for (int i = 0; i < cc; i++)
	{
		for (int j = 62; j >= 0 && cycle[i] != 0; j--)
		{
			if ((cycle[i] & (1LL << j)) != 0)
			{
				if (base[j] == 0) base[j] = cycle[i];
				cycle[i] ^= base[j];
			}
		}
	}
}

int main()
{
	int u, v;
	ll w;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%lld", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs(1);
	linear_basis();
	ll path = V[ivc].s;
	for (int i = 62; i >= 0; i--)
	{
		if ((path ^ base[i]) > path) path ^= base[i];
	}
	printf("%lld", path);
	return 0;
}
