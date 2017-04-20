#include <cstdio>

#define INF 1000000000

typedef long long ll;

using namespace std;

int n, a[100010];
ll dp[100010];

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline ll max(ll x, ll y)
{
	return x > y ? x : y;
}

ll get_max()
{
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(dp[i - 1] + a[i], a[i]);
	}
	ll res = -INF;
	for (int i = 1; i < n; i++)
	{
		if (dp[i] > res) res = dp[i];
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++)
	{
		a[i] = abs(a[i] - a[i + 1]);
	}
	for (int i = 1; i < n; i += 2)
	{
		a[i] = -a[i];
	}
	ll ans = get_max();
	for (int i = 1; i < n; i++)
	{
		a[i] = -a[i];
	}
	printf("%lld\n", max(ans, get_max()));
	return 0;
}
