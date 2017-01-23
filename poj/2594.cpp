#include <cstdio>
#include <cstring>

#define INF 1000000000
#define SOURCE 1005
#define SINK 1006

using namespace std;

struct vertex
{
	int first, dis;
}V[1010];

struct edge
{
	int endp, next, flow;
}E[502010];

int ivc, iec, vc, ec = 2, gap[1010];
bool con[510][510];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	vc = ivc * 2 + 2;
	ec = 2;
	memset(gap, 0, sizeof(gap));
	memset(V, 0, sizeof(V));
	memset(con, false, sizeof(con));
	gap[0] = vc;
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].flow = 0;
	ec++;
}

void floyd()
{
	for (int k = 1; k <= ivc; k++)
	{
		for (int i = 1; i <= ivc; i++)
		{
			for (int j = 1; j <= ivc; j++)
			{
				con[i][j] = con[i][j] || (con[i][k] && con[k][j]);
			}
		}
	}
}

int isap(int u, int curf)
{
	if (u == SINK) return curf;
	int totalf = 0, mindis = vc;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0) V[SOURCE].dis = vc;
		else
		{
			V[u].dis = mindis + 1;
			gap[V[u].dis]++;
		}
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[SOURCE].dis < vc)
	{
		res += isap(SOURCE, INF);
	}
	return res;
}

void build_graph()
{
	for (int i = 1; i <= ivc; i++)
	{
		add_edge(SOURCE, i, 1);
		add_edge(i + ivc, SINK, 1);
	}
	for (int i = 1; i <= ivc; i++)
	{
		for (int j = 1; j <= ivc; j++)
		{
			if (con[i][j] == true)
			{
				add_edge(i, j + ivc, 1);
			}
		}
	}
}

int main()
{
	int u, v;
	while (true)
	{
		scanf("%d%d", &ivc, &iec);
		if (ivc == 0 && iec == 0) break;
		init();
		for (int i = 0; i < iec; i++)
		{
			scanf("%d%d", &u, &v);
			con[u][v] = true;
		}
		floyd();
		build_graph();
		printf("%d\n", ivc - max_flow());
	}
	return 0;
}
