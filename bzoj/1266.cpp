// Problem Name: 上学路线 route
// Source: [AHOI2006]

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis, fdis;
}V[510];

struct edge
{
	int endp, next, w, c, flow;
	bool ing;
}E[124750 * 4 + 10];

int ivc, iec, ec = 2;
int src, sink;

inline void add_edge(int u, int v, int w, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	E[ec].flow = f;
	ec++;
}

int spfa()
{
	for (int i = 2; i <= ivc; i++)
	{
		V[i].dis = INF;
	}
	queue<int> Q;
	static bool inq[510];
	Q.push(1), inq[1] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u].dis + E[cur].w;
			if (newdis < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newdis;
				if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
	return V[ivc].dis;
}

bool bfs()
{
	queue<int> Q;
	static bool vis[2010];
	memset(vis, 0, sizeof(vis));
	Q.push(sink), vis[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].ing == true && vis[E[cur].endp] == false && E[cur ^ 1].flow > 0)
			{
				V[E[cur].endp].fdis = V[u].fdis + 1;
				Q.push(E[cur].endp), vis[E[cur].endp] = true;;
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
		if (E[cur].ing == true && V[u].fdis == V[E[cur].endp].fdis + 1 && E[cur].flow > 0)
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

int main()
{
	int u, v, w, c;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d%d", &u, &v, &w, &c);
		add_edge(u, v, w, c);
		add_edge(v, u, w, 0);
		add_edge(v, u, w, c);
		add_edge(u, v, w, 0);
	}
	printf("%d\n", spfa());
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].dis + E[cur].w == V[E[cur].endp].dis && E[cur].flow > 0)
			{
				E[cur].ing = E[cur ^ 1].ing = true;
			}
		}
	}
	src = 1, sink = ivc;
	printf("%d", dinic());
	return 0;
}
