// Problem Name: 楼房重建
// Source: 中国国家集训队清华集训 2012~2013 第一天

#include <cstdio>

using namespace std;

struct node
{
	node *lch, *rch;
	int cnt;
	double maxk;
}*root;

int n, m;

inline double max(double x, double y)
{
	return x > y ? x : y;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

int count(node *u, int l, int r, double restriction)
{
	if (l == r) return u->maxk > restriction ? 1 : 0;
	if (u->maxk <= restriction) return 0;
	int mid = (l + r) >> 1;
	double lk = u->lch->maxk;
	if (lk <= restriction) return count(u->rch, mid + 1, r, restriction);
	else return count(u->lch, l, mid, restriction) + (u->cnt - u->lch->cnt);
}

void modify(node *u, int l, int r, int p, int h)
{
	if (l == r) u->maxk = (double)h / (double)p, u->cnt = 1;
	else
	{
		int mid = (l + r) >> 1;
		if (p <= mid) modify(u->lch, l, mid, p, h);
		else modify(u->rch, mid + 1, r, p, h);
		u->maxk = max(u->lch->maxk, u->rch->maxk);
		u->cnt = u->lch->cnt + count(u->rch, mid + 1, r, u->lch->maxk);
	}
}

int main()
{
	int p, h;
	scanf("%d%d", &n, &m);
	build(root, 1, n);
	while (m--)
	{
		scanf("%d%d", &p, &h);
		modify(root, 1, n, p, h);
		printf("%d\n", root->cnt);
	}
	return 0;
}
