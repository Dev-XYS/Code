class Solution {
public:
	vector<int> sortArrayByParityII(vector<int>& A) {
		vector<int> r;
		r.resize(A.size());
		int p = 0, q = 1;
		for (auto x : A) {
			if (x & 1) {
				r[q] = x;
				q += 2;
			}
			else {
				r[p] = x;
				p += 2;
			}
		}
		return r;
	}
};