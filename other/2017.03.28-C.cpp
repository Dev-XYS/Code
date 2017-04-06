#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1e9

using namespace std;

struct vertex
{
	int first, dis;
	bool in_src;
}V[20010];

struct edge
{
	int endp, next, flow;
	bool is_cut;
}E[120010];

const int src = 20005, sink = 20006;
int n, k, x[20010], p1, p2, c1, c2, rem1[10010], rem2[10010], ec = 2;
bool brk[20010], has[20010];

inline void _add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void add_edge(int u, int v, int f)
{
	_add_edge(u, v, f);
	_add_edge(v, u, 0);
}

bool bfs()
{
	static bool vis[20010];
	memset(vis, 0, sizeof(vis));
	queue<int> Q;
	Q.push(sink), vis[sink] = true;
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
	return vis[src] == true;
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

int get_div_count()
{
	int _n = n;
	for (int i = 2; i * i <= _n; i++)
	{
		if (n % i == 0)
		{
			p1 = i, c1 = n / p1;
			while (_n % i == 0) _n /= i;
			if (_n == 1) return 1;
			else break;
		}
	}
	if (_n == n)
	{
		p1 = n, c1 = 1;
		return 1;
	}
	for (int i = 2; ; i++)
	{
		if (_n % i == 0)
		{
			p2 = i, c2 = n / i;
			return 2;
		}
	}
}

void dfs_mark(int u)
{
	V[u].in_src = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[E[cur].endp].in_src == false) dfs_mark(E[cur].endp);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &x[i]);
		x[i]--;
		brk[x[i]] = true;
	}
	if (get_div_count() == 1)
	{
		for (int i = 0; i < k; i++)
		{
			rem1[x[i] % c1]++;
		}
		int ans = 0;
		for (int i = 0; i < c1; i++)
		{
			if (rem1[i] == 0) ans++;
		}
		printf("%d", ans == 0 ? -1 : (n - k) - ans * p1);
	}
	else
	{
		for (int i = 0; i < k; i++)
		{
			rem1[x[i] % c1]++;
		}
		for (int i = 0; i < k; i++)
		{
			rem2[x[i] % c2]++;
		}
		int ans = 0;
		for (int i = 0; i < c1; i++)
		{
			if (rem1[i] == 0) add_edge(src, i, p1), ans += p1;
		}
		for (int i = 0; i < c1; i++)
		{
			for (int j = i; j < n; j += c1)
			{
				add_edge(i, j % c2 + c1, INF);
			}
		}
		for (int i = 0; i < c2; i++)
		{
			if (rem2[i] == 0) add_edge(i + c1, sink, p2), ans += p2;
		}
		int d = dinic();
		if (ans - d == 0)
		{
			printf("-1");
			return 0;
		}
		printf("%d\n", (n - k) - (ans - d));
		dfs_mark(src);
		for (int cur = V[src].first; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].in_src == false)
			{
				E[cur].is_cut = E[cur ^ 1].is_cut = true;
			}
		}
		for (int i = 0; i < c1 + c2; i++)
		{
			if (V[i].in_src == true)
			{
				for (int cur = V[i].first; cur != 0; cur = E[cur].next)
				{
					if (V[E[cur].endp].in_src == false)
					{
						E[cur].is_cut = E[cur ^ 1].is_cut = true;
					}
				}
			}
		}
		for (int cur = V[src].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].is_cut == false)
			{
				for (int i = E[cur].endp; i < n; i += c1)
				{
					has[i] = true;
				}
			}
		}
		for (int cur = V[sink].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].is_cut == false)
			{
				for (int i = E[cur].endp - c1; i < n; i += c2)
				{
					has[i] = true;
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (has[i] == false && brk[i] == false)
			{
				printf("%d ", i + 1);
			}
		}
	}
	return 0;
}
