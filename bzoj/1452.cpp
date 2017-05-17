// Problem Name: Count
// Source: [JSOI2009]

#include <cstdio>

#define LOWBIT(x) ((x) & (-(x)))

using namespace std;

int n, m, num[301][301], q, f[101][301][301];

void modify(int c, int x, int y, int v)
{
	for (int _x = x; _x <= n; _x += LOWBIT(_x))
	{
		for (int _y = y; _y <= m; _y += LOWBIT(_y))
		{
			f[c][_x][_y] += v;
		}
	}
}

int query(int c, int x, int y)
{
	int res = 0;
	for (int _x = x; _x > 0; _x -= LOWBIT(_x))
	{
		for (int _y = y; _y > 0; _y -= LOWBIT(_y))
		{
			res += f[c][_x][_y];
		}
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &num[i][j]);
			modify(num[i][j], i, j, 1);
		}
	}
	scanf("%d", &q);
	int op, x1, y1, x2, y2, c;
	while (q--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d%d", &x1, &y1, &c);
			modify(num[x1][y1], x1, y1, -1);
			modify(c, x1, y1, 1);
			num[x1][y1] = c;
		}
		else
		{
			scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
			printf("%d\n", query(c, x2, y2) - query(c, x1 - 1, y2) - query(c, x2, y1 - 1) + query(c, x1 - 1, y1 - 1));
		}
	}
	return 0;
}
