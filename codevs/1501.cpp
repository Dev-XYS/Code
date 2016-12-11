#include <cstdio>

using namespace std;

struct vertex
{
	int first, depth;
}V[20];

struct edge
{
	int endp, next;
}E[20];

int ec = 1, ivc, cnt[20];

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u, int depth)
{
	if (u == 0)
	{
		return;
	}
	V[u].depth = depth;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		DFS(E[cur].endp, depth + 1);
	}
}

int main()
{
	int lch, rch;
	scanf("%d", &ivc);
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%d%d", &lch, &rch);
		if (lch != 0) add_edge(i, lch);
		if (rch != 0) add_edge(i, rch);
	}
	DFS(1, 1);
	int maxh = 0, maxw = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].depth > maxh)
			maxh = V[i].depth;
		cnt[V[i].depth]++;
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (cnt[i] > maxw)
			maxw = cnt[i];
	}
	printf("%d %d", maxw, maxh);
	return 0;
}
