#include <cstdio>
#include <cstring>

using namespace std;

int r, q, k, n;
char s[210], t[30], d[10][210];
int l, dp[210][50];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int count(int a, int b)
{
	int res = 0;
	for (int i = a; i <= b; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int len = strlen(d[j]);
			for (int p = i; p < i + len; p++)
			{
				if (p > b)
				{
					goto END;
				}
				if (d[j][p - i] != s[p])
				{
					goto END;
				}
			}
			res++;
			break;
		END:;
		}
	}
	return res;
}

int main()
{
	scanf("%d", &r);
	while (r--)
	{
		memset(dp, 0, sizeof(dp));
		s[0] = 0;
		scanf("%d%d", &q, &k);
		while (q--)
		{
			scanf("%s", t);
			strcat(s, t);
		}
		l = strlen(s);
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%s", d[i]);
		}
		for (int i = 0; i < l; i++)
		{
			dp[i][1] = count(0, i);
		}
		for (int i = 1; i < l; i++)
		{
			for (int j = 2; j <= k; j++)
			{
				for (int p = j - 1; p <= i; p++)
				{
					dp[i][j] = max(dp[i][j], dp[p - 1][j - 1] + count(p, i));
				}
			}
		}
		printf("%d\n", dp[l - 1][k]);
	}
	return 0;
}
