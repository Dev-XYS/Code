// Problem Name: 约数研究 Common
// Source: [AHOI2005]

#include <cstdio>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += n / i;
	}
	printf("%lld", ans);
	return 0;
}
