class Solution {
public:
	int expressiveWords(string S, vector<string>& words) {
		int ans = 0;
		S += ' ';
		for (int i = 0; i < words.size(); i++)
		{
			words[i] += ' ';
			bool strechy = true;
			int ps = -1, lens = 0, pw = -1, lenw = 0;
			while (ps < (int)S.length() - 1 && pw < (int)words[i].length() - 1)
			{
				ps++;
				lens = 1;
				pw++;
				lenw = 1;
				while (S[ps + 1] == S[ps])
				{
					ps++;
					lens++;
				}
				while (words[i][pw + 1] == words[i][pw])
				{
					pw++;
					lenw++;
				}
				if (S[ps] != words[i][pw])
				{
					strechy = false;
					break;
				}
				if (lens < lenw || (lens == 2 && lenw == 1))
				{
					strechy = false;
					break;
				}
			}
			if (ps != S.length() - 1 || pw != words[i].length() - 1)
			{
				strechy = false;
			}
			if (strechy == true)
			{
				ans++;
			}
		}
		return ans;
	}
};
