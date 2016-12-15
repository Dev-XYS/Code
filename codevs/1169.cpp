#include <cstdio>

#define INF 1000000000

using namespace std;

int m, n, d[60][60], dp[120][60][60];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &d[i][j]);
		}
	}
	for (int k = 3; k <= m + n; k++)
	{
		for (int i = 1; i <= m; i++)
		{
			dp[k][i][i] = -INF;
		}
	}
	for (int k = 3; k <= m + n; k++)
	{
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if ((!(i == m && j == m) && i == j) || k - i <= 0 || k - j <= 0 || k - i > n || k - j > n)
				{
					continue;
				}
				if (i > 1)
				{
					if (j > 1)
					{
						dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - 1][j - 1]);
					}
					dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - 1][j]);
				}
				if (j > 1)
				{
					dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j - 1]);
				}
				dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j]);
				dp[k][i][j] += d[i][k - i] + d[j][k - j];
			}
		}
	}
	printf("%d", dp[m + n - 1][m][m - 1]);
	return 0;
}
