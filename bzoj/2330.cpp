// Problem Name: 糖果
// Source: [SCOI2011]

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

struct vertex
{
	int first, dfn, low, col, cnt;
	bool vis;
}V[100010];

struct edge
{
	int endp, next;
	bool noe;
}E[200010];

struct other_edge
{
	int a, b;
	other_edge(int _a = 0, int _b = 0) : a(_a), b(_b) { }
}O[100010];

int n, m, oc, ec = 1, dfn, col = 1, cnt[100010], S[100010], sp, T[100010], tc;
bool ins[100010];

inline void add_edge(int u, int v, bool noe)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].noe = noe;
	ec++;
}

void dfs(int u)
{
	S[sp++] = u, ins[u] = true;
	V[u].dfn = V[u].low = ++dfn;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			dfs(E[cur].endp);
		}
		else if (ins[E[cur].endp] == false) continue;
		if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
	}
	if (V[u].low == V[u].dfn)
	{
		int v;
		do
		{
			v = S[--sp], ins[v] = false;
			V[v].col = col;
			cnt[col]++;
		} while (v != u);
		col++;
	}
}

void build_graph()
{
	static int a[100010], b[100010];
	int bc = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].col != V[E[cur].endp].col) a[bc] = V[i].col, b[bc] = V[E[cur].endp].col, bc++;
		}
	}
	for (int i = 0; i < oc; i++)
	{
		O[i].a = V[O[i].a].col, O[i].b = V[O[i].b].col;
	}
	memset(V, 0, sizeof(V));
	ec = 1;
	for (int i = 0; i < bc; i++)
	{
		add_edge(a[i], b[i], false);
	}
	for (int i = 0; i < oc; i++)
	{
		add_edge(O[i].a, O[i].b, true);
	}
}

void topo(int u)
{
	S[sp++] = u, ins[u] = true, V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (ins[E[cur].endp] == true) printf("-1"), exit(0);
		if (V[E[cur].endp].vis == false) topo(E[cur].endp);
	}
	T[tc++] = u;
	sp--, ins[u] = false;
}

int main()
{
	int op, a, b;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &op, &a, &b);
		switch (op)
		{
		case 1:
			add_edge(a, b, false);
			add_edge(b, a, false);
			break;
		case 2:
			O[oc++] = other_edge(a, b);
			break;
		case 3:
			add_edge(b, a, false);
			break;
		case 4:
			O[oc++] = other_edge(b, a);
			break;
		case 5:
			add_edge(a, b, false);
			break;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].dfn == 0) dfs(i);
	}
	build_graph();
	sp = 0;
	for (int i = 1; i < col; i++)
	{
		if (V[i].vis == false) topo(i);
	}
	for (int i = tc - 1; i >= 0; i--)
	{
		int u = T[i];
		if (V[u].cnt == 0) V[u].cnt = 1;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].noe == false)
			{
				if (V[u].cnt > V[E[cur].endp].cnt) V[E[cur].endp].cnt = V[u].cnt;
			}
			else
			{
				if (V[u].cnt >= V[E[cur].endp].cnt) V[E[cur].endp].cnt = V[u].cnt + 1;
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i < col; i++)
	{
		ans += (long long)V[i].cnt * (long long)cnt[i];
	}
	printf("%lld", ans);
	return 0;
}
