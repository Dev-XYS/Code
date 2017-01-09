#include <cstdio>
#include <cstring>
#include <algorithm>

#define VERTEX_COUNT 20010
#define EDGE_COUNT 40010

using namespace std;

struct vertex
{
	int first, size, max_size;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, w;
	bool del;
}E[EDGE_COUNT];

int n, ec = 2;

void init()
{
	memset(V, 0, sizeof(V));
	memset(E, 0, sizeof(E));
	ec = 2;
}

void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

int ss, S[20010], sp = 0;
void DFSg(int u, int p)
{
	S[sp++] = u;
	V[u].size = 1;
	V[u].max_size = 0;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].del == false && E[cur].endp != p)
		{
			DFSg(E[cur].endp, u);
			V[u].size += V[E[cur].endp].size;
			V[u].max_size = max(V[u].max_size, V[E[cur].endp].size);
		}
	}
	V[u].max_size = max(V[u].max_size, ss - V[u].size);
}

int get_g(int rt)
{
	sp = 0;
	DFSg(rt, 0);
	int res = S[0];
	for (int i = 1; i < sp; i++)
	{
		if (V[S[i]].max_size < V[res].max_size)
		{
			res = S[i];
		}
	}
	return res;
}

int dis[20010], dc;
void DFS(int u, int p, int ws)
{
	dis[dc++] = ws;
	V[u].size = 1;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].del == false && E[cur].endp != p)
		{
			DFS(E[cur].endp, u, ws + E[cur].w);
			V[u].size += V[E[cur].endp].size;
		}
	}
}

int less_k(int l, int r)
{
	int res = 0;
	int c[3] = { 0, 0, 0 };
	for (int i = l; i <= r; i++)
	{
		c[dis[i] % 3]++;
	}
	for (int i = l; i <= r; i++)
	{
		res += c[(3 - dis[i] % 3) % 3];
	}
	return res;
}

int solve(int rt)
{
	int res = 0;
	int g = get_g(rt);
	dc = 0;
	dis[dc++] = 0;
	int last = 1;
	for (int cur = V[g].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].del == false)
		{
			DFS(E[cur].endp, g, E[cur].w);
			res -= less_k(last, dc - 1);
			last = dc;
		}
	}
	res += less_k(0, dc - 1);
	for (int cur = V[g].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].del == false)
		{
			E[cur].del = E[cur ^ 1].del = true;
			ss = V[E[cur].endp].size;
			res += solve(E[cur].endp);
		}
	}
	return res;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	int u, v, w;
	while (scanf("%d", &n) > 0)
	{
		if (n == 0) break;
		init();
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		ss = n;
		int p = solve(1);
		int q = n * n;
		int g = gcd(p, q);
		p /= g;
		q /= g;
		printf("%d/%d\n", p, q);
	}
	return 0;
}
