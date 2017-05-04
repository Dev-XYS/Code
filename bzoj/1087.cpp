// Problem Name: 互不侵犯 King
// Source: [SCOI2005]
// Algorithm: 状压DP

#include <cstdio>
 
typedef long long ll;
 
using namespace std;
 
int n, k, list[512], cnt1[512], lc;
ll dp[9][26][512];
 
int main()
{
	scanf("%d%d", &n, &k);
	if (k > 25)
	{
		printf("0\n");
		return 0;
	}
	for (int i = (1 << n) - 1; i >= 0; i--)
	{
		int cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if ((i & (1 << j)) != 0) cnt++;
		}
		for (int j = 1; j < n; j++)
		{
			if ((i & (1 << (j - 1))) != 0 && (i & (1 << j)) != 0) goto NEXT1;
		}
		list[lc] = i;
		cnt1[lc] = cnt;
		dp[0][cnt][lc] = 1;
		lc++;
	NEXT1:;
	}
	for (int r = 1; r < n; r++)
	{
		for (int c = 0; c <= 25; c++)
		{
			for (int i = 0; i < lc; i++)
			{
				if (c - cnt1[i] < 0) continue;
				for (int _i = 0; _i < lc; _i++)
				{
					if ((list[i] & (1 << 0)) != 0 && ((list[_i] & (1 << 0)) != 0 || (list[_i] & (1 << 1)) != 0)) goto NEXT2;
					for (int j = 1; j < n - 1; j++)
					{
						if ((list[i] & (1 << j)) != 0 && ((list[_i] & (1 << (j - 1))) != 0 || (list[_i] & (1 << j)) != 0 || (list[_i] & (1 << (j + 1))) != 0)) goto NEXT2;
					}
					if ((list[i] & (1 << (n - 1))) != 0 && ((list[_i] & (1 << (n - 1))) != 0 || (list[_i] & (1 << (n - 2))) != 0)) goto NEXT2;
					dp[r][c][i] += dp[r - 1][c - cnt1[i]][_i];
				NEXT2:;
				}
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < lc; i++)
	{
		ans += dp[n - 1][k][i];
	}
	printf("%lld\n", ans);
	return 0;
}
