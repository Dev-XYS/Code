// Problem Name: 圆上的整点
// Source: [HAOI2008]

#include <cstdio>
#include <cmath>

typedef unsigned int u32;

using namespace std;

u32 gcd(u32 a, u32 b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int count(u32 x)
{
	int res = 0;
	for (u32 i = 1; i * i * 2 < x; i++)
	{
		u32 s = sqrt(x - i * i);
		if (s * s == x - i * i && gcd(i, s) == 1) res++;
	}
	return res;
}

int solve(u32 r)
{
	int ans = 0;
	u32 i;
	for (i = 1; i * i < r * 2; i++)
	{
		if (r * 2 % i == 0) ans += count(r * 2 / i) + count(i);
	}
	if (i * i == r * 2) ans += count(i);
	return (ans + 1) * 4;
}

int main()
{
	u32 r;
	scanf("%u", &r);
	printf("%d\n", solve(r));
	return 0;
}
