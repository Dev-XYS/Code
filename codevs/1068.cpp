#include <cstdio>

using namespace std;

int n, m, s[400], c[5], dp[41][41][41][41];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int main()
{
	int x;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &s[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &x);
		c[x]++;
	}
	dp[0][0][0][0] = s[0];
	for (int i = 0; i <= c[1]; i++)
	{
		for (int j = 0; j <= c[2]; j++)
		{
			for (int k = 0; k <= c[3]; k++)
			{
				for (int l = 0; l <= c[4]; l++)
				{
					if (i > 0) dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l] + s[i + j * 2 + k * 3 + l * 4]);
					if (j > 0) dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j - 1][k][l] + s[i + j * 2 + k * 3 + l * 4]);
					if (k > 0) dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k - 1][l] + s[i + j * 2 + k * 3 + l * 4]);
					if (l > 0) dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l - 1] + s[i + j * 2 + k * 3 + l * 4]);
				}
			}
		}
	}
	printf("%d", dp[c[1]][c[2]][c[3]][c[4]]);
	return 0;
}
