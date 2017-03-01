#include <cstdio>
#include <algorithm>

#define LOWBIT(x) ((x) & (-(x)))

using namespace std;

struct query
{
	int l, r, ord, ans;
}iq[200010];

int n, d[50010], q, back[1000010], last[50010], f[50010];

void modify(int p, int x)
{
	while (p <= n)
	{
		f[p] += x;
		p += LOWBIT(p);
	}
}

int prefix(int p)
{
	int res = 0;
	while (p > 0)
	{
		res += f[p];
		p -= LOWBIT(p);
	}
	return res;
}

bool _query_r_cmp_(const query &x, const query &y)
{
	return x.r < y.r;
}

bool _query_ord_cmp_(const query &x, const query &y)
{
	return x.ord < y.ord;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		scanf("%d%d", &iq[i].l, &iq[i].r);
		iq[i].ord = i;
	}
	sort(iq, iq + q, _query_r_cmp_);
	for (int i = 1; i <= n; i++)
	{
		if (back[d[i]] == 0) back[d[i]] = i;
		else last[i] = back[d[i]], back[d[i]] = i;
	}
	int p = 0;
	for (int i = 1; i <= n; i++)
	{
		if (last[i] != 0) modify(last[i], -1);
		modify(i, 1);
		while (iq[p].r == i)
		{
			iq[p].ans = prefix(iq[p].r) - prefix(iq[p].l - 1);
			p++;
		}
	}
	sort(iq, iq + q, _query_ord_cmp_);
	for (int i = 0; i < q; i++)
	{
		printf("%d\n", iq[i].ans);
	}
	return 0;
}
