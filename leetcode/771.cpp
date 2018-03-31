class Solution {
public:
	int numJewelsInStones(string J, string S) {
		int lJ = J.length(), lS = S.length();
		int jewels[256];
		memset(jewels, 0, sizeof(jewels));
		for (int i = 0; i < lJ; i++)
		{
			jewels[J[i]] = 1;
		}
		int ans = 0;
		for (int i = 0; i < lS; i++)
		{
			ans += jewels[S[i]];
		}
		return ans;
	}
};
