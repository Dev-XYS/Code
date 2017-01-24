#include <cstdio>

#define NIL 0

using namespace std;

struct node
{
	node *ch[2];
	int sum, lazy;
	node(int _sum = 0) : sum(_sum) { ch[0] = ch[1] = NIL; }
}*root;

int n, m, d[100010];

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->sum = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->ch[0], l, mid);
		build(u->ch[1], mid + 1, r);
		u->sum = u->ch[0]->sum + u->ch[1]->sum;
	}
}

void modify(node *&u, int l, int r, int ql, int qr, int delta)
{
	if (l == ql && r == qr)
	{
		u->lazy += delta;
		u->sum += delta * (qr - ql + 1);
	}
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid)
		{
			modify(u->ch[0], l, mid, ql, qr, delta);
		}
		else if (ql > mid)
		{
			modify(u->ch[1], mid + 1, r, ql, qr, delta);
		}
		else
		{
			modify(u->ch[0], l, mid, ql, mid, delta);
			modify(u->ch[1], mid + 1, r, mid + 1, qr, delta);
		}
		u->sum = u->ch[0]->sum + u->ch[1]->sum;
	}
}

int query(node *&u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->sum;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid)
		{
			return query(u->ch[0], l, mid, ql, qr) + u->lazy * (qr - ql + 1);
		}
		else if (ql > mid)
		{
			return query(u->ch[1], mid + 1, r, ql, qr) + u->lazy * (qr - ql + 1);
		}
		else
		{
			return query(u->ch[0], l, mid, ql, mid) + query(u->ch[1], mid + 1, r, mid + 1, qr) + u->lazy * (qr - ql + 1);
		}
	}
}

int main()
{
	int op, x, A, a, b;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build(root, 1, n);
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d", &x, &A);
			modify(root, 1, n, x, x, A);
		}
		else
		{
			scanf("%d%d", &a, &b);
			printf("%d\n", query(root, 1, n, a, b));
		}
	}
	return 0;
}
