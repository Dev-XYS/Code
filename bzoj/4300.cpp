// Problem Name: 绝世好题
// Problem Author: Oxer

#include <cstdio>

using namespace std;

int n, dp[32];

inline int readint()
{
	int res = 0;
	char c;
	while (c = getchar(), c < '0' || c > '9') ;
	do
	{
		res = res * 10 + (c - '0');
		c = getchar();
	} while ('0' <= c && c <= '9');
	return res;
}

int main()
{
	scanf("%d", &n);
	int x;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		int temp = 0;
		for (int j = 0; j <= 30; j++)
		{
			if ((x & (1 << j)) != 0)
			{
				if (dp[j] > temp)
				{
					temp = dp[j];
				}
			}
		}
		temp++;
		for (int j = 0; j <= 30; j++)
		{
			if ((x & (1 << j)) != 0)
			{
				if (temp > dp[j])
				{
					dp[j] = temp;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= 30; i++)
	{
		if (dp[i] > ans)
		{
			ans = dp[i];
		}
	}
	printf("%d\n", ans);
	return 0;
}
