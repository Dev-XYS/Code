#include <cstdio>

using namespace std;

struct vertex
{
	int first, dfn, low, col;
}V[5010];

struct edge
{
	int endp, next;
}E[20010];

int ivc, iec, ec = 2, dfn = 1, col = 1, S[5010], ins[5010], sp = 0, deg[5010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u, int fae)
{
	S[sp++] = u;
	V[u].dfn = V[u].low = dfn++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (cur != (fae ^ 1))
		{
			if (V[E[cur].endp].dfn == 0)
			{
				DFS(E[cur].endp, cur);
				V[u].low = min(V[u].low, V[E[cur].endp].low);
			}
			else
			{
				V[u].low = min(V[u].low, V[E[cur].endp].dfn);
			}
		}
	}
	if (V[u].low == V[u].dfn)
	{
		int v;
		do
		{
			v = S[--sp];
			V[v].col = col;
		} while (v != u);
		col++;
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
		add_edge(v, u);
	}
	DFS(1, 0);
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].col != V[E[cur].endp].col)
			{
				deg[V[i].col]++;
				deg[V[E[cur].endp].col]++;
			}
		}
	}
	int leaf = 0;
	for (int i = 1; i < col; i++)
	{
		if (deg[i] == 2)
		{
			leaf++;
		}
	}
	printf("%d", (leaf + 1) / 2);
	return 0;
}
