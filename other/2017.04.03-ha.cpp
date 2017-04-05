#include <cstdio>
#include <algorithm>

#define INF 1e9

using namespace std;

struct raw_edge
{
	int u, v, w;
}R[5010];

int ivc, iec, q, dis[160][160][160];

inline bool _raw_edge_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.w < y.w;
}

void init()
{
	for (int i = 1; i <= ivc; i++)
	{
		for (int j = 1; j <= ivc; j++)
		{
			for (int k = 0; k < ivc; k++)
			{
				dis[i][j][k] = INF;
			}
		}
		dis[i][i][0] = 0;
	}
}

int main()
{
	scanf("%d%d%d", &ivc, &iec, &q);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].w);
	}
	sort(R, R + iec, _raw_edge_cmp_);
	init();
	for (int k = 0; k < iec; k++)
	{
		for (int i = 1; i <= ivc; i++)
		{
			for (int j = 0; j < ivc; j++)
			{
				int newdis = dis[i][R[k].u][j] + R[k].w;
				if (newdis < dis[i][R[k].v][j + 1]) dis[i][R[k].v][j + 1] = newdis;
			}
		}
	}
	int u, v, k;
	while (q--)
	{
		int ans = INF;
		scanf("%d%d%d", &u, &v, &k);
		if (k >= ivc) k = ivc - 1;
		for (int i = 0; i <= k; i++)
		{
			if (dis[u][v][i] < ans) ans = dis[u][v][i];
		}
		printf("%d\n", ans < INF ? ans : -1);
	}
	return 0;
}
