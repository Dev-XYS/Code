// Problem Name: [Unknown]
// Source: [HAOI2011]

#include <cstdio>

using namespace std;

int prime[10000], pc, div[50010], mu[50010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void sieve()
{
	mu[1] = 1;
	for (int i = 2; i <= 50000; i++)
	{
		if (div[i] == 0) prime[pc++] = i, div[i] = i, mu[i] = -1;
		for (int j = 0; j < pc && i * prime[j] <= 50000; j++)
		{
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j])
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else mu[i * prime[j]] = mu[i] * (-1);
		}
	}
	for (int i = 1; i <= 50000; i++)
	{
		mu[i] += mu[i - 1];
	}
}

int count(int n, int m)
{
	int res = 0, t = min(n, m);
	for (int i = 1; i <= t; )
	{
		int j = min(n / (n / i), m / (m / i));
		res += (n / i) * (m / i) * (mu[j] - mu[i - 1]);
		i = j + 1;
	}
	return res;
}

int main()
{
	int n, a, b, c, d, k;
	sieve();
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%d\n", count(b / k, d / k) - count((a - 1) / k, d / k) - count(b / k, (c - 1) / k) + count((a - 1) / k, (c - 1) / k));
	}
	return 0;
}
