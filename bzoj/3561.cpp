// Problem Name: DZY Loves Math VI
// Problem Author: Jcvb

#include <cstdio>

#define MOD 1000000007LL

typedef long long ll;

using namespace std;

int n, m, to, mto, prime[100010], pc = 0, div[500010], mu[500010];
ll s[500010], sum[500010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

ll qpow(ll x, int y)
{
	if (y == 1) return x;
	ll t = qpow(x, y >> 1);
	t = t * t % MOD;
	if ((y & 1) == 0) return t;
	else return t * x % MOD;
}

void sieve()
{
	mu[1] = 1;
	for (int i = 2; i <= to; i++)
	{
		if (div[i] == 0) prime[pc++] = i, div[i] = i, mu[i] = -1;
		for (int j = 0; j < pc && (ll)i * (ll)prime[j] <= (ll)to; j++)
		{
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j])
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else mu[i * prime[j]] = mu[i] * (-1);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	to = min(n, m);
	mto = max(n, m);
	for (int i = 1; i <= mto; i++)
	{
		s[i] = 1;
	}
	sieve();
	ll ans = 0;
	for (int i = 1; i <= to; i++)
	{
		int _to = to / i, _mto = mto / i;
		for (int j = 1; j <= _mto; j++)
		{
			s[j] = s[j] * (ll)j % MOD;
			sum[j] = (sum[j - 1] + s[j]) % MOD;
		}
		ll t = 0;
		for (int j = 1; j <= _to; j++)
		{
			t = (t + sum[m / i / j] * sum[n / i / j] * mu[j] % MOD * s[j] % MOD * s[j]) % MOD;
		}
		t = t * qpow(i, i) % MOD;
		ans = (ans + t) % MOD;
	}
	printf("%lld", ans);
	return 0;
}
