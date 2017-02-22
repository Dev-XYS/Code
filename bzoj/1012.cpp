#include <cstdio>

typedef long long ll;

using namespace std;

struct node
{
	node *ch[2];
	ll max;
	node() { ch[0] = ch[1] = 0, max = 0; }
}*root;

int m;
ll d;

inline ll max(ll x, ll y)
{
	return x > y ? x : y;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->ch[0], l, mid);
		build(u->ch[1], mid + 1, r);
	}
}

void modify(node *u, int l, int r, int k, ll x)
{
	if (l == r)
	{
		u->max = x;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			modify(u->ch[0], l, mid, k, x);
		}
		else
		{
			modify(u->ch[1], mid + 1, r, k, x);
		}
		u->max = max(u->ch[0]->max, u->ch[1]->max);
	}
}

ll query(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr) return u->max;
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(u->ch[0], l, mid, ql, qr);
	else if (ql > mid) return query(u->ch[1], mid + 1, r, ql, qr);
	else return max(query(u->ch[0], l, mid, ql, mid), query(u->ch[1], mid + 1, r, mid + 1, qr));
}

int main()
{
	int end = 1;
	ll t = 0, x;
	char op[10];
	scanf("%d%lld", &m, &d);
	build(root, 1, m);
	for (int i = 0; i < m; i++)
	{
		scanf("%s%lld", op, &x);
		if (op[0] == 'A')
		{
			modify(root, 1, m, end++, (x + t) % d);
		}
		else
		{
			printf("%lld\n", t = query(root, 1, m, end - x, end - 1));
		}
	}
	return 0;
}
