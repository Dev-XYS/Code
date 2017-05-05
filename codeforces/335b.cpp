// Problem Name: Palindrome
// Source: MemSQL start[c]up Round 2 - online version, Problem B

#include <cstdio>
#include <cstring>

using namespace std;

char s[50010], res[50010];
int len, dp[2600][2600], prel[2600][2600], prer[2600][2600];

void print()
{
	int l = prel[0][len - 1], r = prer[0][len - 1], c = 0;
	bool odd = false;
	while (true)
	{
		res[c++] = s[l];
		if (l == r)
		{
			odd = true;
			break;
		}
		if (l + 1 > r - 1) break;
		int _l = prel[l + 1][r - 1], _r = prer[l + 1][r - 1];
		l = _l, r = _r;
	}
	if (c > 50 || (c == 50 && odd == false))
	{
		for (int i = 0; i < 50; i++)
		{
			printf("%c", res[i]);
		}
		for (int i = 50 - 1; i >= 0; i--)
		{
			printf("%c", res[i]);
		}
	}
	else
	{
		for (int i = 0; i < c - 1; i++)
		{
			printf("%c", res[i]);
		}
		if (odd == true) printf("%c", res[c - 1]);
		else printf("%c%c", res[c - 1], res[c - 1]);
		for (int i = c - 2; i >= 0; i--)
		{
			printf("%c", res[i]);
		}
	}
}

int main()
{
	scanf("%s", s);
	len = strlen(s);
	if (len < 2600)
	{
		for (int i = 0; i < len; i++)
		{
			dp[i][i] = 1;
			prel[i][i] = prer[i][i] = i;
		}
		for (int l = 2; l <= len; l++)
		{
			for (int i = 0; i <= len - l; i++)
			{
				int j = i + l - 1;
				if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2, prel[i][j] = i, prer[i][j] = j;
				else
				{
					if (dp[i + 1][j] > dp[i][j - 1])
					{
						dp[i][j] = dp[i + 1][j];
						prel[i][j] = prel[i + 1][j];
						prer[i][j] = prer[i + 1][j];
					}
					else
					{
						dp[i][j] = dp[i][j - 1];
						prel[i][j] = prel[i][j - 1];
						prer[i][j] = prer[i][j - 1];
					}
				}
			}
		}
		print();
	}
	else
	{
		int cnt[256];
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < len; i++)
		{
			cnt[(int)s[i]]++;
			if (cnt[(int)s[i]] >= 100)
			{
				for (int j = 0; j < 100; j++)
				{
					printf("%c", s[i]);
				}
				return 0;
			}
		}
	}
	return 0;
}
