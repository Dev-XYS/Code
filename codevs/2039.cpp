// Problem Name: 骑马修栅栏
// Source: USACO 3.3.1

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct raw_edge
{
	int endp, ord;
	raw_edge(int _endp = 0, int _ord = 0) : endp(_endp), ord(_ord) { }
};

struct vertex
{
	int first, deg;
	vector<raw_edge> es;
}V[510];

struct edge
{
	int endp, next;
	bool vis;
}E[2058];

int iec, ec = 2, S[2058], sp;

inline void add_edge(int u, int v, int ord)
{
	E[ord].next = V[u].first;
	V[u].first = ord;
	E[ord].endp = v;
}

void dfs(int u)
{
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].vis == false) E[cur].vis = E[cur ^ 1].vis = true, dfs(E[cur].endp);
	}
	S[sp++] = u;
}

inline bool _raw_edge_endp_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.endp < y.endp;
}

int main()
{
	int u, v;
	scanf("%d", &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		V[u].deg++;
		V[v].deg++;
		V[u].es.push_back(raw_edge(v, ec++));
		V[v].es.push_back(raw_edge(u, ec++));
	}
	for (int i = 1; i <= 500; i++)
	{
		sort(V[i].es.begin(), V[i].es.end(), _raw_edge_endp_cmp_);
		for (int j = V[i].es.size() - 1; j >= 0; j--)
		{
			add_edge(i, V[i].es[j].endp, V[i].es[j].ord);
		}
	}
	int start = 0;
	for (int i = 1; i <= 500; i++)
	{
		if ((V[i].deg & 1) == 1)
		{
			start = i;
			break;
		}
		if (V[i].deg > 0 && start == 0) start = i;
	}
	dfs(start);
	for (int i = sp - 1; i >= 0; i--)
	{
		printf("%d\n", S[i]);
	}
	return 0;
}
