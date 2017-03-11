// Problem Name: LCA
// Source: [LNOI2014]

#include <cstdio>
#include <algorithm>

#define NIL 0
#define MOD 201314

using namespace std;

struct vertex
{
	int first, fa, depth, size, son, top, ord;
}V[50010];

struct edge
{
	int endp, next;
}E[50010];

struct node
{
	node *lch, *rch;
	int sum, add;
	node() : lch(NIL), rch(NIL), sum(0), add(0) { }
}*root;

struct query
{
	int pos, z, ord;
	bool isright;
	query(int _pos = 0, int _z = 0, int _ord = 0, bool _isright = false) : pos(_pos), z(_z), ord(_ord), isright(_isright) { }
}iq[100010];

int n, m, ec = 1, qc, ord, ans[50010];

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
	if (u->add != 0)
	{
		int mid = (l + r) >> 1;
		(u->lch->add += u->add) %= MOD;
		(u->lch->sum += u->add * (mid - l + 1)) %= MOD;
		(u->rch->add += u->add) %= MOD;
		(u->rch->sum += u->add * (r - mid)) %= MOD;
		u->add = 0;
	}
}

void update(node *u)
{
	u->sum = (u->lch->sum + u->rch->sum) % MOD;
}

void modify_add(node *u, int l, int r, int ql, int qr, int x)
{
	if (l == ql && r == qr) (u->add += x) %= MOD, u->sum += x * (r - l + 1) % MOD;
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

int query_sum(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr) return u->sum;
	else
	{
		push_down(u, l, r);
		int mid = (l + r) >> 1;
		if (qr <= mid) return query_sum(u->lch, l, mid, ql, qr);
		else if (ql > mid) return query_sum(u->rch, mid + 1, r, ql, qr);
		else return (query_sum(u->lch, l, mid, ql, mid) + query_sum(u->rch, mid + 1, r, mid + 1, qr)) % MOD;
	}
}

void tree_modify_add_1(int u)
{
	while (u != NIL)
	{
		modify_add(root, 1, n, V[V[u].top].ord, V[u].ord, 1);
		u = V[V[u].top].fa;
	}
}

int tree_query_sum(int u)
{
	int res = 0;
	while (u != NIL)
	{
		(res += query_sum(root, 1, n, V[V[u].top].ord, V[u].ord)) %= MOD;
		u = V[V[u].top].fa;
	}
	return res;
}

inline bool _query_pos_cmp_(const query &x, const query &y)
{
	return x.pos < y.pos;
}

int main()
{
	int l, r, z;
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++)
	{
		scanf("%d", &z);
		add_edge(z + 1, i);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(root, 1, n);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &l, &r, &z);
		iq[qc++] = query(l, z + 1, i, false);
		iq[qc++] = query(r + 1, z + 1, i, true);
	}
	sort(iq, iq + qc, _query_pos_cmp_);
	int k = 0;
	for (int i = 0; i <= n; i++)
	{
		tree_modify_add_1(i);
		while (iq[k].pos == i)
		{
			if (iq[k].isright == true)
			{
				ans[iq[k].ord] = (tree_query_sum(iq[k].z) - ans[iq[k].ord] + MOD) % MOD;
			}
			else
			{
				ans[iq[k].ord] = tree_query_sum(iq[k].z);
			}
			k++;
		}
	}
	for (int i = 0; i < m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
