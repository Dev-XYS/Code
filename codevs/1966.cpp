#include <cstdio>

#define INF 1000000000

using namespace std;

int n, d[101], dp[101][101];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			dp[i][j] = INF;
		}
	}
	for (int i = 1; i < n - 1; i++)
	{
		dp[i][i] = d[i - 1] * d[i] * d[i + 1];
	}
	for (int i = 2; i <= n - 2; i++)
	{
		for (int j = 1; j < n - i; j++)
		{
			for (int k = j; k < j + i; k++)
			{
				dp[j][j + i - 1] = min(dp[j][j + i - 1], dp[j][k - 1] + d[k] * d[j - 1] * d[j + i] + dp[k + 1][j + i - 1]);
			}
		}
	}
	printf("%d", dp[1][n - 2]);
	return 0;
}
