#include <cstdio>
#include <cstring>

#define PRIME_COUNT 4

typedef long long ll;

using namespace std;

int n, m;

const ll prime[PRIME_COUNT] = { 10111, 10133, 10141 , 10433 };
ll pow10[PRIME_COUNT][10010];

char a[101][10010];
ll _a[PRIME_COUNT][101], prime_res[PRIME_COUNT][10500], a_res[PRIME_COUNT][10500][101];
int ans[1000010];

void init_pow10()
{
	for (int i = 0; i < PRIME_COUNT; i++)
	{
		pow10[i][0] = 1LL;
		for (int j = 1; j <= 10000; j++)
		{
			pow10[i][j] = (pow10[i][j - 1] * 10) % prime[i];
		}
	}
}

void init_prime_res()
{
	for (int i = 0; i < PRIME_COUNT; i++)
	{
		for (int j = 0; j < prime[i]; j++)
		{
			a_res[i][j][0] = 1;
			for (int k = 1; k <= n; k++)
			{
				a_res[i][j][k] = a_res[i][j][k - 1] * j % prime[i];
			}
		}
	}
	for (int i = 0; i < PRIME_COUNT; i++)
	{
		for (int j = 0; j < prime[i]; j++)
		{
			for (int k = 0; k <= n; k++)
			{
				prime_res[i][j] = (prime_res[i][j] + _a[i][k] * a_res[i][j][k]) % prime[i];
			}
		}
	}
}

ll mod(char *d, int pc)
{
	ll res = 0;
	int len = strlen(d) - 1;
	for (int i = d[0] == '-' ? 1 : 0; i <= len; i++)
	{
		res = (res + pow10[pc][len - i] * (d[i] - '0')) % prime[pc];
	}
	return d[0] != '-' ? res : (prime[pc] - res) % prime[pc];
}

void init_mod()
{
	init_pow10();
	for (int i = 0; i < PRIME_COUNT; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			_a[i][j] = mod(a[j], i);
		}
	}
}

int main()
{
	scanf("%d%d ", &n, &m);
	for (int i = 0; i <= n; i++)
	{
		gets(a[i]);
	}
	init_mod();
	init_prime_res();
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j < PRIME_COUNT; j++)
		{
			if (prime_res[j][i % prime[j]] != 0)
			{
				goto END;
			}
		}
		ans[cnt++] = i;
	END:;
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
