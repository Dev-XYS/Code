// Problem Name: 子集选取
// Source: [JSOI2015]

#include <cstdio>

#define MOD 1000000007

typedef long long ll;

using namespace std;

ll qpow(ll x, int y)
{
	if (y == 0) return 1;
	ll h = qpow(x * x % MOD, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x % MOD;
}

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	printf("%lld\n", qpow(qpow(2, n), k));
	return 0;
}
