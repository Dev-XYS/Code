// Problem Name: 抵制克苏恩
// Source: Lydsy2017年4月月赛
// Problem Author: Tangjz
// Algorithm: DP

#include <cstdio>
 
using namespace std;
 
int T, K, A, B, C;
double dp[51][8][8][8];
 
void init()
{
	for (int k = 1; k <= 50; k++)
	{
		for (int a = 0; a <= 7; a++)
		{
			for (int b = 0; b <= 7; b++)
			{
				for (int c = 0; c <= 7; c++)
				{
					dp[k][a][b][c] += (dp[k - 1][a][b][c] + 1) * (1.0f / (double)(a + b + c + 1));
					if (a > 0) dp[k][a][b][c] += dp[k - 1][a - 1][b][c] * ((double)a / (double)(a + b + c + 1));
					if (b > 0) dp[k][a][b][c] += (a + b + c == 7 ? dp[k - 1][a + 1][b - 1][c] : dp[k - 1][a + 1][b - 1][c + 1])  * ((double)b / (double)(a + b + c + 1));
					if (c > 0) dp[k][a][b][c] += (a + b + c == 7 ? dp[k - 1][a][b + 1][c - 1] : dp[k - 1][a][b + 1][c]) * ((double)c / (double)(a + b + c + 1));
				}
			}
		}
	}
}
 
int main()
{
	scanf("%d", &T);
	init();
	while (T--)
	{
		scanf("%d%d%d%d", &K, &A, &B, &C);
		printf("%.2lf\n", dp[K][A][B][C]);
	}
	return 0;
}
