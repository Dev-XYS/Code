// Problem Name: 采花
// Source: [HEOI2012]

#include <cstdio>
#include <algorithm>

#define LOWBIT(x) ((x) & (-(x)))

using namespace std;

struct query
{
	int l, r, ord, ans;
}qs[1000010];

int n, c, m, col[1000010], next[1000010], pos[1000010], time[1000010], f[1000010];

void add(int p)
{
	while (p <= n)
	{
		f[p]++;
		p += LOWBIT(p);
	}
}

void sub(int p)
{
	while (p <= n)
	{
		f[p]--;
		p += LOWBIT(p);
	}
}

int sum(int p)
{
	int res = 0;
	while (p > 0)
	{
		res += f[p];
		p -= LOWBIT(p);
	}
	return res;
}

inline bool _query_l_cmp_(const query &x, const query &y)
{
	return x.l < y.l;
}

inline bool _query_ord_cmp_(const query &x, const query &y)
{
	return x.ord < y.ord;
}

int main()
{
	scanf("%d%d%d", &n, &c, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &qs[i].l, &qs[i].r);
		qs[i].ord = i;
	}
	for (int i = n; i >= 1; i--)
	{
		next[i] = pos[col[i]];
		pos[col[i]] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if (time[col[i]] == 0) time[col[i]] = -1;
		else if (time[col[i]] == -1)
		{
			time[col[i]] = i;
		}
	}
	for (int i = 1; i <= c; i++)
	{
		if (time[i] > 0) add(time[i]);
		if (time[i] == -1) time[i] = 0;
	}
	sort(qs, qs + m, _query_l_cmp_);
	int p = 0;
	for (int i = 1; i <= n; i++)
	{
		while (qs[p].l == i)
		{
			qs[p].ans = sum(qs[p].r) - sum(qs[p].l - 1);
			p++;
		}
		if (next[i] > 0) sub(next[i]);
		if (next[next[i]] > 0) add(next[next[i]]);
	}
	sort(qs, qs + m, _query_ord_cmp_);
	for (int i = 0; i < m; i++)
	{
		printf("%d\n", qs[i].ans);
	}
	return 0;
}
