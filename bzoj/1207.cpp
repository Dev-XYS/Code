// Problem Name: 打鼹鼠
// Source: [HNOI2004]

#include <cstdio>
#include <algorithm>

using namespace std;

struct event
{
	int time, x, y;
}d[10010];

int n, m, dp[10010];

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline int dist(int i, int j)
{
	return abs(d[i].x - d[j].x) + abs(d[i].y - d[j].y);
}

inline bool _event_time_cmp_(const event &x, const event &y)
{
	return x.time < y.time;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &d[i].time, &d[i].x, &d[i].y);
	}
	sort(d, d + m, _event_time_cmp_);
	for (int i = 0; i < m; i++)
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (dist(i, j) <= d[i].time - d[j].time)
			{
				if (dp[j] >= dp[i]) dp[i] = dp[j] + 1;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		if (dp[i] > ans) ans = dp[i];
	}
	printf("%d\n", ans);
	return 0;
}
