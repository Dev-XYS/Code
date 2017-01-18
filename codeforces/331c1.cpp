#include <cstdio>

#define INF 1000000000

using namespace std;

int n, dp[1000010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= 9; i++)
	{
		dp[i] = 1;
	}
	for (int i = 10; i <= n; i++)
	{
		int k, x = i;
		dp[i] = INF;
		while (x > 0)
		{
			k = x % 10;
			dp[i] = min(dp[i], dp[i - k] + 1);
			x /= 10;
		}
	}
	printf("%d", dp[n]);
	return 0;
}
