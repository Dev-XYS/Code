// Problem Name: HH去散步
// Source: [SDOI2009]

#include <cstdio>
#include <cstring>

#define MOD 45989

using namespace std;

struct raw_edge
{
	int u, v;
}R[125];

struct matrix
{
	int num[120][120];
	matrix() { memset(num, 0, sizeof(num)); }
	int* operator [] (int x) { return num[x]; }
	const int* operator [] (int x) const { return num[x]; }
};

int n, m, t, A, B;

matrix operator * (const matrix &x, const matrix &y)
{
	matrix res;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < m; k++)
			{
				res[i][j] = (res[i][j] + x[i][k] * y[k][j]) % MOD;
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
	else return h * x;
}

inline int oppo(int x)
{
	return x < m ? x + m : x - m;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &t, &A, &B);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &R[i].u, &R[i].v);
		R[i + m].u = R[i].v;
		R[i + m].v = R[i].u;
	}
	matrix base;
	for (int i = 0; i < m * 2; i++)
	{
		for (int j = 0; j < oppo(i); j++)
		{
			if (R[j].v == R[i].u) base[i][j] = 1;
		}
		for (int j = oppo(i) + 1; j < m * 2; j++)
		{
			if (R[j].v == R[i].u) base[i][j] = 1;
		}
	}
	m *= 2;
	base = qpow(base, t - 1);
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		if (R[i].v == B)
		{
			for (int j = 0; j < m; j++)
			{
				if (R[j].u == A) ans = (ans + base[i][j]) % MOD;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
