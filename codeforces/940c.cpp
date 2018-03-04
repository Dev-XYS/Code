// Problem Name: Phone Numbers
// Source: Codeforces Round #466 (Div. 2), Problem C

#include <cstdio>

using namespace std;

int n, k;
char s[100010], min, max;
bool has[256];

char next(char c)
{
	for (c++; ; c++)
	{
		if (has[c] == true)
		{
			return c;
		}
	}
}

int main()
{
	scanf("%d%d%s", &n, &k, s);
	for (int i = 0; i < n; i++)
	{
		has[s[i]] = true;
	}
	for (char c = 'a'; ; c++)
	{
		if (has[c] == true)
		{
			min = c;
			break;
		}
	}
	for (char c = 'z'; ; c--)
	{
		if (has[c] == true)
		{
			max = c;
			break;
		}
	}
	if (k <= n)
	{
		s[k] = 0;
		while (s[--k] == max)
		{
			s[k] = min;
		}
		s[k] = next(s[k]);
	}
	else
	{
		for (int i = n; i < k; i++)
		{
			s[i] = min;
		}
	}
	printf("%s\n", s);
	return 0;
}
