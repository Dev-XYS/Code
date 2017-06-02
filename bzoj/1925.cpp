// Problem Name: 地精部落
// Source: [SDOI2010]

#include <cstdio>
#include <cstring>

using namespace std;

int n, p, dp[4210], _dp[4210];

int main()
{
	scanf("%d%d", &n, &p);
	dp[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		memcpy(_dp, dp, sizeof(dp));
		for (int j = 1; j <= i; j++)
		{
			dp[j] = (dp[j - 1] + _dp[i - j]) % p;
		}
	}
	printf("%d\n", dp[n] * 2 % p);
	return 0;
}
