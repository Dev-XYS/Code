// Problem Name: Airplane Arrangements
// Source: IndiaHacks 2nd Elimination 2017 (unofficial, unrated mirror, ICPC rules), Problem D

#include <cstdio>

#define MOD 1000000007

typedef long long ll;

using namespace std;

int n, m;

ll qpow(ll x, int y)
{
	if (y == 0) return 1;
	if ((y & 1) == 0) return qpow(x * x % MOD, y >> 1);
	else return qpow(x * x % MOD, y >> 1) * x % MOD;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (n < m)
	{
		printf("0\n");
	}
	else
	{
		printf("%d\n", (int)(qpow(2, m) * qpow(n + 1, m - 1) % MOD * (n + 1 - m) % MOD));
	}
	return 0;
}
