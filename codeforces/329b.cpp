// Problem Name: Biridian Forest
// Source: Codeforces Round #192 (Div. 1), Problem B
// Algorithm: 最短路

#include <cstdio>
#include <queue>

#define INF 1000000000

using namespace std;

struct point
{
	int x, y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) { }
};

const int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };
int n, m;
char map[1010][1010];
int dis[1010][1010];

int bfs()
{
	int sx, sy, rx, ry;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == 'E')
			{
				sx = i, sy = j;
			}
			if (map[i][j] == 'S')
			{
				rx = i, ry = j;
			}
			dis[i][j] = INF;
		}
	}
	queue<point> Q;
	dis[sx][sy] = 0;
	Q.push(point(sx, sy));
	while (!Q.empty())
	{
		point u = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++)
		{
			int tx = u.x + dx[i], ty = u.y + dy[i];
			if (map[tx][ty] != 0 && map[tx][ty] != 'T' && dis[tx][ty] == INF)
			{
				dis[tx][ty] = dis[u.x][u.y] + 1;
				Q.push(point(tx, ty));
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ('1' <= map[i][j] && map[i][j] <= '9' && dis[i][j] <= dis[rx][ry]) res += map[i][j] - '0';
		}
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", map[i] + 1);
	}
	printf("%d\n", bfs());
	return 0;
}
