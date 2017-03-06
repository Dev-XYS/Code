// Problem Name: [NOI2010] 能量采集

#include <cstdio>

using namespace std;

int n, m, prime[100010], pc, div[100010], phi[100010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void sieve(int x)
{
	phi[1] = 1;
	for (int i = 2; i <= x; i++)
	{
		if (div[i] == 0) prime[pc++] = i, div[i] = i, phi[i] = i - 1;
		for (int j = 0; j < pc && i * prime[j] <= x; j++)
		{
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j])
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	sieve(min(n, m));
	long long ans = 0;
	for (int i = min(n, m); i >= 1; i--)
	{
		ans += (long long)phi[i] * (long long)(n / i) * (long long)(m / i);
	}
	printf("%lld\n", ans * 2 - (long long)n * (long long)m);
	return 0;
}
