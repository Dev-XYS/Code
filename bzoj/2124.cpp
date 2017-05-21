// Problem Name: 等差子序列

#include <cstdio>
#include <cstring>

#define NIL 0

#define HC 2

typedef long long ll;

using namespace std;

struct node
{
	node *lch, *rch;
	int ltr[HC], rtl[HC];
	node() : lch(NIL), rch(NIL) { }
}*root;

struct query_return_info
{
	int ltr[HC], rtl[HC];
	query_return_info() { }
};

int T, n, d[10010], hmod[HC], hpow[HC][10010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	hmod[0] = 1000000007;
	hmod[1] = 1000000009;
	hpow[0][0] = hpow[1][0] = 1;
	for (int i = 1; i <= 10000; i++)
	{
		for (int h = 0; h < HC; h++)
		{
			hpow[h][i] = (ll)hpow[h][i - 1] * 2 % hmod[h];
		}
	}
}

inline void update(node *u, int l, int mid, int r)
{
	for (int h = 0; h < HC; h++)
	{
		u->ltr[h] = ((ll)u->lch->ltr[h] * hpow[h][r - mid] + u->rch->ltr[h]) % hmod[h];
		u->rtl[h] = ((ll)u->rch->rtl[h] * hpow[h][mid - l + 1] + u->lch->rtl[h]) % hmod[h];
	}
}

void build(node *&u, int l, int r)
{
	u = new node();
	if (l == r)
	{
		for (int h = 0; h < HC; h++)
		{
			u->ltr[h] = u->rtl[h] = 0;
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		update(u, l, mid, r);
	}
}

void modify(node *u, int l, int r, int p)
{
	if (l == r)
	{
		for (int h = 0; h < HC; h++)
		{
			u->ltr[h] = 1;
			u->rtl[h] = 1;
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		if (p <= mid) modify(u->lch, l, mid, p);
		else modify(u->rch, mid + 1, r, p);
		update(u, l, mid, r);
	}
}

query_return_info query(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		query_return_info ret;
		for (int h = 0; h < HC; h++)
		{
			ret.ltr[h] = u->ltr[h];
			ret.rtl[h] = u->rtl[h];
		}
		return ret;
	}
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(u->lch, l, mid, ql, qr);
	else if (ql > mid) return query(u->rch, mid + 1, r, ql, qr);
	else
	{
		query_return_info li = query(u->lch, l, mid, ql, mid), ri = query(u->rch, mid + 1, r, mid + 1, qr), ret;
		for (int h = 0; h < HC; h++)
		{
			ret.ltr[h] = ((ll)li.ltr[h] * hpow[h][qr - mid] + ri.ltr[h]) % hmod[h];
			ret.rtl[h] = ((ll)ri.rtl[h] * hpow[h][mid - ql + 1] + li.rtl[h]) % hmod[h];
		}
		return ret;
	}
}

void remove(node *u)
{
	if (u != NIL)
	{
		remove(u->lch);
		remove(u->rch);
		delete u;
	}
}

int main()
{
	scanf("%d", &T);
	init();
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &d[i]);
		}
		build(root, 1, n);
		for (int i = 1; i <= n; i++)
		{
			modify(root, 1, n, d[i]);
			int llen = d[i] - 1, rlen = n - d[i];
			int len = min(llen, rlen);
			if (len <= 0) continue;
			query_return_info l = query(root, 1, n, d[i] - len, d[i] - 1), r = query(root, 1, n, d[i] + 1, d[i] + len);
			for (int h = 0; h < HC; h++)
			{
				if (l.ltr[h] != r.rtl[h]) goto YES;
			}
		}
		printf("N\n");
		goto END;
	YES:
		printf("Y\n");
	END:;
	}
	return 0;
}
