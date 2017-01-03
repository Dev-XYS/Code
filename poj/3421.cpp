#include <cstdio>
#include <cstring>

using namespace std;

bool isprime[1100000];
int mind[1100000], c[100], cc = 0;

void sieve(int r)
{
	memset(isprime, true, sizeof(isprime));
	memset(mind, 0, sizeof(mind));
	isprime[0] = isprime[1] = false;
	for (long long i = 2; i * i <= r; i++)
	{
		for (long long j = (i << 1); j <= r; j += i)
		{
			if (isprime[j] == true)
			{
				isprime[j] = false;
				mind[j] = i;
			}
		}
	}
}

int sum()
{
	int res = 0;
	for (int i = 1; i <= cc; i++)
	{
		res += c[i];
	}
	return res;
}

long long fac(int x)
{
	long long res = 1;
	for (int i = 2; i <= x; i++)
	{
		res *= (long long)i;
	}
	return res;
}

int main()
{
	int n;
	sieve(1099999);
	while (scanf("%d", &n) > 0)
	{
		int last = 0;
		cc = 0;
		while (mind[n] != 0)
		{
			if (mind[n] != last)
			{
				c[++cc] = 1;
				last = mind[n];
			}
			else
			{
				c[cc]++;
			}
			n /= mind[n];
		}
		if (n == last)
		{
			c[cc]++;
		}
		else
		{
			c[++cc] = 1;
		}
		long long ans = fac(sum());
		for (int i = 1; i <= cc; i++)
		{
			ans /= fac(c[i]);
		}
		printf("%d %lld\n", sum(), ans);
	}
	return 0;
}
