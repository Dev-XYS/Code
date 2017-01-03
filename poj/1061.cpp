#include <cstdio>

using namespace std;

long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void exgcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
	}
	else
	{
		exgcd(b, a % b, x, y);
		long long temp = x;
		x = y;
		y = temp - a / b * y;
	}
}

int main()
{
	long long s, t, m, n, l, x, y;
	scanf("%lld%lld%lld%lld%lld", &s, &t, &m, &n, &l);
	long long p = (m - n + l) % l, q = (t - s + l) % l;
	long long g = gcd(p, l);
	if (q % g == 0)
	{
		exgcd(p / g, l / g, x, y);
		printf("%lld", (x * (q / g) % l + l) % l);
	}
	else
	{
		printf("Impossible");
	}
	return 0;
}
