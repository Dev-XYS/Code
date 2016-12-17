#include <cstdio>

using namespace std;

long long dp[60][60];

int main()
{
	int n, m, x1, y1, x2, y2;
	scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
	dp[x1][y1] = 1LL;
	for (int i = x1 + 1; i <= x2; i++)
	{
		dp[i][1] = dp[i - 2][2] + dp[i - 1][3];
		for (int j = 2; j <= m; j++)
		{
			dp[i][j] = dp[i - 1][j - 2] + dp[i - 1][j + 2] + dp[i - 2][j - 1] + dp[i - 2][j + 1];
		}
	}
	printf("%lld", dp[x2][y2]);
	return 0;
}
