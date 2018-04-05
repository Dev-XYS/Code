class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		if (nums.size() <= 1) return true;
		int l1 = 1, l2 = (nums[1] >= nums[0] ? 2 : 1);
		for (int i = 2; i < nums.size(); i++)
		{
			int l = 0;
			if (nums[i] >= nums[i - 1])
			{
				l = l2 + 1;
			}
			if (nums[i] >= nums[i - 2])
			{
				l = max(l, l1 + 1);
			}
			l1 = l2;
			l2 = l;
		}
		return max(l1, l2) >= nums.size() - 1;
	}
};
