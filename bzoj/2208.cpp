#include <cstdio>
#include <cstring>

using namespace std;

struct vertex
{
	int first, cnt;
}V[2010];

struct edge
{
	int endp, next;
}E[4000010];

int ivc, ec = 1;
bool vis[2010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u)
{
	if (vis[u] == false)
	{
		vis[u] = true;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			dfs(E[cur].endp);
		}
	}
}

int main()
{
	int ans = 0;
	char s[2010];
	scanf("%d", &ivc);
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%s", s + 1);
		for (int j = 1; j <= ivc; j++)
		{
			if (s[j] == '1') add_edge(i, j);
		}
	}
	for (int i = 1; i <= ivc; i++)
	{
		memset(vis, false, sizeof(vis));
		dfs(i);
		for (int j = 1; j <= ivc; j++)
		{
			if (vis[j] == true) ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
