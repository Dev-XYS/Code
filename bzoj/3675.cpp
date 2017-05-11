// Problem Name: Atm
// Source: [APIO2014]

#include <cstdio>
#include <queue>

using namespace std;

struct vertex
{
	int first, w, dfn, low, col, dis;
	bool hasbar;
}V[500010];

struct edge
{
	int endp, next;
}E[500010];

struct raw_edge
{
	int u, v;
	raw_edge(int _u = 0, int _v = 0) : u(_u), v(_v) { }
}R[500010];

int n, m, s, p, ec = 1, dfn, col, S[500010], sp, cash[500010];
bool ins[500010], hasbar[500010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void init_graph()
{
	for (int i = 1; i <= col; i++)
	{
		V[i].first = 0;
	}
	ec = 1;
}

void dfs(int u)
{
	S[sp++] = u, ins[u] = true;
	V[u].low = V[u].dfn = ++dfn;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			dfs(E[cur].endp);
			if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
		}
		else if (ins[E[cur].endp] == true)
		{
			if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
		}
	}
	if (V[u].low == V[u].dfn)
	{
		col++;
		int v;
		do
		{
			v = S[--sp], ins[v] = false;
			V[v].col = col;
			if (V[v].hasbar == true) hasbar[col] = true;
			cash[col] += V[v].w;
		} while (v != u);
	}
}

void spfa()
{
	queue<int> Q;
	static bool inq[500010];
	V[V[s].col].dis = cash[V[s].col];
	Q.push(V[s].col), inq[V[s].col] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u].dis + cash[E[cur].endp];
			if (newdis > V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newdis;
				if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].w);
	}
	scanf("%d%d", &s, &p);
	for (int i = 0; i < p; i++)
	{
		scanf("%d", &u);
		V[u].hasbar = true;
	}
	dfs(s);
	int rec = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].col != V[E[cur].endp].col) R[rec++] = raw_edge(V[i].col, V[E[cur].endp].col);
		}
	}
	init_graph();
	for (int i = 0; i < rec; i++)
	{
		add_edge(R[i].u, R[i].v);
	}
	spfa();
	int ans = 0;
	for (int i = 1; i <= col; i++)
	{
		if (hasbar[i] == true && V[i].dis > ans) ans = V[i].dis;
	}
	printf("%d\n", ans);
	return 0;
}
