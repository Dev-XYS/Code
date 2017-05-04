// Problem Name: Median
// Source: POJ Founder Monthly Contest – 2008.04.13, Lei Tao

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

int n, d[100010];

ll count(int len)
{
	ll res = 0;
	for (int i = 0; i < n; i++)
	{
		int l = i, r = n - 1;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (d[mid] - d[i] <= len) l = mid;
			else r = mid - 1;
		}
		res += l - i;
	}
	return res;
}

int main()
{
	while (scanf("%d", &n) > 0)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &d[i]);
		}
		sort(d, d + n);
		ll m = (ll)n * (n - 1) / 2;
		m = (m + 1) / 2;
		int l = 0, r = 2000000000;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (count(mid - 1) < m) l = mid;
			else r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
