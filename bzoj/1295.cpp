// Problem Name: 最长距离
// Source: [SCOI2009]

#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, w, dis;
}V[910];

struct edge
{
	int endp, next;
}E[3610];

const int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };
int n, m, T, ec = 1;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

inline int point(int x, int y)
{
	return x * m + y;
}

inline int sqr(int x)
{
	return x * x;
}

inline double dist(int x1, int y1, int x2, int y2)
{
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

void build_graph()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int d = 0; d < 4; d++)
			{
				if (i + dx[d] < 0 || i + dx[d] >= n || j + dy[d] < 0 || j + dy[d] >= m) continue;
				add_edge(point(i, j), point(i + dx[d], j + dy[d]));
			}
		}
	}
}

void init_single_source(int x, int y)
{
	for (int i = n * m - 1; i >= 0; i--)
	{
		V[i].dis = INF;
	}
	V[point(x, y)].dis = V[point(x, y)].w;
}

void spfa(int i, int j)
{
	init_single_source(i, j);
	queue<int> Q;
	static bool inq[910];
	memset(inq, 0, sizeof(inq));
	Q.push(point(i, j)), inq[point(i, j)] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u].dis + V[E[cur].endp].w;
			if (newdis < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newdis;
				if (inq[E[cur].endp] == false) Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &T);
	char temp[40];
	for (int i = 0; i < n; i++)
	{
		scanf("%s", temp);
		for (int j = 0; j < m; j++)
		{
			V[point(i, j)].w = temp[j] - '0';
		}
	}
	build_graph();
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			spfa(i, j);
			for (int _i = 0; _i < n; _i++)
			{
				for (int _j = 0; _j < m; _j++)
				{
					if (V[point(_i, _j)].dis <= T && dist(i, j, _i, _j) > ans) ans = dist(i, j, _i, _j);
				}
			}
		}
	}
	printf("%.6lf\n", ans);
	return 0;
}
