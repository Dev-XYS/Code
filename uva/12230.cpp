// Problem Name: Crossing Rivers

#include <cstdio>

using namespace std;

int main()
{
	int n, D, p, L, v, casen = 1;
	while (true)
	{
		scanf("%d%d", &n, &D);
		if (n == 0 && D == 0) break;
		double ans = D;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d", &p, &L, &v);
			ans -= L;
			ans += (double)L * 2 / (double)v;
		}
		printf("Case %d: %.3lf\n\n", casen++, ans);
	}
	return 0;
}
