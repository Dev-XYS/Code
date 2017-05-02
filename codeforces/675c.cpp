// Problem Name: Money Transfers
// Source: Codeforces Round #353 (Div. 2), Problem C
// Algorithm: 前缀和, 众数

#include <cstdio>
#include <map>

typedef long long ll;

using namespace std;

int n;
map<ll, int> M;

int main()
{
	scanf("%d", &n);
	int x;
	ll sum = 0;
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		sum += x;
		M[sum]++;
		if (M[sum] > res) res = M[sum];
	}
	printf("%d\n", n - res);
	return 0;
}
