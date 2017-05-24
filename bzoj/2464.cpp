// Problem Name: 小明的游戏
// Source: [中山市选2009]

#include <cstdio>
#include <queue>

#define INF 1000000000

using namespace std;

struct queue_node
{
	int x, y, dis;
	queue_node(int _x, int _y, int _dis) : x(_x), y(_y), dis(_dis) { }
};

const int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };
int n, m, x1, y1, x2, y2, dis[510][510];
char map[510][510];
bool vis[510][510];

inline bool operator < (const queue_node &x, const queue_node &y)
{
	return x.dis > y.dis;
}

void init_single_source()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			dis[i][j] = INF;
			vis[i][j] = false;
		}
	}
	dis[x1][y1] = 0;
}

void dijkstra()
{
	init_single_source();
	priority_queue<queue_node> Q;
	Q.push(queue_node(x1, y1, 0));
	while (true)
	{
		queue_node u = Q.top();
		Q.pop();
		if (u.x == x2 && u.y == y2) break;
		if (vis[u.x][u.y] == true) break;
		vis[u.x][u.y] = true;
		for (int i = 0; i < 4; i++)
		{
			int x = u.x + dx[i], y = u.y + dy[i];
			if (x <= 0 || x > n || y <= 0 || y > m) continue;
			int newdis = dis[u.x][u.y] + (map[x][y] == map[u.x][u.y] ? 0 : 1);
			if (newdis < dis[x][y])
			{
				dis[x][y] = newdis;
				Q.push(queue_node(x, y, newdis));
			}
		}
	}
}

int main()
{
	while (true)
	{
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", map[i] + 1);
		}
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1++, y1++, x2++, y2++;
		dijkstra();
		printf("%d\n", dis[x2][y2]);
	}
	return 0;
}
