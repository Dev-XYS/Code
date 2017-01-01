#include <cstdio>

using namespace std;

struct vertex
{
	int first, dfn, low, col;
}V[10010];

struct edge
{
	int endp, next;
}E[100010];

int ivc, iec, ec = 1, dfn = 1, col = 1, S[10010], ins[10010], sp = 0, cnt[10010], odeg[10010];

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

void DFS(int u)
{
	S[sp++] = u;
	ins[u] = true;
	V[u].dfn = V[u].low = dfn++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp);
		}
		if (ins[E[cur].endp] == true)
		{
			V[u].low = min(V[u].low, V[E[cur].endp].low);
		}
	}
	if (V[u].low == V[u].dfn)
	{
		int v;
		do
		{
			v = S[--sp];
			ins[v] = false;
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
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].dfn == 0)
		{
			DFS(i);
		}
	}
	for (int i = 1; i <= ivc; i++)
	{
		cnt[V[i].col]++;
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
	int anscol = 0;
	for (int i = 1; i < col; i++)
	{
		if (odeg[i] == 0)
		{
			if (anscol == 0)
			{
				anscol = i;
			}
			else
			{
				printf("0");
				return 0;
			}
		}
	}
	printf("%d", cnt[anscol]);
	return 0;
}
