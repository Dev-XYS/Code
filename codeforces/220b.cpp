#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct query
{
	int l, r, ord, ans;
}Q[100010];

int n, q, d[100010], bsize, cnt[100010];

inline bool _query_block_cmp_(const query &x, const query &y)
{
	if (x.l / bsize == y.l / bsize) return x.r < y.r;
	return x.l < y.l;
}

inline bool _query_ord_cmp_(const query &x, const query &y)
{
	return x.ord < y.ord;
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
		if (d[i] > n) d[i] = n + 1;
	}
	for (int i = 0; i < q; i++)
	{
		scanf("%d%d", &Q[i].l, &Q[i].r);
		Q[i].ord = i;
	}
	bsize = sqrt(n);
	sort(Q, Q + q, _query_block_cmp_);
	int l = 1, r = 1;
	cnt[d[1]]++;
	int ans = (d[1] == 1 ? 1 : 0);
	for (int i = 0; i < q; i++)
	{
		for (int p = l - 1; p >= Q[i].l; p--)
		{
			if (cnt[d[p]] == d[p]) ans--;
			cnt[d[p]]++;
			if (cnt[d[p]] == d[p]) ans++;
		}
		for (int p = l; p < Q[i].l; p++)
		{
			if (cnt[d[p]] == d[p]) ans--;
			cnt[d[p]]--;
			if (cnt[d[p]] == d[p]) ans++;
		}
		for (int p = r; p > Q[i].r; p--)
		{
			if (cnt[d[p]] == d[p]) ans--;
			cnt[d[p]]--;
			if (cnt[d[p]] == d[p]) ans++;
		}
		for (int p = r + 1; p <= Q[i].r; p++)
		{
			if (cnt[d[p]] == d[p]) ans--;
			cnt[d[p]]++;
			if (cnt[d[p]] == d[p]) ans++;
		}
		Q[i].ans = ans;
		l = Q[i].l, r = Q[i].r;
	}
	sort(Q, Q + q, _query_ord_cmp_);
	for (int i = 0; i < q; i++)
	{
		printf("%d\n", Q[i].ans);
	}
	return 0;
}
