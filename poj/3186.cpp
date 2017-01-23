#include <cstdio>

using namespace std;

int n, d[2017], dp[2017][2017];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = n * d[i];
	}
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			dp[i][i + l - 1] = max(dp[i][i + l - 2] + (n - l + 1) * d[i + l - 1], dp[i + 1][i + l - 1] + (n - l + 1) * d[i]);
		}
	}
	printf("%d", dp[1][n]);
	return 0;
}
