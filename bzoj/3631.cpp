#include <cstdio>
#include <vector>

using namespace std;

struct query
{
	int a, b, ans;
	query(int _a, int _b) : a(_a), b(_b), ans(0) { }
};

struct vertex
{
	int first, fa, sub, ans;
	bool vis;
	vector<query> queries;
}V[300010];

struct edge
{
	int endp, next;
}E[600010];

int ivc, room[300010], ec = 1, fa[300010], ancestor[300010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void init_dsu()
{
	for (int i = 1; i <= ivc; i++)
	{
		fa[i] = i;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = getrt(fa[x]);
}

void merge(int x, int y)
{
	fa[getrt(x)] = getrt(y);
}

void dfs(int u, int prev)
{
	V[u].vis = true;
	V[u].fa = prev;
	ancestor[u] = u;
	for (unsigned int i = 0; i < V[u].queries.size(); i++)
	{
		if (V[V[u].queries[i].b].vis == true)
		{
			V[u].queries[i].ans = ancestor[getrt(V[u].queries[i].b)];
		}
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != prev)
		{
			dfs(E[cur].endp, u);
			merge(u, E[cur].endp);
			ancestor[getrt(u)] = u;
		}
	}
}

void get_ans(int u, int prev)
{
	int sum = 0;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != prev)
		{
			get_ans(E[cur].endp, u);
			sum += V[E[cur].endp].ans;
		}
	}
	V[u].ans = sum + V[u].sub;
}

int main()
{
	int u, v;
	scanf("%d", &ivc);
	for (int i = 0; i < ivc; i++)
	{
		scanf("%d", &room[i]);
	}
	for (int i = 1; i < ivc; i++)
	{
		V[room[i]].queries.push_back(query(room[i], room[i - 1]));
		V[room[i - 1]].queries.push_back(query(room[i - 1], room[i]));
	}
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	init_dsu();
	dfs(1, 0);
	for (int i = 1; i <= ivc; i++)
	{
		for (unsigned int j = 0; j < V[i].queries.size(); j++)
		{
			int a = i, b = V[i].queries[j].b, l = V[i].queries[j].ans;
			if (l != 0)
			{
				if (l == a) V[b].sub++, V[V[l].fa].sub--;
				else if (l == b) V[a].sub++, V[V[l].fa].sub--;
				else V[a].sub++, V[b].sub++, V[l].sub--, V[V[l].fa].sub--;
			}
		}
	}
	get_ans(1, 0);
	for (int i = 1; i < ivc; i++)
	{
		V[room[i]].ans--;
	}
	for (int i = 1; i <= ivc; i++)
	{
		printf("%d\n", V[i].ans);
	}
	return 0;
}
