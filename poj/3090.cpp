#include <cstdio>

using namespace std;

int e[1010];

int euler(int x)
{
	int res = x, last = 0;
	while (true)
	{
		for (int i = 2; i * i <= x; i++)
		{
			if (x % i == 0)
			{
				if (i != last)
				{
					res = res / i * (i - 1);
					last = i;
				}
				x /= i;
				goto END;
			}
		}
		if (x != 1 && x != last)
		{
			res = res / x * (x - 1);
		}
		break;
	END:;
	}
	return res;
}

int main()
{
	int x, casen;
	scanf("%d", &casen);
	for (int i = 1; i <= 1000; i++)
	{
		e[i] = euler(i);
	}
	for (int i = 2; i <= 1000; i++)
	{
		e[i] += e[i - 1];
	}
	for (int i = 1; i <= casen; i++)
	{
		scanf("%d", &x);
		printf("%d %d %d\n", i, x, e[x] * 2 + 1);
	}
	return 0;
}
