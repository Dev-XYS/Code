// Problem Name: 音量调节
// Source: [HAOI2012]

#include <cstdio>

using namespace std;

int n, beginlevel, maxlevel, c[55];
bool dp[55][1010];

int main()
{
	scanf("%d%d%d", &n, &beginlevel, &maxlevel);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
	}
	dp[0][beginlevel] = true;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= maxlevel; j++)
		{
			if (j - c[i] >= 0) dp[i][j] |= dp[i - 1][j - c[i]];
			if (j + c[i] <= maxlevel) dp[i][j] |= dp[i - 1][j + c[i]];
		}
	}
	for (int i = maxlevel; i >= 0; i--)
	{
		if (dp[n][i] == true)
		{
			printf("%d\n", i);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
