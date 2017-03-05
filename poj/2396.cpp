// Problem Name: Budget
// Source: Tehran 2003 Preliminary

#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1e9

using namespace std;

struct vertex
{
	int first, iso, dis;
}V[230];

struct edge
{
	int endp, next, lower, flow;
}E[8890];

const int src = 225, sink = 226, _src = 227, _sink = 228;
int n, m, sr[210], sc[30], c, whole[2], row[210][2], column[30][2], cell[210][30][2], res[210][30], ec;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline void add_edge(int u, int v, int lower, int flow)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].lower = lower;
	E[ec].flow = flow;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].lower = lower;
	E[ec].flow = 0;
	ec++;
}

void init()
{
	ec = 2;
	memset(V, 0, sizeof(V));
	memset(E, 0, sizeof(E));
	whole[0] = 0;
	whole[1] = INF;
	for (int i = 1; i <= n; i++)
	{
		row[i][0] = 0;
		row[i][1] = INF;
	}
	for (int i = 1; i <= m; i++)
	{
		column[i][0] = 0;
		column[i][1] = INF;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cell[i][j][0] = 0;
			cell[i][j][1] = INF;
		}
	}
}

bool bfs()
{
	queue<int> Q;
	static bool inq[230];
	memset(inq, false, sizeof(inq));
	Q.push(_sink), inq[_sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (inq[E[cur].endp] == false && E[cur ^ 1].flow > 0)
			{
				Q.push(E[cur].endp), inq[E[cur].endp] = true;
				V[E[cur].endp].dis = V[u].dis + 1;
			}
		}
	}
	return inq[_src] == true;
}

int dfs(int u, int curf)
{
	if (u == _sink) return curf;
	int totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].flow > 0)
		{
			int f = dfs(E[cur].endp, min(curf - totalf, E[cur].flow));
			E[cur].flow -= f;
			E[cur ^ 1].flow += f;
			totalf += f;
		}
	}
	return totalf;
}

void dinic()
{
	while (bfs() == true)
	{
		while (dfs(_src, INF) > 0) ;
	}
}

inline void restrict(int *dest, char op, int v)
{
	switch (op)
	{
	case '=':
		if (v > dest[0]) dest[0] = v;
		if (v < dest[1]) dest[1] = v;
		break;
	case '<':
		if (v <= dest[1]) dest[1] = v - 1;
		break;
	case '>':
		if (v >= dest[0]) dest[0] = v + 1;
		break;
	}
}

void constraint(int x, int y, char op, int v)
{
	if (x == 0 && y == 0) restrict(whole, op, v);
	else if (x == 0) restrict(column[y], op, v);
	else if (y == 0) restrict(row[x], op, v);
	else restrict(cell[x][y], op, v);
}

bool build_graph()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (whole[0] > cell[i][j][0]) cell[i][j][0] = whole[0];
			if (whole[1] < cell[i][j][1]) cell[i][j][1] = whole[1];
			if (row[i][0] > cell[i][j][0]) cell[i][j][0] = row[i][0];
			if (row[i][1] < cell[i][j][1]) cell[i][j][1] = row[i][1];
			if (column[j][0] > cell[i][j][0]) cell[i][j][0] = column[j][0];
			if (column[j][1] < cell[i][j][1]) cell[i][j][1] = column[j][1];
			if (cell[i][j][0] > cell[i][j][1]) return false;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			add_edge(i, j + n, cell[i][j][0], cell[i][j][1] - cell[i][j][0]);
			V[i].iso -= cell[i][j][0];
			V[j + n].iso += cell[i][j][0];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(src, i, sr[i], 0);
		V[i].iso += sr[i];
		if (V[i].iso > 0) add_edge(_src, i, 0, V[i].iso);
		else add_edge(i, _sink, 0, -V[i].iso);
	}
	for (int i = 1; i <= m; i++)
	{
		add_edge(i + n, sink, sc[i], 0);
		V[i + n].iso -= sc[i];
		if (V[i + n].iso > 0) add_edge(_src, i + n, 0, V[i + n].iso);
		else add_edge(i + n, _sink, 0, -V[i + n].iso);
	}
	add_edge(_src, sink, 0, V[sink].iso);
	add_edge(src, _sink, 0, -V[src].iso);
	add_edge(sink, src, 0, INF);
	return true;
}

int main()
{
	int T, x, y, v;
	char op[10];
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &sr[i]);
		}
		for (int i = 1; i <= m; i++)
		{
			scanf("%d", &sc[i]);
		}
		scanf("%d", &c);
		init();
		for (int i = 0; i < c; i++)
		{
			scanf("%d%d%s%d", &x, &y, op, &v);
			constraint(x, y, op[0], v);
		}
		if (build_graph() == true)
		{
			dinic();
			for (int cur = V[_src].first; cur != 0; cur = E[cur].next)
			{
				if (E[cur].flow != 0) goto IMPOSSIBLE;
			}
			for (int cur = V[_sink].first; cur != 0; cur = E[cur].next)
			{
				if (E[cur ^ 1].flow != 0) goto IMPOSSIBLE;
			}
			for (int i = 1; i <= n; i++)
			{
				for (int cur = V[i].first; cur != 0; cur = E[cur].next)
				{
					if (E[cur].endp != src && E[cur].endp != _src && E[cur].endp != _sink) res[i][E[cur].endp - n] = E[cur ^ 1].flow + E[cur].lower;
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					printf("%d ", res[i][j]);
				}
				printf("\n");
			}
			printf("\n");
			goto END;
		}
	IMPOSSIBLE:
		printf("IMPOSSIBLE\n\n");
	END:;
	}
	return 0;
}
