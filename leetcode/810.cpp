class Solution {
public:
	bool xorGame(vector<int>& nums) {
		int x = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			x ^= nums[i];
		}
		if (x == 0)
		{
			return true;
		}
		return (nums.size() & 1) == 0;
	}
};
