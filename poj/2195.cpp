#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000
#define SOURCE 205
#define SINK 206
#define VERTEX_COUNT 210
#define EDGE_COUNT 20410

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow, cost;
}E[EDGE_COUNT];

struct point
{
	int x, y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) { }
}H[110], M[110];

int n, m, ihc, imc, src, sink, ec = 2, ans;
queue<int> Q;
bool inq[VERTEX_COUNT];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

void init()
{
	src = SOURCE;
	sink = SINK;
	ihc = imc = 0;
	ans = 0;
	memset(V, 0, sizeof(V));
	ec = 2;
}

int dist(point &a, point &b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void add_edge(int u, int v, int f, int c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	E[ec].cost = c;
	ec++;
}

void init_single_source()
{
	for (int i = 1; i <= ihc + imc; i++)
	{
		V[i].dis = INF;
	}
	V[sink].dis = INF;
	V[src].dis = 0;
}

bool spfa()
{
	int u;
	init_single_source();
	Q.push(src), inq[src] = true;
	while (!Q.empty())
	{
		u = Q.front(), Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].flow > 0 && V[u].dis + E[cur].cost < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = V[u].dis + E[cur].cost;
				if (inq[E[cur].endp] == false)
				{
					Q.push(E[cur].endp), inq[E[cur].endp] = true;
				}
			}
		}
	}
	return V[sink].dis < INF;
}
		
int DFS(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (inq[E[cur].endp] == false && E[cur].flow > 0 && V[E[cur].endp].dis == V[u].dis + E[cur].cost)
		{
			inq[E[cur].endp] = true;
			int f = DFS(E[cur].endp, min(curf, E[cur].flow));
			inq[E[cur].endp] = false;
			if (f > 0)
			{
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				ans += E[cur].cost;
				return f;
			}
		}
	}
	return 0;
}

void max_flow()
{
	while (spfa() == true)
	{
		DFS(src, INF);
	}
}

int main()
{
	char temp[110];
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0)
		{
			break;
		}
		init();
		for (int i = 0; i < n; i++)
		{
			scanf("%s", temp);
			for (int j = 0; j < m; j++)
			{
				if (temp[j] == 'H')
				{
					H[ihc++] = point(i, j);
				}
				else if(temp[j] == 'm')
				{
					M[imc++] = point(i, j);
				}
			}
		}
		for (int i = 0; i < ihc; i++)
		{
			for (int j = 0; j < imc; j++)
			{
				add_edge(i + 1, j + ihc + 1, 1, dist(H[i], M[j]));
				add_edge(j + ihc + 1, i + 1, 0, -dist(H[i], M[j]));
			}
		}
		for (int i = 0; i < ihc; i++)
		{
			add_edge(src, i + 1, 1, 0);
			add_edge(i + 1, src, 0, 0);
		}
		for (int i = 0; i < imc; i++)
		{
			add_edge(i + ihc + 1, sink, 1, 0);
			add_edge(sink, i + ihc + 1, 0, 0);
		}
		max_flow();
		printf("%d\n", ans);
	}
	return 0;
}
