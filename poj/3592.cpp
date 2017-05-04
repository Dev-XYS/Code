// Problem Name: Instantaneous Transference
// Source: South Central China 2008 hosted by NUDT

#include <cstdio>
#include <queue>

using namespace std;

struct vertex
{
	int first, cnt, dfn, low, col;
}V[1610];

struct edge
{
	int endp, next;
}E[4810];

struct raw_edge
{
	int u, v;
	raw_edge(int _u = 0, int _v = 0) : u(_u), v(_v) { }
}R[4810];

int T, n, m, ec, dfn, col, S[1610], sp, ore[1610], rec, dis[1610];
char map[50][50];
bool ins[1610];

void init_graph()
{
	for (int i = n * m - 1; i >= 0; i--)
	{
		V[i].first = 0;
		V[i].cnt = 0;
		V[i].dfn = 0;
	}
	ec = 1;
	dfn = 0, col = 0;
}

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

inline int ord(int x, int y)
{
	return x * m + y;
}

inline bool can(int x, int y)
{
	if (x >= n) return false;
	if (y >= m) return false;
	if (map[x][y] == '#') return false;
	return true;
}

void dfs(int u)
{
	S[sp++] = u, ins[u] = true;
	V[u].dfn = V[u].low = ++dfn;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			dfs(E[cur].endp);
			if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
		}
		else if (ins[E[cur].endp] == true)
		{
			if (V[E[cur].endp].low < V[u].low) V[u].low = V[E[cur].endp].low;
		}
	}
	if (V[u].low == V[u].dfn)
	{
		col++;
		int v;
		do
		{
			v = S[--sp], ins[v] = false;
			V[v].col = col;
			ore[col] += V[v].cnt;
		} while (v != u);
	}
}

void build_graph()
{
	for (int i = 1; i <= col; i++)
	{
		V[i].first = 0;
	}
	for (int i = 0; i < rec; i++)
	{
		add_edge(R[i].u, R[i].v);
	}
}

void spfa()
{
	for (int i = 1; i <= col; i++)
	{
		dis[i] = 0;
	}
	dis[V[0].col] = ore[V[0].col];
	queue<int> Q;
	static bool inq[1610];
	for (int i = 1; i <= col; i++)
	{
		inq[i] = false;
	}
	Q.push(V[0].col), inq[V[0].col] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = dis[u] + ore[E[cur].endp];
			if (newdis > dis[E[cur].endp])
			{
				dis[E[cur].endp] = newdis;
				if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			scanf("%s", map[i]);
		}
		init_graph();
		int x, y;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if ('0' <= map[i][j] && map[i][j] <= '9')
				{
					V[ord(i, j)].cnt = map[i][j] - '0';
					if (can(i + 1, j) == true) add_edge(ord(i, j), ord(i + 1, j));
					if (can(i, j + 1) == true) add_edge(ord(i, j), ord(i, j + 1));
				}
				else if (map[i][j] == '*')
				{
					scanf("%d%d", &x, &y);
					if (can(i + 1, j) == true) add_edge(ord(i, j), ord(i + 1, j));
					if (can(i, j + 1) == true) add_edge(ord(i, j), ord(i, j + 1));
					add_edge(ord(i, j), ord(x, y));
				}
			}
		}
		for (int i = n * m; i >= 1; i--)
		{
			ore[i] = 0;
		}
		for (int i = n * m - 1; i >= 0; i--)
		{
			if (V[i].dfn == 0) dfs(i);
		}
		rec = 0;
		for (int i = n * m - 1; i >= 0; i--)
		{
			for (int cur = V[i].first; cur != 0; cur = E[cur].next)
			{
				if (V[E[cur].endp].col != V[i].col)
				{
					R[rec++] = raw_edge(V[i].col, V[E[cur].endp].col);
				}
			}
		}
		build_graph();
		spfa();
		int ans = 0;
		for (int i = 1; i <= col; i++)
		{
			if (dis[i] > ans) ans = dis[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
