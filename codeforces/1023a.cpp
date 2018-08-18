#include <cstdio>

using namespace std;

int n, m;
char s[200010], t[200010];

int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	bool has_wildcard = false;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '*')
		{
			has_wildcard = true;
			break;
		}
	}
	bool match = true;
	if (!has_wildcard)
	{
		if (n != m)
		{
			match = false;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (s[i] != t[i])
				{
					match = false;
					break;
				}
			}
		}
	}
	else
	{
		int i, j;
		for (i = 0; s[i] != '*' && i < m; i++)
		{
			if (s[i] != t[i])
			{
				break;
			}
		}
		if (s[i] != '*')
		{
			match = false;
		}
		for (j = 0; s[n - 1 - j] != '*' && j < m; j++)
		{
			if (s[n - 1 - j] != t[m - 1 - j])
			{
				break;
			}
		}
		if (s[n - 1 - j] != '*')
		{
			match = false;
		}
		if (i + j > m)
		{
			match = false;
		}
	}
	printf("%s\n", match ? "YES" : "NO");
	return 0;
}
