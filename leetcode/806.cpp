class Solution {
public:
	vector<int> numberOfLines(vector<int>& widths, string S) {
		const int l = S.length();
		int cnt = 1, len = 0;
		for (int i = 0; i < l; i++)
		{
			if (len + widths[S[i] - 'a'] <= 100)
			{
				len += widths[S[i] - 'a'];
			}
			else
			{
				cnt++;
				len = widths[S[i] - 'a'];
			}
		}
		return { cnt, len };
	}
};
