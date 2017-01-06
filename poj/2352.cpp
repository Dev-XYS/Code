#include <cstdio>
#include <algorithm>

#define NODE_COUNT 100000

using namespace std;

struct node
{
	node *lch, *rch;
	int sum, lazy;
	node(int _sum = 0) : sum(_sum) { lch = rch = 0; lazy = 0; }
	void* operator new (size_t);
}*root, pool[NODE_COUNT];

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

struct point
{
	int x, y;
}d[15010];

int n, res[15010];

void build(node *&u, int l, int r)
{
	u = new node(0);
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

void modify(node *u, int l, int r, int s, int t, int del)
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

int query(node *u, int l, int r, int s, int t)
{
	if (l == s && r == t)
	{
		return u->sum;
	}
	else
	{
		int mid = (l + r) >> 1;
		int res;
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

bool _point_cmp(point x, point y)
{
	if (x.y != y.y)
	{
		return x.y < y.y;
	}
	return x.x < y.x;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &d[i].x, &d[i].y);
	}
	sort(d, d + n, _point_cmp);
	build(root, 0, 32000);
	for (int i = 0; i < n; i++)
	{
		modify(root, 0, 32000, d[i].x, 32000, 1);
		res[query(root, 0, 32000, d[i].x, d[i].x)]++;
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", res[i]);
	}
	return 0;
}
