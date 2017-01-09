#include <cstdio>
#include <algorithm>

using namespace std;

int n, c, x[100010];

int main()
{
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	sort(x, x + n);
	int l = 0, r = 1000000000;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1, last = x[0], j = 1;
		for (int i = 1; i < c; i++)
		{
			while (x[j] - last < mid)
			{
				j++;
				if (j == n)
				{
					r = mid - 1;
					goto END;
				}
			}
			last = x[j];
		}
		l = mid;
	END:;
	}
	printf("%d", l);
	return 0;
}
