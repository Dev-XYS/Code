// Problem Name: 中国象棋 chess
// Source: [AHOI2009]

#include <cstdio>

#define MOD 9999973

typedef long long ll;

using namespace std;

int n, m;
ll dp[101][101][101];

int main()
{
	scanf("%d%d", &n, &m);
	dp[1][m][0] = 1;
	dp[1][m - 1][1] = m;
	dp[1][m - 2][2] = m * (m - 1) / 2;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			for (int k = 0; k <= m - j; k++)
			{
				// put 0
				dp[i][j][k] = dp[i - 1][j][k];
				// put 1
				if (k - 1 >= 0) dp[i][j][k] += dp[i - 1][j + 1][k - 1] * (j + 1);
				if (k + 1 <= m) dp[i][j][k] += dp[i - 1][j][k + 1] * (k + 1);
				// put 2
				if (k - 2 >= 0) dp[i][j][k] += dp[i - 1][j + 2][k - 2] * ((j + 2) * (j + 1) / 2);
				if (k + 2 <= m) dp[i][j][k] += dp[i - 1][j][k + 2] * ((k + 2) * (k + 1) / 2);
				if (j + 1 <= m) dp[i][j][k] += dp[i - 1][j + 1][k] * ((j + 1) * k);
				
				dp[i][j][k] %= MOD;
				//printf("dp[%d][%d][%d] = %d\n", i, j, k, dp[i][j][k]);
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= m - i; j++)
		{
			ans += dp[n][i][j];
		}
		ans %= MOD;
	}
	printf("%d\n", (int)ans);
	return 0;
}
