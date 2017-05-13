// Problem Name: 道路修建
// Source: [NOI2011]

#include <cstdio>
#include <queue>

using namespace std;

struct vertex
{
	int first, size;
	bool vis;
}V[1000010];

struct edge
{
	int endp, next, c;
	bool down;
}E[2000010];

int ivc, ec = 2, order[1000010], oc;

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline void add_edge(int u, int v, int c)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].c = c;
	ec++;
}

void bfs()
{
	queue<int> Q;
	Q.push(1), V[1].vis = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), order[oc++] = u;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].vis == false) Q.push(E[cur].endp), V[E[cur].endp].vis = true, E[cur].down = true;
		}
	}
}

int main()
{
	scanf("%d", &ivc);
	int u, v, c;
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, c);
		add_edge(v, u, c);
	}
	bfs();
	for (int i = oc - 1; i >= 0; i--)
	{
		for (int cur = V[order[i]].first; cur != 0; cur = E[cur].next)
		{
			V[order[i]].size += V[E[cur].endp].size;
		}
		V[order[i]].size++;
	}
	long long ans = 0;
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].down == true) ans += (long long)E[cur].c * abs(ivc - V[E[cur].endp].size * 2);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
