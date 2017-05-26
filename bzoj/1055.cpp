// Problem Name: 玩具取名
// Source: [HAOI2008]

#include <cstdio>
#include <cstring>

using namespace std;

int W, I, N, G;
char str[210];
bool trans[4][4][4], dp[210][210][4];

inline char convert(char x)
{
	switch (x)
	{
	case 'W':
		return 0;
	case 'I':
		return 1;
	case 'N':
		return 2;
	case 'G':
		return 3;
	default:
		return -1;
	}
}

int main()
{
	scanf("%d%d%d%d", &W, &I, &N, &G);
	char temp[10];
	for (int i = 0; i < W; i++)
	{
		scanf("%s", temp);
		trans[convert(temp[0])][convert(temp[1])][0] = true;
	}
	for (int i = 0; i < I; i++)
	{
		scanf("%s", temp);
		trans[convert(temp[0])][convert(temp[1])][1] = true;
	}
	for (int i = 0; i < N; i++)
	{
		scanf("%s", temp);
		trans[convert(temp[0])][convert(temp[1])][2] = true;
	}
	for (int i = 0; i < G; i++)
	{
		scanf("%s", temp);
		trans[convert(temp[0])][convert(temp[1])][3] = true;
	}
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		str[i] = convert(str[i]);
		dp[i][i][str[i]] = true;
	}
	for (int i = 1; i < len; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (trans[str[i - 1]][str[i]][k] == true)
			{
				dp[i - 1][i][k] = true;
			}
		}
	}
	for (int l = 3; l <= len; l++)
	{
		for (int i = 0; i <= len - l; i++)
		{
			for (int j = i; j < i + l - 1; j++)
			{
				for (int p = 0; p < 4; p++)
				{
					for (int q = 0; q < 4; q++)
					{
						if (dp[i][j][p] == true && dp[j + 1][i + l - 1][q] == true)
						{
							for (int k = 0; k < 4; k++)
							{
								if (trans[p][q][k] == true)
								{
									dp[i][i + l - 1][k] = true;
								}
							}
						}
					}
				}
			}
		}
	}
	bool has = false;
	if (dp[0][len - 1][0] == true) printf("W"), has = true;
	if (dp[0][len - 1][1] == true) printf("I"), has = true;
	if (dp[0][len - 1][2] == true) printf("N"), has = true;
	if (dp[0][len - 1][3] == true) printf("G"), has = true;
	if (has == false) printf("The name is wrong!");
	printf("\n");
	return 0;
}
