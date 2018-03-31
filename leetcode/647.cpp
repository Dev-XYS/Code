class Solution {
public:
	int findLengthOfLCIS(vector<int>& nums) {
		const int n = nums.size();
		if (n == 0)
		{
			return 0;
		}
		int ans = 0, len = 1;
		for (int i = 1; i < n; i++)
		{
			if (nums[i] <= nums[i - 1])
			{
				if (len > ans)
				{
					ans = len;
				}
				len = 1;
			}
			else
			{
				len++;
			}
		}
		if (len > ans)
		{
			ans = len;
		}
		return ans;
	}
};
