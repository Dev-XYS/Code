#include <cstdio>
#include <algorithm>

#define ELEMENT_COUNT 100010
#define POOL_SIZE 2000010

using namespace std;

struct info
{
	int v, ord, nv;
}d[ELEMENT_COUNT];

struct node
{
	node *lch, *rch;
	int sum;
	node(int _sum = 0);
	void* operator new (size_t);
}*root[ELEMENT_COUNT], *nil, pool[POOL_SIZE];

node::node(int _sum) : sum(_sum)
{
	lch = rch = nil;
}

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

int n, m, map[ELEMENT_COUNT];

void init()
{
	top = 0;
	nil = new node;
	nil->lch = nil->rch = nil;
	root[0] = nil;
}

void insert(node *&u, node *old, int l, int r, int x)
{
	u = new node;
	if (l == r)
	{
		u->sum = old->sum + 1;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (x <= mid)
		{
			u->rch = old->rch;
			insert(u->lch, old->lch, l, mid, x);
		}
		else
		{
			u->lch = old->lch;
			insert(u->rch, old->rch, mid + 1, r, x);
		}
		u->sum = u->lch->sum + u->rch->sum;
	}
}

int query(node *ul, node *ur, int l, int r, int k)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	int del = ur->lch->sum - ul->lch->sum; 
	if (k <= del)
	{
		return query(ul->lch, ur->lch, l, mid, k);
	}
	else
	{
		return query(ul->rch, ur->rch, mid + 1, r, k - del);
	}
}

bool _info_v_cmp_(const info &x, const info &y)
{
	return x.v < y.v;
}

bool _info_ord_cmp_(const info &x, const info &y)
{
	return x.ord < y.ord;
}

void print(node *u, int l, int r)
{
	if (u != nil)
	{
		printf("[%d, %d] = %d ", l, r, u->sum);
		int mid = (l + r) >> 1;
		print(u->lch, l, mid);
		print(u->rch, mid + 1, r);
	}
}

int main()
{
	int l, r, k;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i].v);
		d[i].ord = i;
	}
	sort(d + 1, d + n + 1, _info_v_cmp_);
	d[0].v = -1000000001;
	for (int i = 1; i <= n; i++)
	{
		if (d[i].v != d[i - 1].v)
		{
			d[i].nv = d[i - 1].nv + 1;
			map[d[i].nv] = d[i].v;
		}
		else
		{
			d[i].nv = d[i - 1].nv;
		}
	}
	int _n = d[n].nv;
	sort(d + 1, d + n + 1, _info_ord_cmp_);
	init();
	for (int i = 1; i <= n; i++)
	{
		insert(root[i], root[i - 1], 1, _n, d[i].nv);
	}
	while (m--)
	{
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", map[query(root[l - 1], root[r], 1, _n, k)]);
	}
	return 0;
}
