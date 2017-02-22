#include <cstdio>
#include <cassert>

#define ensure(x) assert(x)

#define NIL 0
#define ELEMENT_COUNT 100000

using namespace std;

int n, m, d[80010];
int ch[ELEMENT_COUNT][2], fa[ELEMENT_COUNT], key[ELEMENT_COUNT], size[ELEMENT_COUNT], use = 0, root;

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
	int p = fa[u];
	int q = fa[p];
	int uk = which(u), pk = which(p);
	int c = ch[u][uk ^ 1];
	fa[c] = p;
	fa[u] = q;
	fa[p] = u;
	ch[p][uk] = ch[u][uk ^ 1];
	ch[u][uk ^ 1] = p;
	ch[q][pk] = u;
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
	if (tar == 0) root = u;
}

void build(int &u, int prev, int l, int r)
{
	if (l <= r)
	{
		int mid = (l + r) >> 1;
		u = d[mid];
		fa[u] = prev;
		build(ch[u][0], u, l, mid - 1);
		build(ch[u][1], u, mid + 1, r);
		update(u);
	}
}

int cmp(int ikey, int ukey)
{
	return ikey < ukey ? 0 : 1;
}

void insert(int ikey)
{
	if (root == NIL) root = ++use, ch[use][0] = ch[use][1] = fa[use] = NIL, key[use] = ikey;
	else
	{
		int u = root;
		while (key[u] != ikey)
		{
			int k = cmp(ikey, key[u]);
			if (k == -1) break;
			if (ch[u][k] == NIL) ch[u][k] = ++use, fa[use] = u, key[use] = ikey;
			u = ch[u][k];
		}
		splay(u, NIL);
	}
}

int find(int fkey)
{
	int u = root;
	while (u != NIL)
	{
		if (key[u] == fkey) break;
		else u = ch[u][cmp(fkey, key[u])];
	}
	splay(u, NIL);
	return u;
}

int find_max(int u)
{
	int tar = fa[u];
	while (ch[u][1] != NIL)
	{
		u = ch[u][1];
	}
	splay(u, tar);
	return u;
}

int join(int u, int v)
{
	if (u == NIL && v == NIL) return NIL;
	else if (u == NIL) u = v, v = NIL;
	u = find_max(u);
	ch[u][1] = v;
	fa[v] = u;
	update(u);
	return u;
}

void remove(int ord)
{
	splay(ord, NIL);
	root = join(ch[ord][0], ch[ord][1]);
	fa[root] = NIL;
}

void insert_min(int ord)
{
	int u = root;
	while (ch[u][0] != NIL)
	{
		u = ch[u][0];
	}
	ch[u][0] = ord;
	fa[ord] = u;
	ch[ord][0] = ch[ord][1] = NIL;
	size[ord] = 1;
	splay(ord, NIL);
}

void insert_max(int ord)
{
	int u = root;
	while (ch[u][1] != NIL)
	{
		u = ch[u][1];
	}
	ch[u][1] = ord;
	fa[ord] = u;
	ch[ord][0] = ch[ord][1] = NIL;
	size[ord] = 1;
	splay(ord, NIL);
}

int find_kth(int k, int tar)
{
	int u = root;
	while (k != size[ch[u][0]] + 1)
	{
		int dir = cmp(k, size[ch[u][0]] + 1);
		if (dir == 1) k -= size[ch[u][0]] + 1;
		u = ch[u][dir];
	}
	splay(u, tar);
	return u;
}

void print_seq(int u)
{
	if (u != 0)
	{
		print_seq(ch[u][0]);
		printf("%d ", u);
		print_seq(ch[u][1]);
	}
}

int main()
{
	char op[10];
	int s, t, k;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build(root, NIL, 1, n);
	while (m--)
	{
		scanf("%s", op);
		switch (op[0])
		{
		case 'T':
			scanf("%d", &s);
			remove(s);
			insert_min(s);
			break;
		case 'B':
			scanf("%d", &s);
			remove(s);
			insert_max(s);
			break;
		case 'I':
			scanf("%d%d", &s, &t);
			splay(s, NIL);
			k = size[ch[root][0]] + 1;
			remove(s);
			if (k + t == 1) insert_min(s);
			else if (k + t == n) insert_max(s);
			else
			{
				find_kth(k + t - 1, NIL);
				find_kth(k + t, root);
				ch[ch[root][1]][0] = s;
				fa[s] = ch[root][1];
				ch[s][0] = ch[s][1] = NIL;
				size[s] = 1;
				update(ch[root][1]);
				update(root);
			}
			break;
		case 'A':
			scanf("%d", &s);
			splay(s, NIL);
			printf("%d\n", size[ch[root][0]]);
			break;
		case 'Q':
			scanf("%d", &s);
			printf("%d\n", find_kth(s, NIL));
			break;
		}
		ensure(size[root] == n);
	}
	return 0;
}
