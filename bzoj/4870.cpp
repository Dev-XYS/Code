// Problem Name: 组合数问题
// Source: [LNOI2017]

#include <cstdio>
#include <cstring>

typedef long long ll;

using namespace std;

struct matrix
{
	int num[50][50];
	matrix() { memset(num, 0, sizeof(num)); }
	int* operator [] (int x) { return num[x]; }
};

int N, P, K, R;

matrix operator * (matrix x, matrix y)
{
	matrix res;
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			for (int k = 0; k < K; k++)
			{
				res[i][j] = (res[i][j] + (ll)x[i][k] * (ll)y[k][j]) % P;
			}
		}
	}
	return res;
}

matrix qpow(matrix x, ll y)
{
	if (y == 1) return x;
	matrix h = qpow(x * x, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x;
}

int main()
{
	scanf("%d%d%d%d", &N, &P, &K, &R);
	matrix base;
	base[0][0]++, base[0][K - 1]++;
	for (int i = 1; i < K; i++)
	{
		base[i][i]++, base[i][i - 1]++;
	}
	base = qpow(base, (ll)N * (ll)K);
	printf("%d\n", base[R][0]);
	return 0;
}
