#include <cstdio>

using namespace std;

long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	else
	{
		long long gcd = exgcd(b, a % b, x, y);
		long long temp = x;
		x = y;
		y = temp - a / b * y;
		return gcd;
	}
}

int main()
{
	long long a, b, c, k, x, y;
	while (true)
	{
		scanf("%lld%lld%lld%lld", &a, &b, &c, &k);
		if (a == 0 && b == 0 && c == 0 && k == 0)
		{
			break;
		}
		k = 1LL << k;
		long long g = gcd(c, k);
		long long p = ((b - a) % k + k) % k;
		if (p % g != 0)
		{
			printf("FOREVER\n");
		}
		else
		{
			exgcd(c, k, x, y);
			k /= g;
			printf("%lld\n", (x * (p / g) % k + k) % k);
		}
	}
	return 0;
}
