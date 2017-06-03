// Problem Name: 花神游历各国
// Source: SPOJ - GSS4

#include <cstdio>
#include <cmath>
#include <algorithm>

#define NIL 0

typedef long long ll;

using namespace std;

struct node
{
	node *lch, *rch;
	double data;
	ll sum;
	bool clear;
	node(double _data = 0) : lch(NIL), rch(NIL), data(_data), sum(0), clear(false) { }
}*root;

int n, data[100010], m;

inline void update(node *u)
{
	u->sum = u->lch->sum + u->rch->sum;
	u->clear = u->lch->clear && u->rch->clear;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->data = data[l];
		u->sum = (ll)u->data;
		if (u->data < 2)
		{
			u->clear = true;
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		update(u);
	}
}

void modify(node *u, int l, int r, int ql, int qr)
{
	if (u->clear == true)
	{
		return;
	}
	if (l == r)
	{
		u->data = sqrt(u->data);
		u->sum = (ll)u->data;
		if (u->data < 2)
		{
			u->clear = true;
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid)
		{
			modify(u->lch, l, mid, ql, qr);
		}
		else if (ql > mid)
		{
			modify(u->rch, mid + 1, r, ql, qr);
		}
		else
		{
			modify(u->lch, l, mid, ql, mid);
			modify(u->rch, mid + 1, r, mid + 1, qr);
		}
		update(u);
	}
}


ll query(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->sum;
	}
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		return query(u->lch, l, mid, ql, qr);
	}
	else if (ql > mid)
	{
		return query(u->rch, mid + 1, r, ql, qr);
	}
	else
	{
		return query(u->lch, l, mid, ql, mid) + query(u->rch, mid + 1, r, mid + 1, qr);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &data[i]);
	}
	build(root, 1, n);
	scanf("%d", &m);
	int op, l, r;
	while (m--)
	{
		scanf("%d%d%d", &op, &l, &r);
		if (l > r) swap(l, r);
		if (op == 1)
		{
			printf("%lld\n", query(root, 1, n, l, r));
		}
		else
		{
			modify(root, 1, n, l, r);
		}
	}
	return 0;
}
