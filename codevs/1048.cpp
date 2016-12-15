#include <cstdio>

#define INF 1000000000

using namespace std;

int n, d[110], dp[110][110];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	for (int i = 2; i <= n; i++)
	{
		d[i] += d[i - 1];
	}
	for (int k = 2; k <= n; k++)
	{
		for (int i = 1; i <= n - k + 1; i++)
		{
			dp[i][i + k - 1] = INF;
			for (int j = i; j < i + k - 1; j++)
			{
				dp[i][i + k - 1] = min(dp[i][i + k - 1], dp[i][j] + dp[j + 1][i + k - 1] + d[i + k - 1] - d[i - 1]);
			}
		}
	}
	printf("%d", dp[1][n]);
	return 0;
}
