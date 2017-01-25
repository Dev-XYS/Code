#include <cstdio>
#include <cstring>

#define INF 1000000000

using namespace std;

int n, map[20][20], dp1[10000][15], dp2[10000][15];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int solve1(int status, int end)
{
	if (end == n - 2) return 0;
	if (status == 0) return map[n - 2][end];
	if (dp1[status][end] != -1) return dp1[status][end];
	dp1[status][end] = INF;
	for (int i = 0; i < n - 2; i++)
	{
		if ((status & (1 << i)) != 0)
		{
			dp1[status][end] = min(dp1[status][end], solve1(status - (1 << i), i) + map[i][end]);
		}
	}
	return dp1[status][end];
}

int solve2(int status, int end)
{
	if (end == n - 1) return 0;
	if (status == 0) return map[n - 1][end];
	if (dp2[status][end] != -1) return dp2[status][end];
	dp2[status][end] = INF;
	for (int i = 0; i < n - 2; i++)
	{
		if ((status & (1 << i)) != 0)
		{
			dp2[status][end] = min(dp2[status][end], solve2(status - (1 << i), i) + map[i][end]);
		}
	}
	return dp2[status][end];
}

int main()
{
	scanf("%d", &n);
	if (n == 1)
	{
		printf("0");
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	memset(dp1, -1, sizeof(dp1));
	memset(dp2, -1, sizeof(dp2));
	int ans = INF;
	for (int i = (1 << (n - 2)) - 1; i >= 0; i--)
	{
		ans = min(ans, solve1(i, n - 1) + solve2((1 << (n - 2)) - 1 - i, n - 2));
	}
	printf("%d", ans);
	return 0;
}
