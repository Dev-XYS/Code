// Problem Name: 征途
// Source: [SDOI2016]

#include <cstdio>

#define INF 1000000000

typedef long long ll;

using namespace std;

int n, m, s[3010], dp[3010][3010], Q[3010], hp, tp, k;

inline int sqr(int x)
{
	return x * x;
}

inline double get_y(int i)
{
	return dp[k - 1][i] + sqr(s[i]);
}

inline double get_x(int i)
{
	return s[i];
}

inline double slope(int i, int j)
{
	return (double)(get_y(i) - get_y(j)) / (double)(get_x(i) - get_x(j));
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &s[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		s[i] += s[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		dp[0][i] = INF;
	}
	for (k = 1; k <= m; k++)
	{
		dp[k][0] = INF;
		hp = 0;
		tp = 1;
		Q[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (tp - hp >= 2 && slope(Q[hp], Q[hp + 1]) < 2 * s[i]) hp++;
			dp[k][i] = dp[k - 1][Q[hp]] + sqr(s[i] - s[Q[hp]]);
			while (tp - hp >= 2 && slope(Q[tp - 1], i) <= slope(Q[tp - 2], Q[tp - 1])) tp--;
			Q[tp++] = i;
		}
	}
	printf("%lld\n", (ll)dp[m][n] * m - sqr(s[n]));
	return 0;
}
