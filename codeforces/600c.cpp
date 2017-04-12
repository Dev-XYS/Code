// Problem Name: Make Palindrome
// Source: CodeForces, Educational Codeforces Round 2, Problem C

#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	int cnt[26];
	char ch;
	memset(cnt, 0, sizeof(cnt));
	ch = getchar();
	while ('a' <= ch && ch <= 'z')
	{
		cnt[ch - 'a']++;
		ch = getchar();
	}
	int odd = 0;
	for (int i = 0; i < 26; i++)
	{
		if ((cnt[i] & 1) == 1) odd++;
	}
	int c = 0;
	for (int i = 0; i < 26 && c < (odd >> 1); i++)
	{
		if ((cnt[i] & 1) == 1) cnt[i]++, c++;
	}
	c = 0;
	for (int i = 26 - 1; i >= 0 && c < (odd >> 1); i--)
	{
		if ((cnt[i] & 1) == 1) cnt[i]--, c++;
	}
	for (int i = 0; i < 26; i++)
	{
		int h = cnt[i] >> 1;
		for (int j = 0; j < h; j++)
		{
			putchar(i + 'a');
		}
	}
	if ((odd & 1) == 1)
	{
		for (int i = 0; i < 26; i++)
		{
			if ((cnt[i] & 1) == 1)
			{
				putchar(i + 'a');
				cnt[i]--;
				break;
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		cnt[i] >>= 1;
	}
	for (int i = 26 - 1; i >= 0; i--)
	{
		for (int j = 0; j < cnt[i]; j++)
		{
			putchar(i + 'a');
		}
	}
	return 0;
}
