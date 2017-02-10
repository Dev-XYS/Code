#include <cstdio>
#include <cstring>

struct vertex
{
	int first, dfn, low, subnet;
	bool iscv;
}V[1010];

struct edge
{
	int endp, next;
}E[2000010];

int ec, dfn;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	memset(V, 0, sizeof(V));
	ec = 2, dfn = 1;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u, int pe)
{
	V[u].dfn = V[u].low = dfn++;
	V[u].subnet = 1;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp, cur);
			if (V[E[cur].endp].low >= V[u].dfn)
			{
				V[u].iscv = true;
				V[u].subnet++;
			}
			V[u].low = min(V[u].low, V[E[cur].endp].low);
		}
		else if ((pe ^ cur) != 1)
		{
			V[u].low = min(V[u].low, V[E[cur].endp].dfn);
		}
	}
}

void get(int rt)
{
	int chc = 0;
	V[rt].dfn = V[rt].low = dfn++;
	for (int cur = V[rt].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			chc++;
			DFS(E[cur].endp, cur);
		}
	}
	if (chc > 1)
	{
		V[rt].iscv = true;
	}
	V[rt].subnet = chc;
}

int main()
{
	int u, v, casen = 0;
	while (true)
	{
		init();
		scanf("%d", &u);
		if (u == 0) return 0;
		scanf("%d", &v);
		add_edge(u, v);
		add_edge(v, u);
		while (true)
		{
			scanf("%d", &u);
			if (u == 0) break;
			scanf("%d", &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		printf("Network #%d\n", ++casen);
		bool hascv = false;
		for (int i = 1; i <= 1000; i++)
		{
			if (V[i].first != 0)
			{
				if (V[i].dfn == 0)
				{
					get(i);
				}
				if (V[i].iscv == true)
				{
					printf("  SPF node %d leaves %d subnets\n", i, V[i].subnet);
					hascv = true;
				}
			}
		}
		if (hascv == false)
		{
			printf("  No SPF nodes\n");
		}
		printf("\n");
	}
	return 0;
}
