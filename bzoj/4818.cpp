// Problem Name: 序列计数
// Source: [SDOI2017]

#include <cstdio>
#include <cstring>

#define MOD 20170408

typedef long long ll;

using namespace std;

struct matrix
{
	int num[100][100];
	matrix() { memset(num, 0, sizeof(num)); }
	int* operator [] (int x) { return num[x]; }
	const int* operator [] (int x) const { return num[x]; }
};

int n, m, p, prime[2000010], pc, div[20000010];
matrix base1, base2;

matrix operator * (const matrix &x, const matrix &y)
{
	matrix res;
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			for (int k = 0; k < p; k++)
			{
				res[i][j] = ((ll)res[i][j] + (ll)x[i][k] * (ll)y[k][j]) % MOD;
			}
		}
	}
	return res;
}

matrix qpow(const matrix &x, int y)
{
	if (y == 1) return x;
	matrix h = qpow(x * x, y >> 1);
	if ((y & 1) == 0) return h;
	return h * x;
}

void sieve()
{
	base1[0][p - 1]++;
	base2[0][p - 1]++;
	for (int i = 2; i <= m; i++)
	{
		base1[0][(p - i % p) % p]++;
		if (div[i] == 0) prime[pc++] = i, div[i] = i;
		else base2[0][(p - i % p) % p]++;
		for (int j = 0; j < pc && i * prime[j] <= m; j++)
		{
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j]) break;
		}
	}
}

void init_base()
{
	for (int i = 1; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			base1[i][j] = base1[0][(j - i + p) % p];
			base2[i][j] = base2[0][(j - i + p) % p];
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	sieve();
	init_base();
	base1 = qpow(base1, n);
	base2 = qpow(base2, n);
	printf("%d\n", (base1[0][0] - base2[0][0] + MOD) % MOD);
	return 0;
}
