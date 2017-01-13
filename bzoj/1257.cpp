#include <cstdio>

typedef long long ll;

using namespace std;

inline ll min(ll a, ll b)
{
	return a < b ? a : b;
}

int main()
{
	ll n, k, res = 0, i = 1;
	scanf("%lld%lld", &n, &k);
	while (i <= n)
	{
		ll d = k / i;
		ll r = d == 0 ? n : min(k / d, n);
		res += (i + r) * (r - i + 1) / 2 * d;
		i = r + 1;
	}
	printf("%lld", n * k - res);
	return 0;
}
