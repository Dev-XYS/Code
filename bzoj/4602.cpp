// Problem Name: 齿轮
// Source: [SDOI2016]

#include <cstdio>
#include <cstring>

using namespace std;

struct vertex
{
	int first;
	double ratio;
}V[1010];

struct edge
{
	int endp, next;
	double ratio;
}E[20010];

const double eps = 1e-8;
int T, n, m, ec;
bool error;

inline double abs(double x)
{
	return x < 0 ? -x : x;
}

void init_graph()
{
	memset(V, 0, sizeof(V));
	ec = 1;
	error = false;
}

inline void add_edge(int u, int v, double r)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].ratio = r;
	ec++;
}

void dfs(int u, double ratio)
{//printf("dfs : %d, ratio = %.2lf\n", u, ratio);
	V[u].ratio = ratio;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].ratio == 0) dfs(E[cur].endp, ratio * E[cur].ratio);
		else if (abs(V[E[cur].endp].ratio - ratio * E[cur].ratio) > eps) error = true;
	}
}

int main()
{
	int u, v, x, y, casen = 0;
	scanf("%d", &T);
	while (T--)
	{
		init_graph();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d%d%d", &u, &v, &x, &y);
			add_edge(u, v, (double)y / (double)x);
			add_edge(v, u, (double)x / (double)y);
		}
		for (int i = 1; i <= n; i++)
		{
			if (V[i].ratio == 0) dfs(i, 1);
		}
		printf("Case #%d: %s\n", ++casen, error == false ? "Yes" : "No");
	}
	return 0;
}
