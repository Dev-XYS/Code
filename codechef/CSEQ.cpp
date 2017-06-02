// Problem Name: 序列统计

#include <cstdio>

#define MOD 1000003

typedef long long ll;

using namespace std;

int fact[1000010], fact_inv[1000010];

int qpow(int x, int y)
{
	if (y == 0) return 1;
	int h = qpow((ll)x * x % MOD, y >> 1);
	if ((y & 1) == 0) return h;
	else return (ll)h * x % MOD;
}

void init()
{
	fact[0] = 1;
	for (int i = 1; i < MOD; i++)
	{
		fact[i] = (ll)fact[i - 1] * i % MOD;
	}
	fact_inv[MOD - 1] = qpow(fact[MOD - 1], MOD - 2);
	for (int i = MOD - 2; i >= 0; i--)
	{
		fact_inv[i] = (ll)fact_inv[i + 1] * (i + 1) % MOD;
	}
}

int C(int n, int m)
{
	if (n < m) return 0;
	if (n < MOD && m < MOD) return (ll)fact[n] * fact_inv[n - m] % MOD * fact_inv[m] % MOD;
	return (ll)C(n / MOD, m / MOD) * C(n % MOD, m % MOD) % MOD;
}

int main()
{
	int T, n, l, r;
	scanf("%d", &T);
	init();
	while (T--)
	{
		scanf("%d%d%d", &n, &l, &r);
		printf("%d\n", (C(n + r - l + 1, r - l + 1) - 1 + MOD) % MOD);
	}
	return 0;
}
