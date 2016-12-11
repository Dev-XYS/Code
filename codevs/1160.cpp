#include <cstdio>

using namespace std;

int main()
{
	int n, a[101][101];
	scanf("%d", &n);
	int x = n / 2, y = n / 2, k = 2;
	a[x][y] = 1;
	x++;
	for (int i = 1; i <= n / 2; i++)
	{
		for (int j = 1; j < (i << 1); j++)
		{
			a[x][y] = k++;
			y--;
		}
		for (int j = 0; j < (i << 1); j++)
		{
			a[x][y] = k++;
			x--;
		}
		for (int j = 0; j < (i << 1); j++)
		{
			a[x][y] = k++;
			y++;
		}
		for (int j = 0; j <= (i << 1); j++)
		{
			a[x][y] = k++;
			x++;
		}
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", a[j][i]);
		}
		printf("\n");
		sum += a[i][i] + a[n - 1 - i][i];
	}
	sum -= a[n / 2][n / 2];
	printf("%d", sum);
	return 0;
}
