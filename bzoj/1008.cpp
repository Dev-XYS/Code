#include <cstdio>
#include <cstring>

#define MOD 100003

typedef long long ll;

using namespace std;

struct matrix
{
	int num[2][2];
	matrix() { memset(num, 0, sizeof(num)); }
	int* operator [] (int x) { return num[x]; }
	const int* operator [] (int x) const { return num[x]; }
};

matrix operator * (const matrix &x, const matrix &y)
{
	matrix res;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				res[i][j] = (res[i][j] + (ll)x[i][k] * (ll)y[k][j]) % MOD;
			}
		}
	}
	return res;
}

matrix qpow(const matrix &x, ll y)
{
	if (y == 1) return x;
	matrix h = qpow(x * x, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x;
}

int main()
{
	int m;
	ll n;
	scanf("%d%lld", &m, &n);
	if (n == 1)
	{
		printf("0\n");
		return 0;
	}
	matrix base;
	base[0][0] = (m - 1) % MOD;
	base[0][1] = 1;
	base[1][0] = 0;
	base[1][1] = m % MOD;
	base = qpow(base, n - 1);
	printf("%d\n", (int)((ll)m * (ll)base[0][1] % MOD));
	return 0;
}
