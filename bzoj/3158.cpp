// Problem Name: 千钧一发
// Source: Katharon+#1

#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>

#define INF 1000000000

typedef long long ll;

using namespace std;

struct vertex
{
	int first, col, dis;
}V[1010];

struct edge
{
	int endp, next, flow;
}E[1002010];

const int src = 1005, sink = 1006;
int n, ec = 2, A[1010], B[1010];

inline void _add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void add_empty_edge(int u, int v)
{
	_add_edge(u, v, 0);
	_add_edge(v, u, 0);
}

inline void add_edge(int u, int v, int f)
{
	_add_edge(u, v, f);
	_add_edge(v, u, 0);
}

bool bfs()
{
	queue<int> Q;
	static bool vis[1010];
	memset(vis, 0, sizeof(vis));
	V[sink].dis = 0, Q.push(sink), vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (vis[E[cur].endp] == false && E[cur ^ 1].flow > 0)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), vis[E[cur].endp] = true;
			}
		}
	}
	return vis[src];
}

int dfs(int u, int curf)
{
	if (u == sink) return curf;
	int totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].flow > 0)
		{
			int f = dfs(E[cur].endp, min(E[cur].flow, curf - totalf));
			E[cur].flow -= f;
			E[cur ^ 1].flow += f;
			totalf += f;
		}
	}
	if (totalf == 0) V[u].dis = -1;
	return totalf;
}

int dinic()
{
	int res = 0;
	while (bfs() == true)
	{
		int f;
		do
		{
			f = dfs(src, INF);
			res += f;
		} while (f > 0);
	}
	return res;
}

bool is_sqr(ll x)
{
	ll s = (ll)(sqrt(x) + 0.1);
	return s * s == x ? true : false;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void dfs_col(int u, int col)
{
	V[u].col = col;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].col == 0) dfs_col(E[cur].endp, col == 1 ? 2 : 1);
		if (col == 1) E[cur].flow = INF;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &B[i]);
		sum += B[i];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (is_sqr((ll)A[i] * A[i] + (ll)A[j] * A[j]) == true && gcd(A[i], A[j]) == 1)
			{
				add_empty_edge(i, j);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].col == 0)
		{
			dfs_col(i, 1);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (V[i].col == 1)
		{
			add_edge(src, i, B[i]);
		}
		else
		{
			add_edge(i, sink, B[i]);
		}
	}
	printf("%d\n", sum - dinic());
	return 0;
}
