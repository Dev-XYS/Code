// Problem Name: 受欢迎的牛
// Source: [HAOI2006]

#include <cstdio>

using namespace std;

struct vertex
{
	int first, dfn, low, col;
	bool ins;
}V[10010];

struct edge
{
	int endp, next;
}E[50010];

int ivc, iec, ec = 1, dfn, col, S[10010], sp, odeg[10010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u)
{
	S[sp++] = u, V[u].ins = true;
	V[u].dfn = V[u].low = ++dfn;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].ins == false)
		{
			if (V[E[cur].endp].dfn == 0)
			{
				dfs(E[cur].endp);
				if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
			}
		}
		else if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
	}
	if (V[u].low == V[u].dfn)
	{
		col++;
		int v;
		do
		{
			v = S[--sp], V[v].ins = false;
			V[v].col = col;
		} while (v != u);
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].dfn == 0) dfs(i);
	}
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].col != V[E[cur].endp].col)
			{
				odeg[V[i].col]++;
			}
		}
	}
	int cnt = 0, wh = 0;
	for (int i = 1; i <= col; i++)
	{
		if (odeg[i] == 0) cnt++, wh = i;
	}
	if (cnt > 1)
	{
		printf("0\n");
		return 0;
	}
	int ans = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].col == wh) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
