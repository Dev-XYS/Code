// Problem Name: 矩阵游戏
// Source: [NOI2013]

#include <cstdio>
#include <cstring>

#define MOD 1000000007

typedef long long ll;

using namespace std;

struct matrix
{
	int num[2][2];
	matrix() { memset(num, 0, sizeof(num)); }
	matrix(int n1, int n2, int n3, int n4) { num[0][0] = n1, num[0][1] = n2, num[1][0] = n3, num[1][1] = n4; }
	int* operator [] (int x) { return num[x]; }
};

char n[1000010], m[1000010];
int a, b, c, d;

matrix operator * (matrix x, matrix y)
{
	matrix res;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			res[i][j] = ((ll)x[i][0] * y[0][j] + (ll)x[i][1] * y[1][j]) % MOD;
		}
	}
	return res;
}

matrix qpow(matrix x, char *y)
{
	int len = strlen(y);
	matrix res(1, 0, 0, 1);
	for (int i = len - 1; i >= 0; i--)
	{
		int k = y[i] - '0';
		for (int j = 0; j < k; j++)
		{
			res = res * x;
		}
		matrix temp = x * x * x;
		temp = temp * temp * temp;
		x = temp * x;
	}
	return res;
}

void dec(char *x)
{
	int p = strlen(x) - 1;
	while (x[p] == '0') x[p--] = '9';
	x[p]--;
}

int main()
{
	scanf("%s%s%d%d%d%d", n, m, &a, &b, &c, &d);
	dec(n);
	dec(m);
	matrix row(a, b, 0, 1);
	matrix col(c, d, 0, 1);
	row = qpow(row, m);
	matrix base = col * row;
	matrix res = row * qpow(base, n);
	printf("%d\n", (res[0][0] + res[0][1]) % MOD);
	return 0;
}
