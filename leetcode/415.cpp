class Solution {
public:
	string addStrings(string num1, string num2) {
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		string ans;
		int carry = 0;
		for (int i = 0; i < max(num1.length(), num2.length()); i++)
		{
			if (i < num1.length()) carry += num1[i] - '0';
			if (i < num2.length()) carry += num2[i] - '0';
			ans += (char)(carry % 10 + '0');
			carry /= 10;
		}
		if (carry > 0) ans += '1';
		reverse(ans.begin(), ans.end());
		return ans;
	}
};
