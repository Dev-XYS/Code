// Problem Name: [Hnoi2010] 合唱队 chorus

#include <cstdio>
#include <cstring>

#define MOD 19650827

using namespace std;

int n, d[1010], dp[1010][1010][2];

int solve(int l, int r, int k)
{
	if (dp[l][r][k] != -1) return dp[l][r][k];
	if (l == r) dp[l][r][k] = 1;
	else if (r - l == 1)
	{
		if (k == 0) dp[l][r][k] = (d[l] < d[r] ? 1 : 0);
		else dp[l][r][k] = (d[r] > d[l] ? 1 : 0);
	}
	else
	{
		dp[l][r][k] = 0;
		if (k == 0)
		{
			if (d[l] < d[l + 1]) dp[l][r][k] += solve(l + 1, r, 0);
			if (d[l] < d[r]) dp[l][r][k] += solve(l + 1, r, 1);
		}
		else
		{
			if (d[r] > d[r - 1]) dp[l][r][k] += solve(l, r - 1, 1);
			if (d[r] > d[l]) dp[l][r][k] += solve(l, r - 1, 0);
		}
	}
	return dp[l][r][k] %= MOD;
}

int main()
{
	scanf("%d", &n);
	if (n == 1) printf("1");
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	memset(dp, -1, sizeof(dp));
	printf("%d", (solve(1, n, 0) + solve(1, n, 1)) % MOD);
	return 0;
}
