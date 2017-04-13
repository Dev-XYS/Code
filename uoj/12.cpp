// Problem Name: 猜数
// Source: [UER#1] UOJ Easy Round #1, Problem A

#include <cstdio>
#include <cmath>

typedef long long ll;

using namespace std;

inline ll max(ll x, ll y)
{
	return x > y ? x : y;
}

int main()
{
	int T;
	ll g, l;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld", &g, &l);
		printf("%lld %lld\n", ((ll)sqrt(l / g) * g) << 1, (l / g + 1) * g);
	}
	return 0;
}
