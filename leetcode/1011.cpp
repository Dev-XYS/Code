// Problem Name: Capacity To Ship Packages Within D Days

class Solution {
public:
	int shipWithinDays(vector<int> &weights, int D) {
		int n = weights.size(), l = 0, r = 0;
		for (auto w : weights) {
			if (w > l) {
				l = w;
			}
			r += w;
		}
		while (l < r) {
			int mid = (l + r) / 2;
			int s = 0, c = 1;
			bool can = true;
			for (auto w : weights) {
				s += w;
				if (s > mid) {
					if (++c > D) {
						can = false;
					}
					s = w;
				}
			}
			if (can) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		return l;
	}
};
