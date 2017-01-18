#include <cstdio>
#include <algorithm>

using namespace std;

int c[1010], d[1010];
double f[1010];

int main()
{
	int n, k;
	while (true)
	{
		scanf("%d%d", &n, &k);
		if (n == 0 && k == 0) break;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &c[i]);
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &d[i]);
		}
		double l = 0.0f, r = 1.0f;
		for (int epsi = 0; epsi < 10; epsi++)
		{
			double mid = (l + r) / 2;
			for (int i = 0; i < n; i++)
			{
				f[i] = (double)c[i] - mid * (double)d[i];
			}
			sort(f, f + n);
			double lambda = 0.0f;
			for (int i = k; i < n; i++)
			{
				lambda += f[i];
			}
			if (lambda < 0)
			{
				r = mid;
			}
			else
			{
				l = mid;
			}
		}
		printf("%.0f\n", (l + r) * 50);
	}
	return 0;
}
