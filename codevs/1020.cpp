// Problem Name: 孪生蜘蛛

#include <cstdio>

#define INF 1000000000

using namespace std;

int n, dis[105][105], ansx, ansy, time = INF;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline void check_min(int &x, int y)
{
	if (y < x) x = y;
}

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

void init()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			dis[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		dis[i][i] = 0;
	}
}

void floyd()
{
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				check_min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	init();
	int u, v, t;
	while (scanf("%d%d%d", &u, &v, &t) > 0)
	{
		check_min(dis[u][v], t);
		check_min(dis[v][u], t);
	}
	floyd();
	for (int i = n; i >= 1; i--)
	{
		for (int j = n; j >= 1; j--)
		{
			int maxt = 0;
			for (int k = 1; k <= n; k++)
			{
				check_max(maxt, min(dis[i][k], dis[j][k]));
			}
			if (maxt <= time)
			{
				time = maxt;
				ansx = i;
				ansy = j;
			}
		}
	}
	printf("%d %d\n", ansx, ansy);
	return 0;
}
