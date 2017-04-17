// Problem Name: Array Queries
// Source: Educational Codeforces Round 19, Problem E

#include <cstdio>

using namespace std;

int n, a[100010], q, dp[100010][310];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init_dp()
{
	for (int i = n; i >= 1; i--)
	{
		for (int j = min(n, 300); j >= 1; j--)
		{
			if (i + a[i] + j > n) dp[i][j] = 1;
			else dp[i][j] = dp[i + a[i] + j][j] + 1;
		}
	}
}

int brute(int p, int k)
{
	int res = 0;
	while (p <= n)
	{
		res++;
		p += a[p] + k;
	}
	return res;
}

int main()
{
	int p, k;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	init_dp();
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &p, &k);
		if (k <= 300) printf("%d\n", dp[p][k]);
		else printf("%d\n", brute(p, k));
	}
	return 0;
}
