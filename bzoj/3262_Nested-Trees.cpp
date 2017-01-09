#include <cstdio>
#include <algorithm>

#define LOWBIT(x) ((x) & (-(x)))

#define ELEMENT_COUNT 100010
#define MAX_PROPERTY 200010
#define POOL_SIZE 8000010

using namespace std;

struct point
{
	int a, b, c, cnt;
}d[ELEMENT_COUNT];

bool operator == (const point &x, const point &y)
{
	return x.a == y.a && x.b == y.b && x.c == y.c;
}

struct node
{
	node *lch, *rch;
	int sum;
	node(int _sum = 0);
	void* operator new (size_t);
}*root[MAX_PROPERTY], *nil, pool[POOL_SIZE];

node::node(int _sum) : sum(_sum)
{
	lch = rch = nil;
}

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

int n, k, cnt[ELEMENT_COUNT];

void init()
{
	top = 0;
	nil = new node;
	for (int i = 1; i <= k; i++)
	{
		root[i] = nil;
	}
}

void modify(node *&u, int l, int r, int k, int x)
{
	if (u == nil)
	{
		u = new node;
	}
	if (l == r)
	{
		u->sum += x;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			modify(u->lch, l, mid, k, x);
		}
		else
		{
			modify(u->rch, mid + 1, r, k, x);
		}
		u->sum = u->lch->sum + u->rch->sum;
	}
}

int query(node *&u, int l, int r, int ql, int qr)
{
	if (u == nil)
	{
		return 0;
	}
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

bool _point_x_cmp_(point x, point y)
{
	if (x.a != y.a) return x.a < y.a;
	if (x.b != y.b) return x.b < y.b;
	return x.c < y.c;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &d[i].a, &d[i].b, &d[i].c);
	}
	sort(d + 1, d + n + 1, _point_x_cmp_);
	init();
	int sc = 1;
	for (int i = 1; i <= n; i++)
	{
		if (d[i + 1] == d[i])
		{
			sc++;
			continue;
		}
		int ans = 0, x = d[i].b;
		while (x > 0)
		{
			ans += query(root[x], 1, k, 1, d[i].c);
			x -= LOWBIT(x);
		}
		x = d[i].b;
		while (x <= k)
		{
			modify(root[x], 1, k, d[i].c, sc);
			x += LOWBIT(x);
		}
		ans += sc - 1;
		cnt[ans] += sc;
		sc = 1;
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", cnt[i]);
	}
	return 0;
}
