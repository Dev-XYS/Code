// Problem Name: Intersection of Two Arrays

class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		auto it = unique(nums1.begin(), nums1.end());
		nums1.erase(it, nums1.end());
		vector<int> ans;
		int p = 0;
		for (int i = 0; i < nums1.size(); i++)
		{
			while (p < nums2.size() && nums2[p] < nums1[i])
			{
				p++;
			}
			if (p < nums2.size() && nums2[p] == nums1[i])
			{
				ans.push_back(nums1[i]);
			}
		}
		return ans;
	}
};
