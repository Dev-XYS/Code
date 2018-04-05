class Solution {
public:
	int n;
	vector<vector<int>> G;
	bool vis[200];

	void dfs(int u) {
		if (vis[u] == true) return;
		vis[u] = true;
		for (int i = 0; i < n; i++)
		{
			if (G[u][i] == 1)
			{
				dfs(i);
			}
		}
	}

	int findCircleNum(vector<vector<int>>& M) {
		n = M.size();
		G = M;
		memset(vis, 0, n);
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			if (vis[i] == false)
			{
				ans++;
				dfs(i);
			}
		}
		return ans;
	}
};
