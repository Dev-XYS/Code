#include <cstdio>
#include <cstring>

typedef long long ll;

using namespace std;

int n;
ll a[100010], ans[100010];

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

void solve(int l, int r)
{
	if (l <= r)
	{
		int minp = l, maxp = l;
		for (int i = l; i <= r; i++)
		{
			if (a[i] < a[minp])
			{
				minp = i;
			}
			else if (a[i] > a[maxp])
			{
				maxp = i;
			}
		}
		solve(l, minp - 1);
		solve(minp + 1, r);
		for (int i = abs(maxp - minp) + 1; i <= r - l + 1; i++)
		{
			if (a[minp] * a[maxp] > ans[i])
			{
				ans[i] = a[minp] * a[maxp];
			}
		}
	}
}

int main()
{
	while (scanf("%d", &n) > 0)
	{
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &a[i]);
		}
		solve(0, n - 1);
		for (int i = 1; i <= n; i++)
		{
			printf("%lld\n", ans[i]);
		}
	}
	return 0;
}
