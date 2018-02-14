// Problem Name: Almost Acyclic Graph
// Source: Educational Codeforces Round 36, Problem D

#include <cstdio>

using namespace std;

struct vertex
{
	int first;
	bool vis, ins;
}V[510];

struct edge
{
	int endp, next;
	bool del;
}E[100010];

int n, m, ec = 1, S[510], sp = 1, s, cycs, cyc[510];
bool cyclic;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u)
{
	V[u].vis = true;
	V[u].ins = true;
	for (int cur = V[u].first; cur != 0 && cyclic == false; cur = E[cur].next)
	{
		if (E[cur].del == false)
		{
			if (V[E[cur].endp].ins == true)
			{
				cyclic = true;
				S[sp] = cur;
				s = E[cur].endp;
			}
			else if (V[E[cur].endp].vis == false)
			{
				S[sp++] = cur;
				dfs(E[cur].endp);
				sp--;
			}
		}
	}
	V[u].ins = false;
}

bool is_cyclic()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].vis = false;
	}
	cyclic = false;
	for (int i = 1; i <= n && cyclic == false; i++)
	{
		if (V[i].vis == false)
		{
			E[0].endp = i;
			dfs(i);
		}
	}
	return cyclic;
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
	if (is_cyclic() == false)
	{
		printf("YES\n");
		return 0;
	}
	else
	{
		cycs = s;
		for (int i = 0; i <= n; i++)
		{
			cyc[i] = S[i];
		}
		int i;
		for (i = 0; ; i++)
		{
			if (E[cyc[i]].endp == cycs)
			{
				break;
			}
		}
		do
		{
			i++;
			E[cyc[i]].del = true;
			if (is_cyclic() == false)
			{
				printf("YES\n");
				return 0;
			}
			E[cyc[i]].del = false;
		} while (E[cyc[i]].endp != cycs);
	}
	printf("NO\n");
	return 0;
}
