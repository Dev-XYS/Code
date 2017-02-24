// Problem Name: Firing

#include <cstdio>

#define INFL 10000000000000000

typedef long long ll;

using namespace std;

struct vertex
{
	int first, dis, w;
	bool vis;
}V[5010];

struct edge
{
	int endp, next;
	ll f;
}E[140010];

const int src = 5005, sink = 5006;
int ivc, iec, ec = 2, gap[5010];

inline int min(ll x, ll y)
{
	return x < y ? x : y;
}

void init()
{
	gap[0] = ivc + 2;
}

void add_edge(int u, int v, ll f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].f = f;
	ec++;
}

ll isap(int u, ll curf)
{
	if (u == sink) return curf;
	ll totalf = 0;
	int mindis = ivc + 2;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].f > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(E[cur].f, curf - totalf));
				E[cur].f -= f;
				E[cur ^ 1].f += f;
				totalf += f;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		if (--gap[V[u].dis] == 0) V[src].dis = ivc + 2;
		gap[V[u].dis = mindis + 1]++;
	}
	return totalf;
}

ll max_flow()
{
	ll res = 0;
	while (V[src].dis < ivc + 2)
	{
		res += isap(src, INFL);
	}
	return res;
}

void dfs(int u)
{
	if (V[u].vis == false)
	{
		V[u].vis = true;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].f > 0)
			{
				dfs(E[cur].endp);
			}
		}
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &iec);
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%d", &V[i].w);
	}
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v, INFL);
		add_edge(v, u, 0);
	}
	ll posw = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].w >= 0)
		{
			add_edge(src, i, V[i].w);
			add_edge(i, src, 0);
			posw += V[i].w;
		}
		else
		{
			add_edge(i, sink, -V[i].w);
			add_edge(sink, i, 0);
		}
	}
	init();
	ll cut = max_flow();
	dfs(src);
	int cnt = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].vis == true) cnt++;
	}
	printf("%d %lld", cnt, posw - cut);
	return 0;
}
