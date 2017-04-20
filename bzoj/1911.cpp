// Problem Name: 特别行动队
// Source: [APIO2010]

#include <cstdio>

typedef long long ll;

using namespace std;

int n, a, b, c, x[1000010], s[1000010], Q[1000010], hp, tp;
ll dp[1000010];

inline ll sqr(int x)
{
	return (ll)x * (ll)x;
}

inline ll get_x(int i)
{
	return s[i];
}

inline ll get_y(int i)
{
	return dp[i] + (ll)a * sqr(s[i]);
}

inline double get_k(int i, int j)
{
	return (double)(get_y(i) - get_y(j)) / (double)(get_x(i) - get_x(j));
}

int main()
{
	scanf("%d%d%d%d", &n, &a, &b, &c);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + x[i];
	}
	tp++;
	for (int i = 1; i <= n; i++)
	{
		while (tp - hp >= 2 && get_k(Q[hp], Q[hp + 1]) >= 2LL * a * s[i] + b) hp++;
		dp[i] = dp[Q[hp]] + (ll)a * sqr(s[i] - s[Q[hp]]) + (ll)b * (s[i] - s[Q[hp]]) + c;
		while (tp - hp >= 2 && get_k(Q[tp - 1], i) >= get_k(Q[tp - 2], Q[tp - 1])) tp--;
		Q[tp++] = i;
	}
	printf("%lld\n", dp[n]);
	return 0;
}
