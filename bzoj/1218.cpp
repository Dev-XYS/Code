// Problem Name: 激光炸弹
// Source: [HNOI2003]

#include <cstdio>

using namespace std;

int n, r, s[5010][5010];

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

int main()
{
	scanf("%d%d", &n, &r);
	int x, y, c;
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &x, &y, &c);
		s[x + 1][y + 1] += c;
	}
	for (int i = 1; i <= 5001; i++)
	{
		s[0][i] += s[0][i - 1];
	}
	for (int i = 1; i <= 5001; i++)
	{
		for (int j = 1; j <= 5001; j++)
		{
			s[i][j] += s[i][j - 1];
		}
		for (int j = 0; j <= 5001; j++)
		{
			s[i][j] += s[i - 1][j];
		}
	}
	int ans = 0;
	for (int i = 0; i + r <= 5001; i++)
	{
		for (int j = 0; j + r <= 5001; j++)
		{
			check_max(ans, s[i + r][j + r] - s[i][j + r] - s[i + r][j] + s[i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
