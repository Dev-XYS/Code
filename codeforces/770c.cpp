// Problem Name: Online Courses In BSU
// Source: VK Cup 2017 - Qualification 2

#include <cstdio>
#include <cstdlib>

using namespace std;

struct vertex
{
	int first;
	bool vis;
}V[100010];

struct edge
{
	int endp, next;
}E[100010];

int n, k, d[100010], ec = 2, study[100010], sc = 0;
bool ins[100010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u)
{
	if (ins[u] == true) printf("-1\n"), exit(0);
	if (V[u].vis == true) return;
	ins[u] = true;
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		dfs(E[cur].endp);
	}
	study[sc++] = u;
	ins[u] = false;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &d[i]);
	}
	int t, x;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &t);
		while (t--)
		{
			scanf("%d", &x);
			add_edge(i, x);
		}
	}
	for (int i = 0; i < k; i++)
	{
		dfs(d[i]);
	}
	printf("%d\n", sc);
	for (int i = 0; i < sc; i++)
	{
		printf("%d ", study[i]);
	}
	return 0;
}
