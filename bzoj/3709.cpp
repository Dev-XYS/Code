// Problem Name: Bohater
// Source: [PA2014]

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

struct info
{
	int d, a, ord;
}d[100010];

int n;
ll z;

inline bool _info_cmp_(const info &x, const info &y)
{
	if (x.a - x.d > 0 && y.a - y.d > 0) return x.d < y.d;
	if (x.a - x.d > 0 && y.a - y.d <= 0) return true;
	if (x.a - x.d <= 0 && y.a - y.d > 0) return false;
	return x.a > y.a;
}

int main()
{
	scanf("%d%lld", &n, &z);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &d[i].d, &d[i].a);
		d[i].ord = i + 1;
	}
	sort(d, d + n, _info_cmp_);
	int i;
	for (i = 0; i < n && d[i].a - d[i].d > 0; i++)
	{
		if (d[i].d >= z)
		{
			printf("NIE\n");
			return 0;
		}
		z = z - d[i].d + d[i].a;
	}
	for (; i < n; i++)
	{
		z = z - d[i].d + d[i].a;
	}
	for (i = n - 1; i >= 0 && d[i].d - d[i].a >= 0; i--)
	{
		if (d[i].a >= z)
		{
			printf("NIE\n");
			return 0;
		}
		z = z - d[i].a + d[i].d;
	}
	printf("TAK\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", d[i].ord);
	}
	return 0;
}
