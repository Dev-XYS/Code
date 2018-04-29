// Problem Name: Integer Replacement

class Solution {
public:
	map<unsigned int, int> ans;

	int solve(unsigned int n) {
		if (ans.count(n) > 0) return ans[n];
		if ((n & 1) == 0)
		{
			return ans[n] = solve(n >> 1) + 1;
		}
		else
		{
			return ans[n] = min(solve(n - 1), solve(n + 1)) + 1;
		}
	}

	int integerReplacement(int n) {
		ans[1] = 0;
		return solve(n);
	}
};
