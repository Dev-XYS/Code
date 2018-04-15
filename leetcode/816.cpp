class Solution {
public:
	bool check(string a, string b) {
		if (a[0] == '0' && a.length() > 1) return false;
		if (b.length() > 0 && b[b.length() - 1] == '0') return false;
		return true;
	}

	vector<string> ambiguousCoordinates(string S) {
		vector<string> ans;
		S = S.substr(1, S.length() - 2);
		for (int i = 1; i < S.length(); i++)
		{
			string s1 = S.substr(0, i), s2 = S.substr(i);
			for (int j = 1; j <= i; j++)
			{
				string s11 = s1.substr(0, j), s12 = s1.substr(j);
				if (check(s11, s12) == false) continue;
				for (int k = 1; k <= S.length() - i; k++)
				{
					string s21 = s2.substr(0, k), s22 = s2.substr(k);
					if (check(s21, s22) == true)
					{
						ans.push_back("(" + s11 + (s12 == "" ? "" : "." + s12) + ", " + s21 + (s22 == "" ? "" : "." + s22) + ")");
					}
				}
			}
		}
		return ans;
	}
};
