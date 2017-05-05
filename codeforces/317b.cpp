// Problem Name: Ants
// Source: Codeforces Round #188 (Div. 1), Problem B

#include <cstdio>
#include <cstring>

using namespace std;

struct _map_
{
	int cnt[131][131];
	void set(int x, int y, int v) { cnt[x + 65][y + 65] = v; }
	int get(int x, int y) { return cnt[x + 65][y + 65]; }
	bool move();
}map;

const int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };

bool _map_::move()
{
	static int _cnt[131][131];
	bool has = false;
	memset(_cnt, 0, sizeof(_cnt));
	for (int i = 1; i < 130; i++)
	{
		for (int j = 1; j < 130; j++)
		{
			if (map.cnt[i][j] >= 4) has = true;
			_cnt[i][j] += map.cnt[i][j] & 3;
			for (int k = 0; k < 4; k++)
			{
				_cnt[i + dx[k]][j + dy[k]] += map.cnt[i][j] >> 2;
			}
		}
	}
	memcpy(map.cnt, _cnt, sizeof(_cnt));
	return has;
}

int n, t;

void move()
{
	map.set(0, 0, n);
	while (map.move() == true) ;
}

int main()
{
	scanf("%d%d", &n, &t);
	move();
	int x, y;
	while (t--)
	{
		scanf("%d%d", &x, &y);
		if (x < -65 || x > 65 || y < -65 || y > 65) printf("0\n");
		else printf("%d\n", map.get(x, y));
	}
	return 0;
}
