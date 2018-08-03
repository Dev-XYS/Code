// Problem Name: 【模板】线段树 2

#include <cstdio>

#define NIL 0

typedef long long ll;

using namespace std;

struct node
{
	node *lch, *rch;
	int sum, mul, add;
	node() : lch(NIL), rch(NIL), mul(1), add(0) { }
}*root;

int n, m, p, a[100010];

void update(node *u)
{
	u->sum = (u->lch->sum + u->rch->sum) % p;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(u->lch, l, mid);
	build(u->rch, mid + 1, r);
	update(u);
}

void refresh(node *u, int l, int r, int mul, int add)
{
	u->sum = (ll)u->sum * mul % p;
	u->sum = (u->sum + (ll)add * (r - l + 1)) % p;
	u->mul = (ll)u->mul * mul % p;
	u->add = ((ll)u->add * mul + add) % p;
}

void push_down(node *u, int l, int r)
{
	if (u->mul != 1 || u->add != 0)
	{
		int mid = (l + r) >> 1;
		refresh(u->lch, l, mid, u->mul, u->add);
		refresh(u->rch, mid + 1, r, u->mul, u->add);
		u->mul = 1;
		u->add = 0;
	}
}

void modify(node *u, int l, int r, int ql, int qr, int mul, int add)
{
	if (l == ql && r == qr)
	{
		refresh(u, l, r, mul, add);
		return;
	}
	push_down(u, l, r);
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		modify(u->lch, l, mid, ql, qr, mul, add);
	}
	else if (ql > mid)
	{
		modify(u->rch, mid + 1, r, ql, qr, mul, add);
	}
	else
	{
		modify(u->lch, l, mid, ql, mid, mul, add);
		modify(u->rch, mid + 1, r, mid + 1, qr, mul, add);
	}
	update(u);
}

int query(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->sum;
	}
	push_down(u, l, r);
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
		return (query(u->lch, l, mid, ql, mid) + query(u->rch, mid + 1, r, mid + 1, qr)) % p;
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	build(root, 1, n);
	int op, l, r, x;
	while (m--)
	{
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1)
		{
			scanf("%d", &x);
			modify(root, 1, n, l, r, x, 0);
		}
		else if (op == 2)
		{
			scanf("%d", &x);
			modify(root, 1, n, l, r, 1, x);
		}
		else
		{
			printf("%d\n", query(root, 1, n, l, r));
		}
	}
	return 0;
}
