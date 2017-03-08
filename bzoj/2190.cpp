// Problem Name: [SDOI2008] 仪仗队

#include <cstdio>

using namespace std;

int phi(int x)
{
	int res = x;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0) res = res / i * (i - 1);
		while (x % i == 0) x /= i;
	}
	if (x != 1) res = res / x * (x - 1);
	return res;
}

int main()
{
	int n;
	scanf("%d", &n);
	int res = 0;
	for (int i = 2; i < n; i++)
	{
		res += phi(i);
	}
	printf("%d", res * 2 + 3);
	return 0;
}
