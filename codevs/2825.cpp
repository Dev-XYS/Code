// Problem Name: 危险的组合

#include <cstdio>

typedef long long ll;

using namespace std;

ll f[100];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 3; i <= n; i++)
	{
		f[i] = (1 << (i - 3)) + f[i - 1] + f[i - 2] + f[i - 3];
	}
	printf("%lld\n", f[n]);
	return 0;
}
