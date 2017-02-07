#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct string
{
	char str[110];
}ord[10000];

int n;
char s[10000][110], pre[100];

bool _string_cmp_(const string &x, const string &y)
{
	return strcmp(x.str, y.str) < 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s[i]);
	}
	int len = 0;
	for (int i = 0; ; i++)
	{
		if (s[0][i] >= '0' && s[0][i] <= '9')
		{
			len = i;
			break;
		}
		else
		{
			pre[i] = s[0][i];
		}
	}
	for (int i = 0; i < n; i++)
	{
		int k = len;
		while (s[i][k] != '.') k++;
		for (int j = k - 1; j >= len; j--)
		{
			ord[i].str[j - k + 100] = s[i][j];
		}
		for (int j = len - 1; j - k + 100 >= 0; j--)
		{
			ord[i].str[j - k + 100] = '0';
		}
	}
	sort(ord, ord + n, _string_cmp_);
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		while (ord[i].str[k] == '0') k++;
		printf("%s%s.in\n", pre, ord[i].str + k);
	}
	return 0;
}
