// Problem Name: LCMSum

#include <cstdio>

typedef long long ll;

using namespace std;

int t, n, prime[1000010], pc, div[1000010], phi[1000010];

void sieve()
{
	phi[1] = 2;
	for (int i = 2; i <= 1000000; i++)
	{
		if (div[i] == 0) prime[pc++] = i, div[i] = i, phi[i] = i - 1;
		for (int j = 0; j < pc && prime[j] * i <= 1000000; j++)
		{
			div[prime[j] * i] = prime[j];
			if (div[i] != prime[j]) phi[prime[j] * i] = phi[i] * (prime[j] - 1);
			else
			{
				phi[prime[j] * i] = phi[i] * prime[j];
				break;
			}
		}
	}
}

int main()
{
	scanf("%d", &t);
	sieve();
	/*for (int i = 1; i <= 100; i++)
	{
		printf("%d : %d %d\n", i, div[i], phi[i]);
		}*/
	while (t--)
	{
		scanf("%d", &n);
		ll ans = 0;
		int i;
		for (i = 1; i * i < n; i++)
		{
			if (n % i == 0)
			{
				ans += (ll)i * (ll)phi[i] >> 1;
				ans += (ll)(n / i) * (ll)phi[n / i] >> 1;
			}
		}
		if (i * i == n) ans += (ll)i * (ll)phi[i] >> 1;
		ans *= (ll)n;
		printf("%lld\n", ans);
	}
	return 0;
}
