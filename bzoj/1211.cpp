// Problem Name: 树的计数
// Source: [HNOI2004]

#include <cstdio>

typedef long long ll;

using namespace std;

int n, deg[1010], fill, mul[1010];

void mul_fac(int x)
{
	for (int i = 2; i <= x; i++)
	{
		mul[i]++;
	}
}

void div_fac(int x)
{
	for (int i = 2; i <= x; i++)
	{
		mul[i]--;
	}
}

void calc()
{
	ll ans = 1;
	for (int i = 2; i <= n; i++)
	{
		while (mul[i]--) ans *= (ll)i;
	}
	printf("%lld", ans);
}

int main()
{
	scanf("%d", &n);
	if (n == 1)
	{
		scanf("%d", &deg[1]);
		printf(deg[1] == 0 ? "1" : "0");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &deg[i]);
		if (deg[i] == 0)
		{
			printf("0");
			return 0;
		}
		fill += deg[i] - 1;
	}
	if (fill != n - 2)
	{
		printf("0");
		return 0;
	}
	mul_fac(n - 2);
	for (int i = 1; i <= n; i++)
	{
		div_fac(deg[i] - 1);
	}
	calc();
	return 0;
}
