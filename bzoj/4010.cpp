// Problem Name: 菜肴制作
// Source: [NHOI2015]

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct vertex
{
	int first, ideg;
}V[100010];

struct edge
{
	int endp, next;
}E[100010];

struct info
{
	int ideg, id;
	info(int _ideg, int _id) : ideg(_ideg), id(_id) { }
};

int ivc, iec, ec = 1, ans[100010], ac;
priority_queue<info> Q;

inline bool operator < (const info &x, const info &y)
{
	if (x.ideg == y.ideg) return x.id < y.id;
	return x.ideg > y.ideg;
}

inline void add_edge(int u, int v)
{
	V[v].ideg++;
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void init()
{
	memset(V, 0, sizeof(V));
	ec = 1;
	ac = 0;
	while (Q.size() > 0) Q.pop();
}

bool solve()
{
	for (int i = 1; i <= ivc; i++)
	{
		Q.push(info(V[i].ideg, i));
	}
	int oc = 0;
	while (oc < ivc)
	{
		info u = Q.top();
		Q.pop();
		if (u.ideg > 0) return false;
		ans[ac++] = u.id;
		for (int cur = V[u.id].first; cur != 0; cur = E[cur].next)
		{
			Q.push(info(--V[E[cur].endp].ideg, E[cur].endp));
		}
		oc++;
	}
	return true;
}

int main()
{
	int D, u, v;
	scanf("%d", &D);
	while (D--)
	{
		init();
		scanf("%d%d", &ivc, &iec);
		for (int i = 0; i < iec; i++)
		{
			scanf("%d%d", &u, &v);
			add_edge(v, u);
		}
		if (solve() == false) printf("Impossible!\n");
		else
		{
			for (int i = ac - 1; i >= 0; i--)
			{
				printf("%d ", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
