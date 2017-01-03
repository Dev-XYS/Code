#include <cstdio>

typedef long long ll;

using namespace std;

ll ans = 0;

void gcd(ll a, ll b)
{
	if (b != 0)
	{
		ans += a / b;
		gcd(b, a % b);
	}
}

int main()
{
	ll r, c;
	scanf("%lld%lld", &r, &c);
	gcd(r, c);
	printf("%lld", ans);
	return 0;
}
