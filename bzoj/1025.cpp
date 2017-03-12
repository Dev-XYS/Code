// Problem Name: 游戏
// Source: [SCOI2009]

#include <cstdio>

typedef long long ll;

using namespace std;

int n, prime[200], pc;
ll dp[1010][200], s[1010];

void sieve()
{
	for (int i = 2; i <= n; i++)
	{
		for (int k = 2; k * k <= i; k++)
		{
			if (i % k == 0) goto NEXT;
		}
		prime[++pc] = i;
	NEXT:;
	}
}

void dynamic_programming()
{
	dp[0][0] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= pc; j++)
		{
			for (int p = prime[j]; p <= i; p *= prime[j])
			{
				for (int k = 0; k < j; k++)
				{
					dp[i][j] += dp[i - p][k];
				}
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	sieve();
	dynamic_programming();
	ll ans = 0;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= pc; j++)
		{
			ans += dp[i][j];
		}
	}
	printf("%lld", ans);
	return 0;
}
