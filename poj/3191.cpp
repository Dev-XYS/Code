#include <cstdio>

using namespace std;

int main()
{
	long long n, k = 0, r = 2;
	char ans[50];
	scanf("%lld", &n);
	while (n != 0)
	{
		if (n % r != 0)
		{
			ans[k] = '1';
			n -= r / 2;
		}
		else
		{
			ans[k] = '0';
		}
		k++;
		r *= (-2);
	}
	if (k == 0)
	{
		printf("0");
	}
	else
	{
		for (k--; k >= 0; k--)
		{
			printf("%c", ans[k]);
		}
	}
	return 0;
}
