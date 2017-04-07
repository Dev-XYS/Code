// Problem Name: 仓库建设
// Source: [ZJOI2007]

#include <cstdio>

typedef long long ll;

using namespace std;

int n, x[1000010], Q[1000010], hp, tp;
ll p[1000010], c[1000010], sum[1000010], dp[1000010];

inline ll get_y(int a)
{
	return dp[a] - sum[a] + p[a] * (ll)x[a];
}

inline double get_k(int a, int b)
{
	return (double)(get_y(a) - get_y(b)) / (double)(p[a] - p[b]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%lld%lld", &x[i], &p[i], &c[i]);
	}
	for (int i = 2; i <= n; i++)
	{
		sum[i] = sum[i - 1] + p[i - 1];
	}
	for (int i = 2; i <= n; i++)
	{
		sum[i] *= (ll)(x[i] - x[i - 1]);
	}
	for (int i = 2; i <= n; i++)
	{
		sum[i] += sum[i - 1];
	}
	for (int i = 2; i <= n; i++)
	{
		p[i] += p[i - 1];
	}
	Q[tp++] = 0;
	dp[1] = c[1];
	Q[tp++] = 1;
	for (int i = 2; i <= n; i++)
	{
		while (tp - hp >= 2 && get_k(Q[hp], Q[hp + 1]) < (double)x[i]) hp++;
		dp[i] = dp[Q[hp]] + (sum[i] - sum[Q[hp]]) - p[Q[hp]] * (ll)(x[i] - x[Q[hp]]) + c[i];
		while (tp - hp >= 2 && get_k(Q[tp - 2], Q[tp - 1]) > get_k(Q[tp - 1], i)) tp--;
		Q[tp++] = i;
	}
	printf("%lld", dp[n]);
	return 0;
}
