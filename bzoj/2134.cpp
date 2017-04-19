// Problem Name: 单选错位

#include <cstdio>

int a[10000010];

int main()
{
	int n, A, B, C;
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &a[1]);
	for (int i = 2; i <= n; i++)
	{
		a[i] = ((long long)a[i - 1] * A + B) % 100000001;
	}
	for (int i = 1; i <= n; i++)
	{
		a[i] = a[i] % C + 1;
	}
	double ans = 0;
	for (int i = 2; i <= n; i++)
	{
		ans += (a[i] > a[i - 1] ? 1 / (double)a[i] : 1 / (double)a[i - 1]);
	}
	ans += (a[1] > a[n] ? 1 / (double)a[1] : 1 / (double)a[n]);
	printf("%.3lf\n", ans);
	return 0;
}
