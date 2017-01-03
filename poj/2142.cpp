#include <cstdio>

using namespace std;

inline long long abs(long long x)
{
	return x < 0 ? -x : x;
}

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
	long long s, a, b, x, y;
	while (true)
	{
		scanf("%lld%lld%lld", &a, &b, &s);
		if (s == 0 && a == 0 && b == 0)
		{
			break;
		}
		long long g = gcd(a, b);
		a /= g;
		b /= g;
		s /= g;
		exgcd(a, b, x, y);
		long long a1 = (x * s % b + b) % b;
		long long b1 = abs((s - a * a1) / b);
		long long b2 = (y * s % a + a) % a;
		long long a2 = abs((s - b * b2) / a);
		if (a1 + b1 < a2 + b2)
		{
			printf("%lld %lld\n", a1, b1);
		}
		else if (a1 + b1 > a2 + b2)
		{
			printf("%lld %lld\n", a2, b2);
		}
		else
		{
			if (a1 * a + b1 * b < a2 * a + b2 * b)
			{
				printf("%lld %lld\n", a1, b1);
			}
			else
			{
				printf("%lld %lld\n", a2, b2);
			}
		}
	}
	return 0;
}
