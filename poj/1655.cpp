#include <cstdio>
#include <cstring>

using namespace std;

struct vertex
{
	int first, balance;
}V[20010];

struct edge
{
	int endp, next;
}E[40010];

int ec = 1, ivc;

inline int max(int x, int y)
{
	return x > y ? x : y;
}

void init_graph()
{
	memset(V, 0, sizeof(V));
	ec = 1;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

int DFS(int u, int p)
{
	int sum = 1, sub;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != p)
		{
			sub = DFS(E[cur].endp, u);
			V[u].balance = max(V[u].balance, sub);
			sum += sub;
		}
	}
	V[u].balance = max(V[u].balance, ivc - sum);
	return sum;
}

int main()
{
	int t, u, v;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &ivc);
		init_graph();
		for (int i = 1; i < ivc; i++)
		{
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		DFS(1, 0);
		int mo = 1;
		for (int i = 2; i <= ivc; i++)
		{
			if (V[i].balance < V[mo].balance)
			{
				mo = i;
			}
		}
		printf("%d %d\n", mo, V[mo].balance);
	}
	return 0;
}
