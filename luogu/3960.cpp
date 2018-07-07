// Problem Name: 列队
// Source: [NOIP2017], Day 2, Problem 3

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

struct node *nil;

struct node
{
	node *lch, *rch;
	int sum;
	ll id;
	node(int _sum = 0, ll _id = 0) : lch(nil), rch(nil), sum(_sum), id(_id) { }
}*root[300010], *tail;

int n, m, q, cnt[300010];

void build(node *&u, int l, int r)
{
	u = new node(max(min(n, r) - l + 1, 0), (ll)l * m);
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

void init()
{
	nil = new node();
	for (int i = 1; i <= n; i++)
	{
		root[i] = new node(m - 1);
		cnt[i] = m - 1;
	}
	build(tail, 1, n + q);
}

void setup_node(node *&u, int l, int r)
{
	u = new node(max(min(m - 1, r) - l + 1, 0));
}

ll remove(node *&u, int l, int r, int k)
{
	u->sum--;
	if (l == r)
	{
		return u->id == 0 ? -l : u->id;
	}
	int mid = (l + r) >> 1;
	if (u->lch == nil) setup_node(u->lch, l, mid);
	if (u->rch == nil) setup_node(u->rch, mid + 1, r);
	if (k <= u->lch->sum)
	{
		return remove(u->lch, l, mid, k);
	}
	else
	{
		return remove(u->rch, mid + 1, r, k - u->lch->sum);
	}
}

void insert(node *&u, int l, int r, int p, ll id)
{
	if (u == nil) setup_node(u, l, r);
	u->sum++;
	if (l == r)
	{
		u->id = id;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid)
	{
		insert(u->lch, l, mid, p, id);
	}
	else
	{
		insert(u->rch, mid + 1, r, p, id);
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	init();
	int x, y;
	for (int i = 1; i <= q; i++)
	{
		scanf("%d%d", &x, &y);
		ll ans, res;
		if (y != m)
		{
			ans = remove(root[x], 1, m + q, y);
			ans = ans < 0 ? (ll)(x - 1) * m - ans : ans;
			res = remove(tail, 1, n + q, x);
			insert(root[x], 1, m + q, ++cnt[x], res);
			insert(tail, 1, n + q, n + i, ans);
		}
		else
		{
			ans = remove(tail, 1, n + q, x);
			insert(tail, 1, n + q, n + i, ans);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
