// Problem Name:Dima and Two Sequences
// Source: Codeforces Round #167 (Div. 2), Problem D

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

struct point
{
	int x, y;
}d[200010];

ll m, _fact[200010];

void init()
{
	_fact[0] = 1;
	for (int i = 1; i <= 200000; i++)
	{
		if ((i & 1) == 0) _fact[i] = _fact[i - 1] * (i >> 1) % m;
		else _fact[i] = _fact[i - 1] * i % m;
	}
}

ll qpow(ll x, int y)
{
	if (y == 0) return 1;
	int h = qpow(x * x % m, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x % m;
}

ll count(int n, int k)
{
	return _fact[n] * qpow(2, (n >> 1) - k) % m;
}

inline bool _point_cmp_(const point &x, const point &y)
{
	if (x.x == y.x) return x.y < y.y;
	return x.x < y.x;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i].x);
		d[i].y = i;
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i + n].x);
		d[i + n].y = i;
	}
	scanf("%lld", &m);
	n <<= 1;
	sort(d, d + n, _point_cmp_);
	init();
	ll ans = 1;
	int start = 0;
	for (int i = 1; i <= n; i++)
	{
		if (d[i].x != d[i - 1].x)
		{
			int k = 0;
			for (int j = start + 1; j < i; j++)
			{
				if (d[j].y == d[j - 1].y) k++;
			}
			ans = ans * count(i - start, k) % m;
			start = i;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
