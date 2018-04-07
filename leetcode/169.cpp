// Problem Name: Majority Element

class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int num = 0, cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (cnt1 == 0)
			{
				num = nums[i];
				cnt1 = 1;
			}
			else
			{
				if (nums[i] == num)
				{
					cnt1++;
				}
				else
				{
					cnt2++;
					if (cnt1 == cnt2)
					{
						cnt1 = cnt2 = 0;
					}
				}
			}
		}
		return num;
	}
};
