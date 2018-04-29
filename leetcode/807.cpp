// Problem Name: Max Increase to Keep City Skyline

class Solution {
public:
	int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
		const int r = grid.size(), c = grid[0].size();
		vector<int> maxr(r), maxc(c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (grid[i][j] > maxr[i]) maxr[i] = grid[i][j];
				if (grid[i][j] > maxc[j]) maxc[j] = grid[i][j];
			}
		}
		int ans = 0;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				ans += min(maxr[i], maxc[j]) - grid[i][j];
			}
		}
		return ans;
	}
};
