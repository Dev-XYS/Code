// Problem Name: [SDOI2012] Longge的问题

#include <cstdio>

typedef long long ll;

using namespace std;

int phi(int x)
{
	int res = x;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0) res = res / i * (i - 1);
		while (x % i == 0) x /= i;
	}
	if (x != 1) res = res / x * (x - 1);
	return res;
}

int main()
{
	int n;
	scanf("%d", &n);
	ll ans = 0;
	int i;
	for (i = 1; i * i < n; i++)
	{
		if (n % i == 0)
		{
			ans += (ll)i * (ll)phi(n / i);
			ans += (ll)(n / i) * (ll)phi(i);
		}
	}
	if (i * i == n) ans += (ll)i * (ll)phi(n / i);
	printf("%lld", ans);
	return 0;
}
