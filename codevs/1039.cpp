#include <cstdio>

using namespace std;

int n, p, dp[210][10][210];

int main()
{
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++)
	{
		dp[i][1][i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 2; j <= p; j++)
		{
			for (int k = 1; k <= i; k++)
			{
				for (int l = 1; l <= k; l++)
				{
					dp[i][j][k] += dp[i - k][j - 1][l];
				}
			}
		}
	}
	int ans = 0;
	for (int k = 1; k <= n; k++)
	{
		ans += dp[n][p][k];
	}
	printf("%d", ans);
	return 0;
}
