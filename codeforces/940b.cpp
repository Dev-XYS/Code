// Problem Name: Our Tanya is Crying Out Loud
// Source: Codeforces Round #466 (Div. 2), Problem B

#include <cstdio>

typedef long long ll;

using namespace std;

int k, A, B;

inline ll min(ll x, ll y)
{
	return x < y ? x : y;
}

ll solve(int n)
{
	if (n == 0)
	{
		return -A;
	}
	if (n == 1)
	{
		return 0;
	}
	if (n % k == 0)
	{
		return min(solve(n / k) + B, (ll)A * (n - 1));
	}
	else
	{
		return solve(n - n % k) + (ll)A * (n % k);
	}
}

int main()
{
	int n;
	scanf("%d%d%d%d", &n, &k, &A, &B);
	if (k == 1)
	{
		printf("%I64d\n", (ll)A * (n - 1));
	}
	else
	{
		printf("%I64d\n", solve(n));
	}
	return 0;
}
