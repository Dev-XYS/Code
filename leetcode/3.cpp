// Problem Name: Longest Substring Without Repeating Characters

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int cnt[256];
		memset(cnt, 0, sizeof(cnt));
		int p = 0, ans = 0;
		for (int i = 0; i < s.length(); i++)
		{
			while (p < s.length() && cnt[s[p]] == 0)
			{
				cnt[s[p++]] = 1;
			}
			ans = max(ans, p - i);
			if (p == s.length()) break;
			cnt[s[i]] = 0;
		}
		return ans;
	}
};
