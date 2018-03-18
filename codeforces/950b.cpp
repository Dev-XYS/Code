// Problem Name: Intercepted Message
// Source: Codeforces Round #469 (Div. 2), Problem B

#include <cstdio>

using namespace std;

int n, m, x[100010], y[100010];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &y[i]);
	}
	int sumx = 0, sumy = 0, j = 0, ans = 0;
	for (int i = 0; i < n; i++)
	{
		sumx += x[i];
		while (sumy < sumx)
		{
			sumy += y[j++];
		}
		if (sumx == sumy)
		{
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
