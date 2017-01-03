#include <cstdio>
#include <cmath>
#include <cstring>

#define INF 1000000000LL

using namespace std;

bool isprime0[100000], isprime[1000010];

inline long long max(long long x, long long y)
{
	return x > y ? x : y;
}

void sieve_0(long long r)
{
	memset(isprime0, true, sizeof(isprime0));
	isprime[0] = isprime[1] = false;
	for (long long i = 2; i * i <= r; i++)
	{
		for (long long j = (i << 1); j <= r; j += i)
		{
			isprime0[j] = false;
		}
	}
}

void sieve(long long l, long long r)
{
	long long x = (long long)sqrt(r) + 1;
	sieve_0(x);
	memset(isprime, true, sizeof(isprime));
	for (long long i = 2; i <= x; i++)
	{
		if (isprime0[i] == true)
		{
			for (long long j = max(i << 1, ((l - 1) / i + 1) * i); j <= r; j += i)
			{
				isprime[j - l] = false;
			}
		}
	}
	if (1 - l >= 0)
	{
		isprime[1 - l] = false;
	}
}

int main()
{
	long long l, r;
	while (scanf("%lld%lld", &l, &r) > 0)
	{
		long long left = 0, s1 = 0, s2 = INF, l1 = 0, l2 = 0;
		sieve(l, r);
		for (long long i = l; i <= r; i++)
		{
			if (isprime[i - l] == true)
			{
				if (left == 0)
				{
					left = i;
				}
				else
				{
					if (i - left < s2 - s1)
					{
						s1 = left;
						s2 = i;
					}
					if (i - left > l2 - l1)
					{
						l1 = left;
						l2 = i;
					}
					left = i;
				}
			}
		}
		if (s1 == 0)
		{
			printf("There are no adjacent primes.\n");
		}
		else
		{
			printf("%lld,%lld are closest, %lld,%lld are most distant.\n", s1, s2, l1, l2);
		}
	}
	return 0;
}
