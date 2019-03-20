class Solution {
public:
	int dominantIndex(vector<int>& nums) {
		int p = 0;
		for (int i = 1; i < (int)nums.size(); i++) {
			if (nums[i] > nums[p]) {
				p = i;
			}
		}
		for (int i = 0; i < (int)nums.size(); i++) {
			if (nums[i] != nums[p]) {
				if (nums[i] * 2 > nums[p]) {
					return -1;
				}
			}
		}
		return p;
	}
};