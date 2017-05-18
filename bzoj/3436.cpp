// Problem Name: 小K的农场
// Source: Kpmcup#0 By Greens

#include <cstdio>
#include <cstdlib>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
	bool vis;
}V[10010];

struct edge
{
	int endp, next, w;
}E[20010];

int n, m, ec = 1;
bool ins[10010];

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void init_single_source(int s)
{
	for (int i = 1; i <= n; i++)
	{
		V[i].dis = INF;
	}
	V[s].dis = 0;
}

void dfs(int u)
{
	if (ins[u] == true)
	{
		printf("No\n");
		exit(0);
	}
	V[u].vis = true;
	ins[u] = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		int newdis = V[u].dis + E[cur].w;
		if (newdis < V[E[cur].endp].dis)
		{
			V[E[cur].endp].dis = newdis;
			dfs(E[cur].endp);
		}
	}
	ins[u] = false;
}

int main()
{
	scanf("%d%d", &n, &m);
	int op, a, b, c;
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d%d", &a, &b, &c);
			add_edge(a, b, -c);
		}
		else if (op == 2)
		{
			scanf("%d%d%d", &a, &b, &c);
			add_edge(b, a, c);
		}
		else
		{
			scanf("%d%d", &a, &b);
			add_edge(a, b, 0);
			add_edge(b, a, 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].vis == false)
		{
			init_single_source(i);
			dfs(i);
		}
	}
	printf("Yes\n");
	return 0;
}
