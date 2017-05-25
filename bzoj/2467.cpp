// Problem Name: 生成树
// Source: [中山市选2010]

#include <cstdio>

#define MOD 2007

using namespace std;

int qpow(int x, int y)
{
	if (y == 0) return 1;
	int h = qpow(x * x % MOD, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x % MOD;
}

int main()
{
	int T, n;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		printf("%d\n", n * 4 * qpow(5, n - 1) % MOD);
	}
	return 0;
}
