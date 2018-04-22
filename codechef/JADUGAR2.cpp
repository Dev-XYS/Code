// Problem Name: Chef and Same Old Recurrence 2

#include <cstdio>

#define MOD 1000000007

typedef long long ll;

using namespace std;

int N, K, A, B, Q, F[10000010], R[10000010];

int main()
{
	scanf("%d%d%d%d%d", &N, &K, &A, &B, &Q);
	F[1] = K;
	F[2] = ((ll)A * K + (ll)B * K % MOD * K % MOD) % MOD;
	R[1] = 1;
	R[2] = 500000004;
	for (int i = 3; i <= N; i++)
	{
		F[i] = ((A + (ll)2 * B * K) % MOD * (2 * i - 3) % MOD * F[i - 1] % MOD - (ll)A * A % MOD * (i - 3) % MOD * F[i - 2] % MOD) % MOD;
		R[i] = -(ll)(MOD / i) * R[MOD % i] % MOD;
		F[i] = (ll)F[i] * R[i] % MOD;
	}
	for (int i = 1; i <= N; i++)
	{
		F[i] = (F[i - 1] + (ll)F[i] * F[i]) % MOD;
	}
	int l, r;
	while (Q--)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", (F[r] - F[l - 1] + MOD) % MOD);
	}
	return 0;
}
