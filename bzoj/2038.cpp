#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long ll;

using namespace std;

struct query
{
	int l, r, ord;
	ll ans;
}iq[50010];

int n, m, col[50010], cnt[50010], block;

void init()
{
	block = (int)sqrt(n);
}

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

bool _query_proc_cmp_(const query &x, const query &y)
{
	if (x.l / block == y.l / block) return x.r < y.r;
	return x.l < y.l;
}

bool _query_ord_cmp_(const query &x, const query &y)
{
	return x.ord < y.ord;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &iq[i].l, &iq[i].r);
		iq[i].ord = i;
	}
	init();
	sort(iq, iq + m, _query_proc_cmp_);
	int l = 1, r = 1;
	ll ch = 1;
	cnt[col[1]] = 1;
	for (int i = 0; i < m; i++)
	{
		if (iq[i].l < l)
		{
			for (l--; l >= iq[i].l; l--)
			{
				ch -= (ll)cnt[col[l]] * (ll)cnt[col[l]];
				cnt[col[l]]++;
				ch += (ll)cnt[col[l]] * (ll)cnt[col[l]];
			}
			l++;
		}
		if (iq[i].l > l)
		{
			for (; l < iq[i].l; l++)
			{
				ch -= (ll)cnt[col[l]] * (ll)cnt[col[l]];
				cnt[col[l]]--;
				ch += (ll)cnt[col[l]] * (ll)cnt[col[l]];
			}
		}
		if (iq[i].r > r)
		{
			for (r++; r <= iq[i].r; r++)
			{
				ch -= (ll)cnt[col[r]] * (ll)cnt[col[r]];
				cnt[col[r]]++;
				ch += (ll)cnt[col[r]] * (ll)cnt[col[r]];
			}
			r--;
		}
		if (iq[i].r < r)
		{
			for (; r > iq[i].r; r--)
			{
				ch -= (ll)cnt[col[r]] * (ll)cnt[col[r]];
				cnt[col[r]]--;
				ch += (ll)cnt[col[r]] * (ll)cnt[col[r]];
			}
		}
		iq[i].ans = ch - (iq[i].r - iq[i].l + 1);
	}
	sort(iq, iq + m, _query_ord_cmp_);
	for (int i = 0; i < m; i++)
	{
		ll a = iq[i].ans, b = (ll)(iq[i].r - iq[i].l + 1) * (ll)(iq[i].r - iq[i].l);
		ll g = gcd(a, b);
		printf("%lld/%lld\n", a / g, b / g);
	}
	return 0;
}
