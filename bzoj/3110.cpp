// Problem Name: K大数查询
// Source: [ZJOI2013]

#include <cstdio>

#define NIL 0

typedef unsigned int u32;

using namespace std;

struct rnode
{
	rnode *lch, *rch;
	u32 sum, lazy;
	rnode() : lch(NIL), rch(NIL), sum(0), lazy(0) { }
};

struct wnode
{
	wnode *lch, *rch;
	rnode *root;
	wnode() : lch(NIL), rch(NIL), root(NIL) { }
}*root;

int n, m;

u32 query(rnode *u, int l, int r, int ql, int qr)
{
	if (u == NIL) return 0;
	if (l == ql && r == qr) return u->sum;
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(u->lch, l, mid, ql, qr) + u->lazy * (qr - ql + 1);
	else if (ql > mid) return query(u->rch, mid + 1, r, ql, qr) + u->lazy * (qr - ql + 1);
	else return query(u->lch, l, mid, ql, mid) + query(u->rch, mid + 1, r, mid + 1, qr) + u->lazy * (qr - ql + 1);
}

int find_kth(wnode *u, int l, int r, int ql, int qr, u32 k)
{
	if (l == r) return l;
	u32 q = query(u->rch->root, 1, n, ql, qr);
	if (k > q) return find_kth(u->lch, l, (l + r) >> 1, ql, qr, k - q);
	else return find_kth(u->rch, ((l + r) >> 1) + 1, r, ql, qr, k);
}

void interval_add(rnode *&u, int l, int r, int ql, int qr)
{
	if (u == NIL) u = new rnode;
	u->sum += qr - ql + 1;
	if (l == ql && r == qr) u->lazy++;
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid) interval_add(u->lch, l, mid, ql, qr);
		else if (ql > mid) interval_add(u->rch, mid + 1, r, ql, qr);
		else interval_add(u->lch, l, mid, ql, mid), interval_add(u->rch, mid + 1, r, mid + 1, qr);
	}
}

void insert(wnode *u, int l, int r, int ql, int qr, int x)
{
	interval_add(u->root, 1, n, ql, qr);
	if (l < r)
	{
		int mid = (l + r) >> 1;
		if (x <= mid) insert(u->lch, l, mid, ql, qr, x);
		else insert(u->rch, mid + 1, r, ql, qr, x);
	}
}

void build(wnode *&u, int l, int r)
{
	u = new wnode;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

int main()
{
	int op, l, r, x;
	scanf("%d%d", &n, &m);
	build(root, 1, n);
	while (m--)
	{
		scanf("%d%d%d%d", &op, &l, &r, &x);
		if (op == 1)
		{
			insert(root, 1, n, l, r, x);
		}
		else
		{
			printf("%d\n", find_kth(root, 1, n, l, r, x));
		}
	}
	return 0;
}
