// Problem Name: Most Common Word

class Solution {
public:
	string mostCommonWord(string paragraph, vector<string>& banned) {
		bool punc[256];
		memset(punc, 0, sizeof(punc));
		punc[' '] = true;
		punc['!'] = true;
		punc['?'] = true;
		punc['\''] = true;
		punc[','] = true;
		punc[';'] = true;
		punc['.'] = true;
		map<string, int> M;
		string temp;
		paragraph += ' ';
		for (int i = 0; i < paragraph.length(); i++)
		{
			if (punc[paragraph[i]] == true)
			{
				transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
				M[temp]++;
				temp = "";
			}
			else
			{
				temp += paragraph[i];
			}
		}
		string ans;
		int cnt = 0;
		banned.push_back("");
		for (map<string, int>::iterator it = M.begin(); it != M.end(); it++)
		{
			if (find(banned.begin(), banned.end(), it->first) == banned.end() && it->second > cnt)
			{
				ans = it->first;
				cnt = it->second;
			}
		}
		return ans;
	}
};
