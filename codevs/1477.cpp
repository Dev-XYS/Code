// Problem Name: 永无乡
// Source: [HNOI2012]

#include <cstdio>
#include <algorithm>

#define NIL 0

using namespace std;

int n, m, q;
int ch[100010][2], fa[100010], key[100010], size[100010];

inline int which(int u)
{
	return ch[fa[u]][0] == u ? 0 : 1;
}

inline void update(int u)
{
	size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
}

void rotate(int u)
{
	int k1 = which(u);
	int c = ch[u][k1 ^ 1];
	int p = fa[u];
	int g = fa[p];
	int k0 = which(p);
	fa[c] = p;
	fa[u] = g;
	fa[p] = u;
	ch[g][k0] = u;
	ch[p][k1] = c;
	ch[u][k1 ^ 1] = p;
	update(p);
	update(u);
}

void splay(int u, int tar)
{
	while (fa[u] != tar)
	{
		if (fa[fa[u]] != tar)
		{
			if (which(u) == which(fa[u])) rotate(fa[u]);
			else rotate(u);
		}
		rotate(u);
	}
}

int find_kth(int u, int k)
{
	if (size[u] < k) return -1;
	while (size[ch[u][0]] != k - 1)
	{
		if (size[ch[u][0]] < k) k -= size[ch[u][0]] + 1, u = ch[u][1];
		else u = ch[u][0];
	}
     	splay(u, NIL);
	return u;
}

void insert(int u, int rt)
{
	while (true)
	{
		int &next = key[u] < key[rt] ? ch[rt][0] : ch[rt][1];
		if (next == NIL)
		{
			next = u;
			fa[u] = rt;
			ch[u][0] = ch[u][1] = NIL;
			size[u] = 1;
			splay(u, NIL);
			break;
		}
		size[rt]++;
		rt = next;
	}
}

int seq[100010], sc;
void dfs(int v)
{
	seq[sc++] = v;
	if (ch[v][0] != NIL) dfs(ch[v][0]);
	if (ch[v][1] != NIL) dfs(ch[v][1]);
}

void merge(int u, int v)
{
	if (u == v) return;
	splay(u, NIL);
	splay(v, NIL);
	if (fa[u] != NIL || fa[v] != NIL) return;
	if (size[u] < size[v]) swap(u, v);
	sc = 0, dfs(v);
	insert(seq[0], u);
	for (int i = 1; i < sc; i++)
	{
		insert(seq[i], seq[i - 1]);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &key[i]);
		size[i] = 1;
	}
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		merge(u, v);
	}
	scanf("%d", &q);
	char op[10];
	int x, y;;
	while (q--)
	{
		scanf("%s%d%d", op, &x, &y);
		if (op[0] == 'B') merge(x, y);
		else
		{
			splay(x, NIL);
			printf("%d\n", find_kth(x, y));
		}
	}
	return 0;
}
