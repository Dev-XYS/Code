// Problem Name: 找单词

#include <cstdio>

using namespace std;

int N, x[26], dp[26][51];

int main()
{
	scanf("%d", &N);
	while (N--)
	{
		for (int i = 0; i < 26; i++)
		{
			scanf("%d", &x[i]);
		}
		for (int j = 0; j <= x[0]; j++)
		{
			dp[0][j] = 1;
		}
		for (int j = x[0] + 1; j <= 50; j++)
		{
			dp[0][j] = 0;
		}
		for (int i = 1; i < 26; i++)
		{
			for (int j = 0; j <= 50; j++)
			{
				dp[i][j] = 0;
				for (int k = 0; k <= (i + 1) * x[i] && k <= j; k += i + 1)
				{
					dp[i][j] += dp[i - 1][j - k];
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= 50; i++)
		{
			ans += dp[25][i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
