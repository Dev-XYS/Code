// Problem Name: 硬币购物
// Source: [HAOI2008]

#include <cstdio>

typedef long long ll;

using namespace std;

int c[4], T, d[4], tot;
ll dp[100010];

void init()
{
	dp[0] = 1;
	for (int k = 0; k < 4; k++)
	{
		for (int i = c[k]; i <= 100000; i++)
		{
			dp[i] += dp[i - c[k]];
		}
	}
}

int main()
{
	scanf("%d%d%d%d%d", &c[0], &c[1], &c[2], &c[3], &T);
	init();
	while (T--)
	{
		scanf("%d%d%d%d%d", &d[0], &d[1], &d[2], &d[3], &tot);
		ll res = dp[tot];
		if ((ll)c[0] * (d[0] + 1) <= tot) res -= dp[tot - c[0] * (d[0] + 1)];
		if ((ll)c[1] * (d[1] + 1) <= tot) res -= dp[tot - c[1] * (d[1] + 1)];
		if ((ll)c[2] * (d[2] + 1) <= tot) res -= dp[tot - c[2] * (d[2] + 1)];
		if ((ll)c[3] * (d[3] + 1) <= tot) res -= dp[tot - c[3] * (d[3] + 1)];
		
		if ((ll)c[0] * (d[0] + 1) + (ll)c[1] * (d[1] + 1) <= tot) res += dp[tot - c[0] * (d[0] + 1) - c[1] * (d[1] + 1)];
		if ((ll)c[0] * (d[0] + 1) + (ll)c[2] * (d[2] + 1) <= tot) res += dp[tot - c[0] * (d[0] + 1) - c[2] * (d[2] + 1)];
		if ((ll)c[0] * (d[0] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res += dp[tot - c[0] * (d[0] + 1) - c[3] * (d[3] + 1)];
		if ((ll)c[1] * (d[1] + 1) + (ll)c[2] * (d[2] + 1) <= tot) res += dp[tot - c[1] * (d[1] + 1) - c[2] * (d[2] + 1)];
		if ((ll)c[1] * (d[1] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res += dp[tot - c[1] * (d[1] + 1) - c[3] * (d[3] + 1)];
		if ((ll)c[2] * (d[2] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res += dp[tot - c[2] * (d[2] + 1) - c[3] * (d[3] + 1)];
		
		if ((ll)c[0] * (d[0] + 1) + (ll)c[1] * (d[1] + 1) + (ll)c[2] * (d[2] + 1) <= tot) res -= dp[tot - c[0] * (d[0] + 1) - c[1] * (d[1] + 1) - c[2] * (d[2] + 1)];
		if ((ll)c[0] * (d[0] + 1) + (ll)c[1] * (d[1] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res -= dp[tot - c[0] * (d[0] + 1) - c[1] * (d[1] + 1) - c[3] * (d[3] + 1)];
		if ((ll)c[0] * (d[0] + 1) + (ll)c[2] * (d[2] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res -= dp[tot - c[0] * (d[0] + 1) - c[2] * (d[2] + 1) - c[3] * (d[3] + 1)];
		if ((ll)c[1] * (d[1] + 1) + (ll)c[2] * (d[2] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res -= dp[tot - c[1] * (d[1] + 1) - c[2] * (d[2] + 1) - c[3] * (d[3] + 1)];

		if ((ll)c[0] * (d[0] + 1) + (ll)c[1] * (d[1] + 1) + (ll)c[2] * (d[2] + 1) + (ll)c[3] * (d[3] + 1) <= tot) res += dp[tot - c[0] * (d[0] + 1) - c[1] * (d[1] + 1) - c[2] * (d[2] + 1) - c[3] * (d[3] + 1)];

		printf("%lld\n", res);
	}
	return 0;
}
