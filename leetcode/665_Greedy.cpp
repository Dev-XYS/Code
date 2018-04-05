class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		int cnt = 0;
		nums.insert(nums.begin(), INT_MIN);
		for (int i = 2; i < nums.size(); i++)
		{
			if (nums[i] < nums[i - 1])
			{
				if (++cnt > 1) return false;
				if (nums[i] < nums[i - 2])
				{
					nums[i] = nums[i - 1];
				}
			}
		}
		return true;
	}
};
