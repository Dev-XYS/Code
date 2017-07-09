#include <cstdio>

#define MOD 1000000007

using namespace std;

typedef long long ll;

int t, l, r;
ll dp[5000010];

inline void check_min(ll &x, ll y)
{
	if (y < x) x = y;
}

int main()
{
	scanf("%d%d%d", &t, &l, &r);
	for (int i = 2; i <= r; i++)
	{
		dp[i] = (ll)i * (i - 1) / 2;
	}
	for (int i = 2; i < r; i++)
	{
		for (int j = (i << 1); j <= r; j += i)
		{
			check_min(dp[j], dp[i] + (ll)j * (j / i - 1) / 2);
		}
	}
	int ans = 0;
	int m = 1;
	for (int i = l; i <= r; i++)
	{
		dp[i] %= MOD;
		ans = (ans + (ll)m * dp[i]) % MOD;
		m = (ll)m * t % MOD;
	}
	printf("%d\n", ans);
	return 0;
}
