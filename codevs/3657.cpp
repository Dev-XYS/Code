#include <cstdio>
#include <cstring>

#define INF 1000000000

using namespace std;

char s[210];
int dp[210][210];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main()
{
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		dp[i][i] = 1;
	}
	for (int l = 2; l <= len; l++)
	{
		for (int i = 0; i <= len - l; i++)
		{
			dp[i][i + l - 1] = INF;
			for (int k = i; k < i + l - 1; k++)
			{
				dp[i][i + l - 1] = min(dp[i][i + l - 1], dp[i][k] + dp[k + 1][i + l - 1]);
			}
			if ((s[i] == '(' && s[i + l - 1] == ')') || (s[i] == '[' && s[i + l - 1] == ']')) dp[i][i + l - 1] = min(dp[i][i + l - 1], dp[i + 1][i + l - 2]);
			else dp[i][i + l - 1] = min(dp[i][i + l - 1], dp[i + 1][i + l - 2] + 2);
		}
	}
	printf("%d", dp[0][len - 1] + len);
	return 0;
}
