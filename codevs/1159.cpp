// Problem Name: 最大全0子矩阵
// Algorithm: 悬线法

#include <cstdio>

#define INF 1000000000

using namespace std;

int n, matrix[2010][2010], rl[2010][2010], rr[2010][2010], up[2010][2010], l[2010][2010], r[2010][2010], size[2010][2010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int reverse(int x)
{
	return x == 0 ? 1 : 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (matrix[i][j] == 1) rl[i][j] = 0;
			else rl[i][j] = rl[i][j - 1] + 1;
		}
		for (int j = n; j >= 1; j--)
		{
			if (matrix[i][j] == 1) rr[i][j] = 0;
			else rr[i][j] = rr[i][j + 1] + 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		l[0][i] = INF;
		r[0][i] = INF;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (matrix[i][j] == 1) up[i][j] = 0, l[i][j] = INF, r[i][j] = INF;
			else
			{
				up[i][j] = up[i - 1][j] + 1;
				l[i][j] = min(l[i - 1][j], rl[i][j]);
				r[i][j] = min(r[i - 1][j], rr[i][j]);
				size[i][j] = (l[i][j] + r[i][j] - 1) * up[i][j];
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (size[i][j] > ans) ans = size[i][j];
		}
	}
	printf("%d\n", ans);
	return 0;
}
