// Problem Name: Chef and Same Old Recurrence

#include <cstdio>

#define MOD 1000000007

typedef long long ll;

using namespace std;

int N, K, A, B, R[10000010];

int main()
{
	scanf("%d%d%d%d", &N, &K, &A, &B);
	if (N == 1)
	{
		printf("%d\n", K);
		return 0;
	}
	int f_i_2 = K, f_i_1 = ((ll)A * K + (ll)B * K % MOD * K % MOD) % MOD;
	R[1] = 1;
	R[2] = 500000004;
	for (int i = 3; i <= N; i++)
	{
		int f_i = ((A + (ll)2 * B * K) % MOD * (2 * i - 3) % MOD * f_i_1 % MOD - (ll)A * A % MOD * (i - 3) % MOD * f_i_2 % MOD) % MOD;
		R[i] = -(ll)(MOD / i) * R[MOD % i] % MOD;
		f_i = (ll)f_i * R[i] % MOD;
		f_i_2 = f_i_1;
		f_i_1 = f_i;
	}
	printf("%d\n", (f_i_1 + MOD) % MOD);
	return 0;
}
