// Problem Name: 最大公约数
// Source: [JSOI2015]

#include <cstdio>

typedef long long ll;

using namespace std;

int n;
ll st[100010][18];

inline void check_max(ll &x, ll y)
{
	if (y > x) x = y;
}

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void init_st()
{
	for (int k = 1; (1 << k) <= n; k++)
	{
		for (int i = 0; i + (1 << k) <= n + 1; i++)
		{
			st[i][k] = gcd(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
		}
	}
}

inline int log2(int x)
{
	int res = -1;
	while (x > 0)
	{
		res++;
		x >>= 1;
	}
	return res;
}

inline ll get_gcd(int l, int r)
{
	int k = log2(r - l + 1);
	return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

int binary_search(int l, int r, ll x)
{
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (get_gcd(l, mid) >= x) l = mid + 1;
		else r = mid;
	}
	return l;
}

ll solve()
{
	init_st();
	ll ans = 0;
	for (int i = 0; i < n; i++)
	{
		int s = i;
		while (s < n)
		{
			int p = binary_search(s, n, get_gcd(i, s));
			check_max(ans, get_gcd(i, p - 1) * (p - i));
			s = p;
		}
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &st[i][0]);
	}
	printf("%lld\n", solve());
	return 0;
}
