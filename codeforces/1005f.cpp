// Problem Name: Berland and the Shortest Paths
// Source: Codeforces Round #496 (Div. 3), Problem F

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct vertex
{
	int first, dis;
}V[200010];

struct edge
{
	int next, endp, id;
}E[400010];

int n, m, k, t;
char *ans[200010];

inline void add_edge(int u, int v, int id)
{
	static int ec = 1;
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].id = id;
	ec++;
}

void bfs()
{
	queue<int> Q;
	V[1].dis = 1;
	Q.push(1);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].dis == 0)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp);
			}
		}
	}
}

void init_ans()
{
	ans[++t] = new char[m + 1];
	memcpy(ans[t], ans[t - 1], m + 1);
}

void init()
{
	ans[0] = new char[m + 1];
	for (int i = 0; i < m; i++)
	{
		ans[0][i] = '0';
	}
	ans[0][m] = 0;
	init_ans();
}

void dfs(int u)
{
	if (u > n)
	{
		init_ans();
		return;
	}
	for (int cur = V[u].first; cur != 0 && t <= k; cur = E[cur].next)
	{
		if (V[E[cur].endp].dis == V[u].dis - 1)
		{
			ans[t][E[cur].id] = '1';
			dfs(u + 1);
			ans[t][E[cur].id] = '0';
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v, i);
		add_edge(v, u, i);
	}
	bfs();
	init();
	dfs(2);
	printf("%d\n", t - 1);
	for (int i = 1; i < t; i++)
	{
		printf("%s\n", ans[i]);
	}
	return 0;
}
