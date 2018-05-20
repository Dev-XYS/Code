// Problem Name: Maximum Average Subarray I

class Solution {
public:
	double findMaxAverage(vector<int>& nums, int k) {
		int sum = 0, max_sum, i;
		for (i = 0; i < k; i++)
		{
			sum += nums[i];
		}
		max_sum = sum;
		for (; i < nums.size(); i++)
		{
			sum += nums[i];
			sum -= nums[i - k];
			max_sum = max(max_sum, sum);
		}
		return (double)max_sum / k;
	}
};
