class Solution {
public:
	struct sort_struct {
		double f;
		int p, q;
		inline bool operator < (const sort_struct &x) {
			return f < x.f;
		}
	};
	
	vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
		const int n = A.size();
		vector<sort_struct> F;
		F.reserve(n * (n - 1) / 2);
		int p = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				F.push_back((sort_struct){ (double)A[i] / A[j], A[i], A[j] });
			}
		}
		nth_element(F.begin(), F.begin() + K - 1, F.end());
		return { F[K - 1].p, F[K - 1].q };
	}
};
