// Problem Name: Gty的妹子树
// Problem Author: Autumn

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct vertex
{
	int first, w, fa, block, top;
}V[60010];

struct edge
{
	int endp, next;
}E[120010];

int n, m, ec = 2, S, bc, size[60010];
vector<int> ele[60010], nb[60010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void insert_into_block(int block, int w)
{
	int l = 0, r = size[block] - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (ele[block][mid] > w) r = mid;
		else l = mid + 1;
	}
	ele[block].insert(ele[block].begin() + l, w);
}

void remove_from_block(int block, int w)
{
	int l = 0, r = size[block] - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (ele[block][mid] >= w) r = mid;
		else l = mid + 1;
	}
	ele[block].erase(ele[block].begin() + l);
}

void make_fa(int u, int fa)
{
	if (size[V[fa].block] < S)
	{
		V[u].block = V[fa].block;
		V[u].top = V[fa].top;
	}
	else
	{
		V[u].block = ++bc;
		V[u].top = u;
		nb[V[fa].block].push_back(u);
	}
	size[V[u].block]++;
	insert_into_block(V[u].block, V[u].w);
}

void dfs(int u, int fa)
{
	V[u].fa = fa;
	make_fa(u, fa);
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			dfs(E[cur].endp, u);
		}
	}
}

void build()
{
	V[1].top = 1;
	size[0] = 1;
	ele[0].push_back(V[1].w);
	for (int cur = V[1].first; cur != 0; cur = E[cur].next)
	{
		dfs(E[cur].endp, 1);
	}
}

int query_whole(int u, int w)
{
	int l = 0, r = size[V[u].block] - 1;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (ele[V[u].block][mid] <= w) l = mid;
		else r = mid - 1;
	}
	int res = ele[V[u].block][0] > w ? size[V[u].block] : size[V[u].block] - 1 - l;
	for (int i = 0; i < (int)nb[V[u].block].size(); i++)
	{
		res += query_whole(nb[V[u].block][i], w);
	}
	return res;

}

int query(int u, int w)
{
	if (V[u].top == u)
	{
		return query_whole(u, w);
	}
	int res = (int)(V[u].w > w);
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != V[u].fa)
		{
			res += query(E[cur].endp, w);
		}
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d\n", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].w);
	}
	S = sqrt(n) * 32;
	build();
	scanf("%d", &m);
	int op, x, lastans = 0;
	while (m--)
	{
		scanf("%d%d%d", &op, &u, &x);
		u ^= lastans;
		x ^= lastans;
		if (op == 0)
		{
			printf("%d\n", lastans = query(u, x));
		}
		else if (op == 1)
		{
			remove_from_block(V[u].block, V[u].w);
			V[u].w = x;
			insert_into_block(V[u].block, V[u].w);
		}
		else
		{
			V[++n].w = x;
			make_fa(n, u);
			add_edge(u, n);
		}
	}
	return 0;
}
