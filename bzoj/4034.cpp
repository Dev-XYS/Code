// Problem Name: 树上操作
// Source: [HAOI2015]

#include <cstdio>

#define NIL 0

typedef long long ll;

using namespace std;

struct vertex
{
	int first, fa, size, son, top, ord;
}V[100010];

struct edge
{
	int endp, next;
}E[200010];

struct node
{
	node *lch, *rch;
	ll sum, add;
	node() : lch(NIL), rch(NIL), sum(0), add(0) { }
}*root;

int n, m, w[100010], ec = 1, ord, map[100010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs1(int u, int fa)
{
	V[u].fa = fa;
	int maxsize = 0;
	for (int cur = V[u].first; cur != NIL; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			dfs1(E[cur].endp, u);
			if (V[E[cur].endp].size > maxsize) V[u].son = E[cur].endp, maxsize = V[E[cur].endp].size;
			V[u].size += V[E[cur].endp].size;
		}
	}
	V[u].size++;
}

void dfs2(int u, int top)
{
	V[u].ord = ++ord, map[ord] = u;
	V[u].top = top;
	if (V[u].son != NIL) dfs2(V[u].son, top);
	for (int cur = V[u].first; cur != NIL; cur = E[cur].next)
	{
		if (E[cur].endp != V[u].son && E[cur].endp != V[u].fa) dfs2(E[cur].endp, E[cur].endp);
	}
}

void push_down(node *u, int l, int r)
{
	if (u->add != 0)
	{
		int mid = (l + r) >> 1;
		u->lch->add += u->add;
		u->lch->sum += u->add * (ll)(mid - l + 1);
		u->rch->add += u->add;
		u->rch->sum += u->add * (ll)(r - mid);
		u->add = 0;
	}
}

void update(node *u)
{
	u->sum = u->lch->sum + u->rch->sum;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r) u->sum = w[map[l]];
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		update(u);
	}
}

void modify_add(node *u, int l, int r, int ql, int qr, int x)
{
	if (l == ql && r == qr) u->add += (ll)x, u->sum += (ll)x * (ll)(r - l + 1);
	else
	{
		push_down(u, l, r);
		int mid = (l + r) >> 1;
		if (qr <= mid) modify_add(u->lch, l, mid, ql, qr, x);
		else if (ql > mid) modify_add(u->rch, mid + 1, r, ql, qr, x);
		else modify_add(u->lch, l, mid, ql, mid, x), modify_add(u->rch, mid + 1, r, mid + 1, qr, x);
		update(u);
	}
}

ll query_sum(node *u, int l, int r, int ql, int qr)
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

ll tree_query_sum(int u)
{
	ll res = 0;
	while (u != NIL)
	{
		res += query_sum(root, 1, n, V[V[u].top].ord, V[u].ord);
		u = V[V[u].top].fa;
	}
	return res;
}

void tree_modify_subtree(int u, int x)
{
	modify_add(root, 1, n, V[u].ord, V[u].ord + V[u].size - 1, x);
}

void tree_modify_vertex(int u, int x)
{
	modify_add(root, 1, n, V[u].ord, V[u].ord, x);
}

int main()
{
	int op, u, v, x;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(root, 1, n);
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d", &u, &x);
			tree_modify_vertex(u, x);
		}
		else if (op == 2)
		{
			scanf("%d%d", &u, &x);
			tree_modify_subtree(u, x);
		}
		else
		{
			scanf("%d", &u);
			printf("%lld\n", tree_query_sum(u));
		}
	}
	return 0;
}
