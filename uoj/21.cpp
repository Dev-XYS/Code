// Problem Name: 缩进优化
// Source: UOJ Round #1, Problem A

#include <cstdio>

typedef long long ll;

using namespace std;

int n, a[1000010], c[2000010];

int main()
{
	scanf("%d", &n);
	int maxa = 0;
	ll sum = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		c[a[i]]++;
		if (a[i] > maxa) maxa = a[i];
		sum += a[i];
	}
	for (int i = 1; i <= maxa; i++)
	{
		c[i] += c[i - 1];
	}
	for (int i = maxa + 1; i <= 2000000; i++)
	{
		c[i] = c[maxa];
	}
	ll max = 0;
	for (int x = 2; x <= maxa; x++)
	{
		ll t = 0;
		for (int i = maxa / x; i > 0; i--)
		{
			t += (ll)(c[(i + 1) * x - 1] - c[i * x - 1]) * (ll)i;
		}
		t *= (ll)(x - 1);
		if (t > max) max = t;
	}
	printf("%lld", sum - max);
	return 0;
}
