// Problem Name: Total Hamming Distance

class Solution {
public:
	int totalHammingDistance(vector<int> &nums) {
		int cnt[31];
		memset(cnt, 0, sizeof(cnt));
		for (auto v : nums) {
			for (int i = 0; i < 31; i++) {
				cnt[i] += (v & (1 << i)) >> i;
			}
		}
		int a = 0;
		for (int i = 0; i < 31; i++) {
			a += cnt[i] * (nums.size() - cnt[i]);
		}
		return a;
	}
};
