// Problem Name: Claris的剑

#include <cstdio>

#define MOD 1000000007

typedef long long ll;

using namespace std;

int fact[2000010], fact_inv[2000010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int qpow(int x, int y)
{
	if (y == 0) return 1;
	int h = qpow((ll)x * x % MOD, y >> 1);
	if ((y & 1) == 0) return h;
	else return (ll)h * x % MOD;
}

void init(int to)
{
	fact[0] = fact[1] = fact_inv[0] = 1;
	for (int i = 2; i <= to; i++)
	{
		fact[i] = (ll)fact[i - 1] * i % MOD;
	}
	fact_inv[to] = qpow(fact[to], MOD - 2);
	for (int i = to - 1; i >= 1; i--)
	{
		fact_inv[i] = (ll)fact_inv[i + 1] * (i + 1) % MOD;
	}
}

inline int C(int n, int m)
{
	return (ll)fact[n] * fact_inv[n - m] % MOD * fact_inv[m] % MOD;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	init((n + min(n, m)) / 2);
	ll ans = 1;
	for (int i = min(n, m); i >= 2; i--)
	{
		if (((n - i) & 1) == 0)
		{
			ans += C((n - i) / 2 + i - 1, i - 1) + C((n - i) / 2 + i - 2, i - 1);
		}
		else
		{
			ans += C((n - i) / 2 + i - 1, i - 1) * 2;
		}
	}
	printf("%d\n", (int)(ans % MOD));
	return 0;
}
