// Problem Name: 变换序列
// Source: [NOI2009]

#include <cstdio>
#include <cstring>
#include <algorithm>

#define VERTEX_COUNT 20010
#define EDGE_COUNT 20010

using namespace std;

struct vertex
{
	int first, mv;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int n, ec = 1;
bool vis[VERTEX_COUNT];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

bool dfs(int u)
{
	if (vis[u] == true) return false;
	vis[u] = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[u].mv != E[cur].endp && (V[E[cur].endp].mv == 0 || dfs(V[E[cur].endp].mv) == true))
		{
			V[u].mv = E[cur].endp;
			V[E[cur].endp].mv = u;
			return true;
		}
	}
	return false;
}

int match()
{
	int res = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		memset(vis, false, sizeof(vis));
		res += (int)dfs(i);
	}
	return res;
}

int main()
{
	int x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		int a = (i - x + n) % n, b = (i + x) % n;
		if (a < b) swap(a, b);
		add_edge(i, a + n);
		add_edge(i, b + n);
	}
	if (match() < n) printf("No Answer");
	else
	{
		printf("%d", V[0].mv - n);
		for (int i = 1; i < n; i++)
		{
			printf(" %d", V[i].mv - n);
		}
	}
	return 0;
}
