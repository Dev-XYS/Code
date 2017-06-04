// Problem Name: 食物链
// Source: [HAOI2016]

#include <cstdio>

using namespace std;

struct vertex
{
	int first, ideg, odeg, cnt;
}V[100010];

struct edge
{
	int endp, next;
}E[200010];

int n, m, ec = 1;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u)
{
	if (V[u].odeg == 0)
	{
		V[u].cnt = 1;
		return;
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].cnt == 0)
		{
			dfs(E[cur].endp);
		}
		V[u].cnt += V[E[cur].endp].cnt;
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
		V[u].odeg++;
		V[v].ideg++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].cnt == 0)
		{
			dfs(i);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (V[i].ideg == 0 && V[i].odeg > 0)
		{
			ans += V[i].cnt;
		}
	}
	printf("%d\n", ans);
	return 0;
}
