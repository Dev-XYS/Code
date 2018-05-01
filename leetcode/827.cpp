// Problem Name: Making A Large Island

class Solution {
public:
	int n, m, fa[2500], size[2500];

	void init_dsu() {
		for (int i = n * m - 1; i >= 0; i--)
		{
			fa[i] = i;
			size[i] = 1;
		}
	}

	int getrt(int x) {
		return fa[x] == x ? x : fa[x] = getrt(fa[x]);
	}

	void merge(int x, int y) {
		int rtx = getrt(x), rty = getrt(y);
		if (rtx == rty) return;
		int sx = size[rtx], sy = size[rty];
		if (sx < sy)
		{
			fa[rtx] = rty;
			size[rty] += sx;
		}
		else
		{
			fa[rty] = rtx;
			size[rtx] += sy;
		}
	}

	int index(int x, int y) {
		return x * m + y;
	}

	int largestIsland(vector<vector<int>>& grid) {
		n = grid.size();
		m = grid[0].size();
		init_dsu();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 1)
				{
					if (i < n - 1 && grid[i + 1][j] == 1) merge(index(i, j), index(i + 1, j));
					if (j < m - 1 && grid[i][j + 1] == 1) merge(index(i, j), index(i, j + 1));
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 0)
				{
					vector<int> blocks;
					if (i > 0 && grid[i - 1][j] == 1) blocks.push_back(getrt(index(i - 1, j)));
					if (i < n - 1 && grid[i + 1][j] == 1) blocks.push_back(getrt(index(i + 1, j)));
					if (j > 0 && grid[i][j - 1] == 1) blocks.push_back(getrt(index(i, j - 1)));
					if (j < m - 1 && grid[i][j + 1] == 1) blocks.push_back(getrt(index(i, j + 1)));
					sort(blocks.begin(), blocks.end());
					vector<int>::iterator end = unique(blocks.begin(), blocks.end());
					int cnt = 1;
					for (vector<int>::iterator it = blocks.begin(); it != end; it++)
					{
						cnt += size[*it];
					}
					if (cnt > ans) ans = cnt;
				}
				else
				{
					ans = max(ans, size[getrt(index(i, j))]);
				}
			}
		}
		return ans;
	}
};
