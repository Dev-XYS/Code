// Problem Name: 生日聚会 Party
// Source: [ZJOI2008]

#include <cstdio>

#define MOD 12345678

using namespace std;

int n, m, k, dp[151][151][22][22];

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int j = 0; j <= k; j++)
	{
		dp[0][j][0][j] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		if (i <= k)
		{
			dp[i][0][i][0] = 1;
		}
		for (int j = 1; j <= m; j++)
		{
			for (int q = 1; q <= k; q++)
			{
				dp[i][j][0][q] = (dp[i][j - 1][1][q - 1] + dp[i][j - 1][0][q - 1]) % MOD;
			}
			for (int p = 1; p <= k; p++)
			{
				dp[i][j][p][0] = (dp[i - 1][j][p - 1][1] + dp[i - 1][j][p - 1][0]) % MOD;
				for (int q = 1; q <= k; q++)
				{
					dp[i][j][p][q] = (dp[i - 1][j][p - 1][q + 1] + dp[i][j - 1][p + 1][q - 1]) % MOD;
				}
			}
		}
	}
	int ans = 0;
	for (int p = 0; p <= k; p++)
	{
		for (int q = 0; q <= k; q++)
		{
			ans = (ans + dp[n][m][p][q]) % MOD;
		}
	}
	printf("%d\n", ans);
	return 0;
}
