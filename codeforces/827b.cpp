#include <cstdio>

using namespace std;

int n, k;

int main()
{
	scanf("%d%d", &n, &k);
	if ((n - 1) % k == 0)
	{
		printf("%d\n", (n - 1) / k * 2);
	}
	else if ((n - 1) % k == 1)
	{
		printf("%d\n", (n - 1) / k * 2 + 1);
	}
	else
	{
		printf("%d\n", (n - 1) / k * 2 + 2);
	}
	for (int i = 2; i <= k + 1; i++)
	{
		printf("1 %d\n", i);
	}
	for (int i = 2; i + k <= n; i++)
	{
		printf("%d %d\n", i, i + k);
	}
	return 0;
}
