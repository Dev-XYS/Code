#include <cstdio>
#include <cstring>

using namespace std;

const int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };

int n, k, idn, id[510][510], cnt[250010], bcnt[250010], stamp[250010], current;
char map[510][510];

void dfs(int x, int y)
{
	if (map[x][y] != '.' || id[x][y] != 0) return;
	id[x][y] = idn;
	cnt[idn]++;
	for (int i = 0; i < 4; i++)
	{
		dfs(x + dx[i], y + dy[i]);
	}
}

void new_start(int row)
{
	memset(bcnt, 0, sizeof(bcnt));
	for (int j = 1; j <= k; j++)
	{
		for (int p = row; p < row + k; p++)
		{
			bcnt[id[p][j]]++;
		}
	}
	bcnt[0] = 0;
}

void shift_right(int r, int c)
{
	for (int i = r; i < r + k; i++)
	{
		bcnt[id[i][c]]--;
		bcnt[id[i][c + k]]++;
	}
	bcnt[0] = 0;
}

int get_cnt(int r, int c)
{
	int res = 0;
	for (int i = c; i < c + k; i++)
	{
		if (stamp[id[r - 1][i]] != current)
		{
			res += cnt[id[r - 1][i]] - bcnt[id[r - 1][i]];
			stamp[id[r - 1][i]] = current;
		}
		if (stamp[id[r + k][i]] != current)
		{
			res += cnt[id[r + k][i]] - bcnt[id[r + k][i]];
			stamp[id[r + k][i]] = current;
		}
	}
	for (int i = r; i < r + k; i++)
	{
		if (stamp[id[i][c - 1]] != current)
		{
			res += cnt[id[i][c - 1]] - bcnt[id[i][c - 1]];
			stamp[id[i][c - 1]] = current;
		}
		if (stamp[id[i][c + k]] != current)
		{
			res += cnt[id[i][c + k]] - bcnt[id[i][c + k]];
			stamp[id[i][c + k]] = current;
		}
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", map[i] + 1);
	}
	for (int i = 0; i <= n + 1; i++)
	{
		map[0][i] = 'X';
		map[n + 1][i] = 'X';
		map[i][0] = 'X';
		map[i][n + 1] = 'X';
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (map[i][j] == '.' && id[i][j] == 0)
			{
				idn++;
				dfs(i, j);
			}
		}
	}
	int ans = 0, t;
	for (int i = 1; i <= n - k + 1; i++)
	{
		current++;
		new_start(i);
		t = get_cnt(i, 1);
		if (t > ans) ans = t;
		for (int j = 1; j < n - k + 1; j++)
		{
			current++;
			shift_right(i, j);
			t = get_cnt(i, j + 1);
			if (t > ans) ans = t;
		}
	}
	printf("%d\n", ans + k * k);
	return 0;
}
