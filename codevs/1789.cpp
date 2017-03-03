// Problem Name: [NOI2006] 最大获利

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

typedef long long ll;

using namespace std;

struct vertex
{
	int first, dis, w;
	bool vis;
}V[55010];

struct edge
{
	int endp, next, f;
}E[310010];

const int src = 55005, sink = 55006;
int n, m, ivc, ec = 2, gap[55010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	ivc = n + m;
	gap[0] = ivc + 2;
}

inline void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].f = f;
	ec++;
}

bool bfs()
{
	queue<int> Q;
	static bool inq[55010];
	memset(inq, false, sizeof(inq));
	Q.push(sink), inq[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur ^ 1].f > 0 && inq[E[cur].endp] == false)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
	return inq[src] == true;
}

int dfs(int u, int curf)
{
	if (u == sink) return curf;
	int totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].f > 0)
		{
			int f = dfs(E[cur].endp, min(E[cur].f, curf - totalf));
			E[cur].f -= f;
			E[cur ^ 1].f += f;
			totalf += f;
		}
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (bfs() == true)
	{
		int flow;
		do
		{
			flow = dfs(src, INF);
			res += flow;
		} while (flow > 0);
	}
	return res;
}

int main()
{
	int a, b, c;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i + m].w);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		V[i].w = c;
		add_edge(i, a + m, INF);
		add_edge(a + m, i, 0);
		add_edge(i, b + m, INF);
		add_edge(b + m, i, 0);
	}
	int psum = 0;
	for (int i = 1; i <= m; i++)
	{
		psum += V[i].w;
		add_edge(src, i, V[i].w);
		add_edge(i, src, 0);
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(i + m, sink, V[i + m].w);
		add_edge(sink, i + m, 0);
	}
	init();
	printf("%d", psum - max_flow());
	return 0;
}
