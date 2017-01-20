#include <cstdio>

using namespace std;

int n, m, x, res[32][2];
char op[10];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 30; i >= 0; i--)
	{
		res[i][1] = 1 << i;
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%s%d", op, &x);
		for (int k = 30; k >= 0; k--)
		{
			if (op[0] == 'A') res[k][0] &= (x & (1 << k)), res[k][1] &= (x & (1 << k));
			else if (op[0] == 'O') res[k][0] |= (x & (1 << k)), res[k][1] |= (x & (1 << k));
			else res[k][0] ^= (x & (1 << k)), res[k][1] ^= (x & (1 << k));
		}
	}
	int use = 0, ans = 0;
	for (int i = 30; i >= 0; i--)
	{
		if (res[i][0] != 0)
		{
			ans += res[i][0];
		}
		else if (use + (1 << i) <= m && res[i][1] != 0)
		{
			use += (1 << i);
			ans += res[i][1];
		}
	}
	printf("%d", ans);
	return 0;
}
