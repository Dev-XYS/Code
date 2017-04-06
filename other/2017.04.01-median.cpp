#include <cstdio>

#define MOD 998244353

typedef long long ll;

using namespace std;

ll fact[1000010], inv[1000010], fact_inv[1000010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void sieve(int n)
{
	fact[0] = 1;
	fact[1] = 1;
	inv[1] = 1;
	fact_inv[0] = 1;
	fact_inv[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		fact[i] = fact[i - 1] * i % MOD;
		inv[i] = (-(ll)(MOD / i) * inv[MOD % i] % MOD + MOD) % MOD;
		fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
	}
}

ll C(int n, int m)
{
	if (n < 0 || m < 0 || n < m) return 0;
	return fact[n] * fact_inv[m] % MOD * fact_inv[n - m] % MOD;
}

ll solve(int n, int k)
{//printf("solve\n");
	ll ans = 0;
	//printf("case 1:\n");
	// Case 1:
	//printf("ans += %lld * 2 - %lld = %lld\n", C(n - 2, k - 2), C(n - 3, k - 3), C(n - 2, k - 2) * 2 - C(n - 3, k - 3));
	ans = (ans + C(n - 2, k - 2) * 2 - C(n - 3, k - 3)) % MOD;
	//printf("case 2:\n");
	// Case 2:
	for (int i = 1; i <= n - 4 && k - (i >> 1) - 4 >= 0 && n - i - 4 >= k - (i >> 1) - 4; i += 2)
	{//printf("ans += %d * %lld = %lld\n", min(i, n - i + 1 - 4), C(n - i - 4, k - (i >> 1) - 4), (ll)min(i, n - i + 1 - 4) * C(n - i - 4, k - (i >> 1) - 4));
		ans = (ans + (ll)min(i, n - i + 1 - 4) * C(n - i - 4, k - (i >> 1) - 4)) % MOD;
	}
	//printf("case 3:\n");
	// Case 3:
	for (int i = 2; i <= n - 4 && k - (i >> 1) - 2 >= 0 && n - i - 4 >= k - (i >> 1) - 2; i += 2)
	{//printf("ans += %d * %lld * 2 = %lld\n", min(i >> 1, (n >> 1) - (i >> 1) + 1), C(n - i - 4, k - (i >> 1) - 2), (ll)min(i >> 1, (n >> 1) - (i >> 1) + 1) * C(n - i - 4, k - (i >> 1) - 2) * 2);
		ans = (ans + (ll)min(i >> 1, (n >> 1) - ((i >> 1) + 2) + 1) * C(n - i - 4, k - (i >> 1) - 2) * 2) % MOD;
	}
	//printf("case 4:\n");
	// Case 4:
	for (int i = (n + 1) >> 1; i <= n - 2 && k - (i >> 1) - 2 >= 0 && n - i - 2 >= k - (i >> 1) - 2; i++)
	{//printf("ans += %lld * 2 = %lld\n", C(n - i - 2, k - (i >> 1) - 2), C(n - i - 2, k - (i >> 1) - 2) * 2);
		ans = (ans + C(n - i - 2, k - (i >> 1) - 2) * 2) % MOD;
	}
	//printf("case 5:\n");
	// Case 5:
	if (k == (n + 1) >> 1) ans = (ans + 1) % MOD;
	//printf("sub-result = %lld\n", ans);
	return ans * fact[k] % MOD * fact[n - k] % MOD;
}

int main()
{
	freopen("median.in", "r", stdin);
	freopen("median.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	sieve(n);
	if (k == 0) printf("%lld", solve(n, 0));
	else printf("%lld", (solve(n, k) - solve(n, k - 1) + MOD) % MOD);
	return 0;
}
