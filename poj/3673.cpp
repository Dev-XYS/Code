#include <cstdio>

int main()
{
	int a, b, ans = 0;
	scanf("%d%d", &a, &b);
	while (a > 0)
	{
		int x = b;
		while (x > 0)
		{
			ans += (a % 10) * (x % 10);
			x /= 10;
		}
		a /= 10;
	}
	printf("%d", ans);
	return 0;
}
