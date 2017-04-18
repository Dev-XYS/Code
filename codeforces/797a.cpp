// Problem Name: k-Factorization
// Source: Educational Codeforces Round 19, Problem A

#include <cstdio>

using namespace std;

int main()
{
	int n, k, ans[30], ac = 0;
	scanf("%d%d", &n, &k);
	for (int i = 2; i * i <= n; i++)
	{
		if (ac == k - 1) break;
		if (n % i == 0)
		{
			ans[ac++] = i;
			n /= i;
			i--;
		}
	}
	if (ac < k - 1) printf("-1\n");
	else
	{
		for (int i = 0; i < k - 1; i++)
		{
			printf("%d ", ans[i]);
		}
		printf("%d\n", n);
	}
	return 0;
}
