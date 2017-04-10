// Problem Name: Gcd
// Source: 湖北省队互测

#include <cstdio>

typedef long long ll;

using namespace std;

int n, prime[1000010], pc, div[10000010], mu[10000010];

void linear_sieve()
{
	mu[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (div[i] == 0) prime[pc++] = i, div[i] = i, mu[i] = -1;
		for (int j = 0; j < pc && (ll)i * (ll)prime[j] <= n; j++)
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
}

ll solve()
{
	ll res = 0;
	for (int i = 0; i < pc; i++)
	{
		for (int j = n / prime[i]; j > 0; j--)
		{
			res += (ll)(n / prime[i] / j) * (ll)(n / prime[i] / j) * mu[j];
		}
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	linear_sieve();
	printf("%lld", solve());
	return 0;
}
