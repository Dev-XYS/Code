#include <cstdio>

typedef long long ll;

using namespace std;

ll l, r, k, ans[100], ac;

int main()
{
	scanf("%lld%lld%lld", &l, &r, &k);
	ll p = 1;
	while (true)
	{
		if (p >= l)
		{
			ans[ac++] = p;
		}
		if (r / p >= k)
		{
			p *= k;
		}
		else
		{
			break;
		}
	}
	if (ac == 0)
	{
		printf("-1\n");
	}
	for (int i = 0; i < ac; i++)
	{
		printf("%lld ", ans[i]);
	}
	return 0;
}
