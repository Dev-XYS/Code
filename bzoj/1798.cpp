// Problem Name: 维护序列 seq

#include <cstdio>

#define NIL 0

typedef long long ll;

using namespace std;

struct node
{
	node *lch, *rch;
	ll sum, add, mul;
	node() : lch(NIL), rch(NIL), sum(0), add(0), mul(1) { }
}*root;

int n, m;
ll p, d[100010];

void update(node *u)
{
	u->sum = (u->lch->sum + u->rch->sum) % p;
}

void push_down(node *u, int l, int r)
{
	if (u->lch != NIL)
	{
		int mid = (l + r) >> 1;
		((u->lch->add *= u->mul) += u->add) %= p;
		(u->lch->mul *= u->mul) %= p;
		((u->lch->sum *= u->mul) += u->add * (ll)(mid - l + 1)) %= p;
		((u->rch->add *= u->mul) += u->add) %= p;
		(u->rch->mul *= u->mul) %= p;
		((u->rch->sum *= u->mul) += u->add * (ll)(r - mid)) %= p;
	}
	u->add = 0, u->mul = 1;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r) u->sum = d[l] % p;
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		update(u);
	}
}

void modify_add(node *u, int l, int r, int ql, int qr, ll x)
{
	push_down(u, l, r);
	if (l == ql && r == qr)
	{
		u->add = x;
		(u->sum += x * (ll)(r - l + 1)) %= p;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid)
		{
			modify_add(u->lch, l, mid, ql, qr, x);
		}
		else if (ql > mid)
		{
			modify_add(u->rch, mid + 1, r, ql, qr, x);
		}
		else
		{
			modify_add(u->lch, l, mid, ql, mid, x);
			modify_add(u->rch, mid + 1, r, mid + 1, qr, x);
		}
		update(u);
	}
}

void modify_mul(node *u, int l, int r, int ql, int qr, ll x)
{
	push_down(u, l, r);
	if (l == ql && r == qr)
	{
		u->mul = x;
		(u->sum *= x) %= p;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (qr <= mid)
		{
			modify_mul(u->lch, l, mid, ql, qr, x);
		}
		else if (ql > mid)
		{
			modify_mul(u->rch, mid + 1, r, ql, qr, x);
		}
		else
		{
			modify_mul(u->lch, l, mid, ql, mid, x);
			modify_mul(u->rch, mid + 1, r, mid + 1, qr, x);
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
		return (query(u->lch, l, mid, ql, qr) * u->mul + u->add * (ll)(qr - ql + 1)) % p;
	}
	else if (ql > mid)
	{
		return (query(u->rch, mid + 1, r, ql, qr) * u->mul + u->add * (ll)(qr - ql + 1)) % p;
	}
	else
	{
		return ((query(u->lch, l, mid, ql, mid) + query(u->rch, mid + 1, r, mid + 1, qr)) * u->mul + u->add * (ll)(qr - ql + 1)) % p;
	}
}

int main()
{
	int op, l, r;
	ll x;
	scanf("%d%lld", &n, &p);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &d[i]);
	}
	build(root, 1, n);
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d%lld", &l, &r, &x);
			modify_mul(root, 1, n, l, r, x % p);
		}
		else if (op == 2)
		{
			scanf("%d%d%lld", &l, &r, &x);
			modify_add(root, 1, n, l, r, x % p);
		}
		else
		{
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(root, 1, n, l, r));
		}
	}
	return 0;
}
