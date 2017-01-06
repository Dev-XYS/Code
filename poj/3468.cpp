#include <cstdio>

#define ELEMENT_COUNT 100010
#define NODE_COUNT 200010

typedef long long ll;

using namespace std;

struct node
{
	node *lch, *rch;
	ll sum, lazy;
	node(ll _sum = 0) : sum(_sum) { lch = rch = 0; lazy = 0; }
	void* operator new (size_t);
}*root, pool[NODE_COUNT];

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

int n, m;
ll d[ELEMENT_COUNT];

void build(node *&u, int l, int r)
{
	u = new node(d[l]);
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		u->sum = u->lch->sum + u->rch->sum;
	}
}

void push_down(node *u, int l, int r, int mid)
{
	u->lch->sum += u->lazy * (mid - l + 1);
	u->lch->lazy += u->lazy;
	u->rch->sum += u->lazy * (r - mid);
	u->rch->lazy += u->lazy;
	u->lazy = 0;
}

void modify(node *u, int l, int r, int s, int t, ll del)
{
	if (l == s && r == t)
	{
		u->sum += del * (r - l + 1);
		u->lazy += del;
	}
	else
	{
		int mid = (l + r) >> 1;
		push_down(u, l, r, mid);
		if (t <= mid)
		{
			modify(u->lch, l, mid, s, t, del);
		}
		else if (s > mid)
		{
			modify(u->rch, mid + 1, r, s, t, del);
		}
		else
		{
			modify(u->lch, l, mid, s, mid, del);
			modify(u->rch, mid + 1, r, mid + 1, t, del);
		}
		u->sum = u->lch->sum + u->rch->sum;
	}
}

ll query(node *u, int l, int r, int s, int t)
{
	if (l == s && r == t)
	{
		return u->sum;
	}
	else
	{
		int mid = (l + r) >> 1;
		ll res;
		push_down(u, l, r, mid);
		if (t <= mid)
		{
			res = query(u->lch, l, mid, s, t);
		}
		else if (s > mid)
		{
			res = query(u->rch, mid + 1, r, s, t);
		}
		else
		{
			res = query(u->lch, l, mid, s, mid) + query(u->rch, mid + 1, r, mid + 1, t);
		}
		u->sum = u->lch->sum + u->rch->sum;
		return res;
	}
}

int main()
{
	char op[10];
	int l, r;
	ll c;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &d[i]);
	}
	build(root, 1, n);
	while (m--)
	{
		scanf("%s%d%d", op, &l, &r);
		if (op[0] == 'C')
		{
			scanf("%lld", &c);
			modify(root, 1, n, l, r, c);
		}
		else
		{
			printf("%lld\n", query(root, 1, n, l, r));
		}
	}
	return 0;
}
