#include <cstdio>

using namespace std;

struct vertex
{
	int first, deg, ideg, odeg;
	bool vis;
}V[100010];

struct edge
{
	int endp, next, ord;
	bool dir, vis;
}E[400010];

int t, ivc, iec, ec = 2, S[200010], sp;

inline void add_edge(int u, int v, int ord, bool dir)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].ord = ord;
	E[ec].dir = dir;
	ec++;
}

void dfs_b(int u)
{
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].vis == false) dfs_b(E[cur].endp);
		E[cur].vis = E[cur ^ 1].vis = true;
	}
}

void f_dfs_b(int u)
{
	while (V[u].first != 0)
	{
		int cur = V[u].first;
		V[u].first = E[cur].next;
		if (E[cur].vis == true) continue;
		E[cur ^ 1].vis = true, f_dfs_b(E[cur].endp), S[sp++] = (E[cur].dir == true ? E[cur].ord : -E[cur].ord);
	}
}

void dfs_d(int u)
{
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].vis == false) dfs_d(E[cur].endp);
		E[cur].vis = true;
	}
}

void f_dfs_d(int u)
{
	while (V[u].first != 0)
	{
		int cur = V[u].first;
		V[u].first = E[cur].next;
		f_dfs_d(E[cur].endp), S[sp++] = E[cur].ord;
	}
}

int main()
{
	int u, v;
	scanf("%d%d%d", &t, &ivc, &iec);
	if (t == 1)
	{
		for (int i = 1; i <= iec; i++)
		{
			scanf("%d%d", &u, &v);
			add_edge(u, v, i, true);
			add_edge(v, u, i, false);
			V[u].deg++;
			V[v].deg++;
		}
		int start = 0;
		for (int i = 1; i <= ivc; i++)
		{
			if ((V[i].deg & 1) != 0)
			{
				printf("NO\n");
				return 0;
			}
			if (V[i].deg > 0)
			{
				start = i;
				dfs_b(i);
				break;
			}
		}
		for (int i = 1; i <= ivc; i++)
		{
			for (int cur = V[i].first; cur != 0; cur = E[cur].next)
			{
				if (E[cur].vis == false)
				{
					printf("NO\n");
					return 0;
				}
			}
		}
		for (int i = 2; i < 2 + iec * 2; i++)
		{
			E[i].vis = false;
		}
		f_dfs_b(start);
		printf("YES\n");
		for (int i = sp - 1; i >= 0; i--)
		{
			printf("%d ", S[i]);
		}
	}
	else
	{
		for (int i = 1; i <= iec; i++)
		{
			scanf("%d%d", &u, &v);
			add_edge(u, v, i, true);
			V[u].odeg++;
			V[v].ideg++;
		}
		int start = 0;
		for (int i = 1; i <= ivc; i++)
		{
			if (V[i].ideg != V[i].odeg)
			{
				printf("NO\n");
				return 0;
			}
			if (V[i].ideg > 0 || V[i].odeg > 0)
			{
				start = i;
				dfs_d(i);
				break;
			}
		}
		for (int i = 1; i <= ivc; i++)
		{
			for (int cur = V[i].first; cur != 0; cur = E[cur].next)
			{
				if (E[cur].vis == false)
				{
					printf("NO\n");
					return 0;
				}
			}
		}
		f_dfs_d(start);
		printf("YES\n");
		for (int i = sp - 1; i >= 0; i--)
		{
			printf("%d ", S[i]);
		}
	}
	return 0;
}
