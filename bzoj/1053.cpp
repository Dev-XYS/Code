// Problem Name: 反素数
// Source: [HAOI2007]

#include <cstdio>

#define INF 2000000000

typedef long long ll;

using namespace std;

const int prime[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
ll ppow[10][33];
int n, minnum[3010];

void init_ppow()
{
	for (int i = 0; i < 10; i++)
	{
		ppow[i][0] = 1;
		for (int j = 1; j <= 32; j++)
		{
			ppow[i][j] = ppow[i][j - 1] * prime[i];
		}
	}
}

void dfs(int k, int num, int c)
{
	if (num < minnum[c]) minnum[c] = num;
	if (k >= 10) return;
	for (int i = 1; i <= 32; i++)
	{
		if (n / num >= ppow[k][i]) dfs(k + 1, num * ppow[k][i], c * (i + 1));
		else break;
	}
}

int main()
{
	scanf("%d", &n);
	init_ppow();
	for (int i = 1; i <= 3000; i++)
	{
		minnum[i] = INF + 1;
	}
	dfs(0, 1, 1);
	int ans = 0;
	for (int i = 3000; i >= 1; i--)
	{
		if (minnum[i] <= INF)
		{
			ans = minnum[i];
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
