class Solution {
private:
	string longestCommonPrefix(string &x, string &y) {
		string r;
		for (int i = 0; i < min(x.size(), y.size()); i++)
		{
			if (x[i] == y[i]) r += x[i];
			else break;
		}
		return r;
	}

public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() == 0) return "";
		string r = strs[0];
		for (int i = 1; i < (int)strs.size(); i++)
		{
			r = longestCommonPrefix(r, strs[i]);
		}
		return r;
	}
};
