// Problem Name: 社交网络
// Source: [NOI2007]

#include <cstdio>

#define INF 1000000000

typedef long long ll;

using namespace std;

int n, m, dis[105][105];
ll cnt[105][105];

void init()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			dis[i][j] = INF;
		}
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
				int newdis = dis[i][k] + dis[k][j];
				if (newdis < dis[i][j])
				{
					dis[i][j] = newdis;
					cnt[i][j] = cnt[i][k] * cnt[k][j];
				}
				else if (newdis == dis[i][j])
				{
					cnt[i][j] += cnt[i][k] * cnt[k][j];
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	int u, v, w;
	init();
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = dis[v][u] = w;
		cnt[u][v] = cnt[v][u] = 1;
	}
	floyd();
	for (int i = 1; i <= n; i++)
	{
		double ans = 0;
		for (int s = 1; s <= n; s++)
		{
			if (s == i) continue;
			for (int t = 1; t <= n; t++)
			{
				if (t == i) continue;
				if (dis[s][i] + dis[i][t] == dis[s][t])
				{
					ans += (double)(cnt[s][i] * cnt[i][t]) / (double)cnt[s][t];
				}
			}
		}
		printf("%.3lf\n", ans);
	}
	return 0;
}
