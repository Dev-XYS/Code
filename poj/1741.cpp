#include <cstdio>
#include <cstring>
#include <algorithm>

#define printf(...) printf(__VA_ARGS__);fflush(stdout)

#define VERTEX_COUNT 10010
#define EDGE_COUNT 20010

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

int n, k, ec = 2;

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

int ss, S[10010], sp = 0;
void DFSg(int u, int p)
{//printf("DFSg : u = %d, p = %d\n", u, p);
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
{//printf("get_g\n");
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

int dis[10010], dc;
void DFS(int u, int p, int ws)
{//printf("DFS : u = %d, p = %d, ws = %d\n", u, p, ws);
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
	while (l <= r)
	{
		if (dis[l] + dis[r] <= k)
		{
			res += r - l++ + 1;
		}
		else
		{
			r--;
		}
	}
	return res;
}

int solve(int rt)
{//printf("solve : rt = %d\n", rt);
	int res = 0;
	int g = get_g(rt);//printf("get_g finished : %d.\n", g);
	dc = 0;
	dis[dc++] = 0;
	int last = 1;
	for (int cur = V[g].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].del == false)
		{
			DFS(E[cur].endp, g, E[cur].w);
			sort(dis + last, dis + dc);
			res -= less_k(last, dc - 1);//printf("res(sub) -= %d.\n", less_k(last, dc - 1));
			last = dc;
		}
	}
	sort(dis, dis + dc);
	res += less_k(0, dc - 1) - 1;//printf("res(all) += %d.\n", less_k(0, dc - 1) - 1);
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

int main()
{
	int u, v, w;
	while (scanf("%d%d", &n, &k))
	{
		if (n == 0 && k == 0) break;
		init();
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		ss = n;
		printf("%d\n", solve(1));
	}
	return 0;
}
