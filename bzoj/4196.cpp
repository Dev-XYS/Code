// Problem Name: 软件包管理器
// Source: [NOI2015]

#include <cstdio>

#define NIL 0

using namespace std;

struct vertex
{
	int first, fa, depth, size, son, top, ord;
}V[100010];

struct edge
{
	int endp, next;
}E[100010];

struct node
{
	node *lch, *rch;
	int sum, same;
	node() : lch(NIL), rch(NIL), sum(0), same(-1) { }
}*root;

int n, m, ec = 1, ord;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs1(int u, int fa, int depth)
{
	V[u].fa = fa;
	V[u].depth = depth;
	int maxsize = 0;
	for (int cur = V[u].first; cur != NIL; cur = E[cur].next)
	{
		dfs1(E[cur].endp, u, depth + 1);
		if (V[E[cur].endp].size > maxsize) V[u].son = E[cur].endp, maxsize = V[E[cur].endp].size;
		V[u].size += V[E[cur].endp].size;
	}
	V[u].size++;
}

void dfs2(int u, int top)
{
	V[u].ord = ++ord;
	V[u].top = top;
	if (V[u].son != NIL) dfs2(V[u].son, top);
	for (int cur = V[u].first; cur != NIL; cur = E[cur].next)
	{
		if (E[cur].endp != V[u].son) dfs2(E[cur].endp, E[cur].endp);
	}
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

void push_down(node *u, int l, int r)
{
	if (u->lch != NIL && u->same != -1)
	{
		int mid = (l + r) >> 1;
		u->lch->same = u->same;
		u->lch->sum = u->same * (mid - l + 1);
		u->rch->same = u->same;
		u->rch->sum = u->same * (r - mid);
		u->same = -1;
	}
}

void update(node *u)
{
	u->sum = u->lch->sum + u->rch->sum;
}

void modify_same(node *u, int l, int r, int ql, int qr, int x)
{
	if (l == ql && r == qr) u->same = x, u->sum = x * (r - l + 1);
	else
	{
		push_down(u, l, r);
		int mid = (l + r) >> 1;
		if (qr <= mid) modify_same(u->lch, l, mid, ql, qr, x);
		else if (ql > mid) modify_same(u->rch, mid + 1, r, ql, qr, x);
		else modify_same(u->lch, l, mid, ql, mid, x), modify_same(u->rch, mid + 1, r, mid + 1, qr, x);
		update(u);
	}
}

int query_sum(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr) return u->sum;
	else
	{
		push_down(u, l, r);
		int mid = (l + r) >> 1;
		if (qr <= mid) return query_sum(u->lch, l, mid, ql, qr);
		else if (ql > mid) return query_sum(u->rch, mid + 1, r, ql, qr);
		else return query_sum(u->lch, l, mid, ql, mid) + query_sum(u->rch, mid + 1, r, mid + 1, qr);
	}
}

int tree_query_sum(int u)
{
	int res = 0;
	while (u != NIL)
	{
		res += query_sum(root, 1, n, V[V[u].top].ord, V[u].ord);
		u = V[V[u].top].fa;
	}
	return res;
}

void tree_modify_same_to_1(int u)
{
	while (u != NIL)
	{
		modify_same(root, 1, n, V[V[u].top].ord, V[u].ord, 1);
		u = V[V[u].top].fa;
	}
}

int tree_query_subtree_sum(int u)
{
	return query_sum(root, 1, n, V[u].ord, V[u].ord + V[u].size - 1);
}

void tree_modify_subtree_to_0(int u)
{
	modify_same(root, 1, n, V[u].ord, V[u].ord + V[u].size - 1, 0);
}

int install(int u)
{
	int res = V[u].depth - tree_query_sum(u);
	tree_modify_same_to_1(u);
	return res;
}

int uninstall(int u)
{
	int res = tree_query_subtree_sum(u);
	tree_modify_subtree_to_0(u);
	return res;
}

int main()
{
	int u;
	char op[10];
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
	{
		scanf("%d", &u);
		add_edge(u + 1, i);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(root, 1, n);
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s%d", op, &u);
		if (op[0] == 'i') printf("%d\n", install(u + 1));
		else printf("%d\n", uninstall(u + 1));
	}
	return 0;
}
