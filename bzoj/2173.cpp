// Problem Name: 整数的lqp拆分

#include <cstdio>

#define MOD 1000000007

using namespace std;

unsigned int A[1000010];

int main()
{
	int n;
	scanf("%d", &n);
	A[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		A[i] = (2 * A[i - 1] + A[i - 2]) % MOD;
	}
	printf("%u\n", A[n]);
	return 0;
}
