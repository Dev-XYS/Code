// Problem Name: House Robber II

typedef long long ll;

class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		if (nums.size() == 1) return nums[0];
		ll *first0 = new ll[nums.size()], *first1 = new ll[nums.size()];
		first0[0] = 0;
		first1[0] = nums[0];
		first0[1] = nums[1];
		first1[1] = first1[0];
		for (int i = 2; i < nums.size(); i++)
		{
			first0[i] = max(first0[i - 1], first0[i - 2] + nums[i]);
			first1[i] = max(first1[i - 1], first1[i - 2] + nums[i]);
		}
		return max(first0[nums.size() - 1], first1[nums.size() - 2]);
	}
};
