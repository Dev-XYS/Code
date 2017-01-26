#include <cstdio>
#include <cstring>

using namespace std;

int l, r, dp[10][10][2];

int solve(int n)
{
	memset(dp, 0, sizeof(dp));
	int k = 0;
	for (int i = n % 10; i >= 0; i--)
	{
		dp[0][i][0] = 1;
	}
	for (int i = n % 10 + 1; i < 10; i++)
	{
		dp[0][i][1] = 1;
	}
	n /= 10;
	while (n > 0)
	{
		k++;
		int x = n % 10;
		n /= 10;
		for (int i = 0; i < x; i++)
		{
			for (int j = i - 2; j >= 0; j--)
			{
				dp[k][i][0] += dp[k - 1][j][0] + dp[k - 1][j][1];
			}
			for (int j = i + 2; j < 10; j++)
			{
				dp[k][i][0] += dp[k - 1][j][0] + dp[k - 1][j][1];
			}
		}
		for (int j = x - 2; j >= 0; j--)
		{
			dp[k][x][0] += dp[k - 1][j][0];
			dp[k][x][1] += dp[k - 1][j][1];
		}
		for (int j = x + 2; j < 10; j++)
		{
			dp[k][x][0] += dp[k - 1][j][0];
			dp[k][x][1] += dp[k - 1][j][1];
		}
		for (int i = x + 1; i < 10; i++)
		{
			for (int j = i - 2; j >= 0; j--)
			{
				dp[k][i][1] += dp[k - 1][j][0] + dp[k - 1][j][1];
			}
			for (int j = i + 2; j < 10; j++)
			{
				dp[k][i][1] += dp[k - 1][j][0] + dp[k - 1][j][1];
			}
		}
	}
	int res = 0;
	for (int j = 1; j <= 9; j++)
	{
		res += dp[k][j][0];
	}
	for (int i = k - 1; i >= 0; i--)
	{
		for (int j = 1; j <= 9; j++)
		{
			res += dp[i][j][0] + dp[i][j][1];
		}
	}//printf("dp result:\n");for (int i = 0; i <= k; i++) for (int j = 0; j < 10; j++) printf("dp[%d][%d][0] = %d, dp[%d][%d][1] = %d\n", i, j, dp[i][j][0], i, j, dp[i][j][1]);
	return res;
}

int main()
{
	scanf("%d%d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;
}
