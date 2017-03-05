// Problem Name: albus就是要第一个出场

#include <cstdio>

#define MOD 10086

using namespace std;

int n, q, d[100010], b[32], bsize;

void linear_basis()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 30; j >= 0 && d[i] != 0; j--)
		{
			if ((d[i] >> j) == 0) continue;
			else if (b[j] != 0) d[i] ^= b[j];
			else
			{
				b[j] = d[i];
				bsize++;
				break;
			}
		}
	}
}

int pow(int a, int x)
{
	int res = 1;
	for (int i = 0; i < x; i++)
	{
		res = res * a % MOD;
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	scanf("%d", &q);
	linear_basis();
	int ans = 0, c = bsize;
	for (int i = 30; i >= 0; i--)
	{
		if (b[i] == 0) continue;
		c--;
		if ((q & (1 << i)) != 0) ans = (ans + pow(2, c)) % MOD;
	}
	ans = (ans * pow(2, n - bsize) + 1) % MOD;
	printf("%d", ans);
	return 0;
}
