// Problem Name: 栈
// Source: 2003年NOIP全国联赛普及组

#include <cstdio>

typedef long long ll;

using namespace std;

ll C[40][40];

void init_C()
{
	for (int i = 0; i <= 36; i++)
	{
		C[i][0] = 1;
	}
	for (int i = 1; i <= 36; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
}

ll catalan(int n)
{
	return C[n * 2][n] - C[n * 2][n - 1];
}

int main()
{
	int n;
	scanf("%d", &n);
	init_C();
	printf("%lld\n", catalan(n));
	return 0;
}
