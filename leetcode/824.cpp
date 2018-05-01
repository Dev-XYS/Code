// Problem Name: Goat Latin

class Solution {
public:
	bool is_vowel(char c) {
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
		else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return true;
		else return false;
	}

	string repeat(char c, int times) {
		string res;
		for (; times > 0; times--)
		{
			res += c;
		}
		return res;
	}

	string toGoatLatin(string S) {
		string ans;
		int counter = 0;
		while (S != "")
		{
			string word = S.substr(0, S.find(' '));
			S.erase(0, word.length() + 1);
			if (is_vowel(word[0]))
			{
				word += "ma";
			}
			else
			{
				word += word[0];
				word += "ma";
				word.erase(0, 1);
			}
			word += repeat('a', ++counter);
			ans += word + ' ';
		}
		return ans.substr(0, ans.length() - 1);
	}
};
