#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000

using namespace std;

struct raw_edge
{
	int u, v, t;
}R[100010];

struct vertex
{
	int first, dis;
}V[1010];

struct edge
{
	int endp, next, t;
}E[100010];

int ivc, iec, X, ec, total[1010];
bool inq[1010];

void init_graph()
{
	memset(V, 0, sizeof(V));
	ec = 1;
	for (int i = 1; i <= ivc; i++)
	{
		V[i].dis = INF;
	}
	V[X].dis = 0;
}

void add_edge(int u, int v, int t)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].t = t;
	ec++;
}

void spfa()
{
	queue<int> Q;
	Q.push(X), inq[X] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u].dis + E[cur].t;
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
	scanf("%d%d%d", &ivc, &iec, &X);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].t);
	}
	init_graph();
	for (int i = 0; i < iec; i++)
	{
		add_edge(R[i].u, R[i].v, R[i].t);
	}
	spfa();
	for (int i = 1; i <= ivc; i++)
	{
		total[i] = V[i].dis;
	}
	init_graph();
	for (int i = 0; i < iec; i++)
	{
		add_edge(R[i].v, R[i].u, R[i].t);
	}
	spfa();
	for (int i = 1; i <= ivc; i++)
	{
		total[i] += V[i].dis;
	}
	int ans = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (total[i] > ans) ans = total[i];
	}
	printf("%d", ans);
	return 0;
}
