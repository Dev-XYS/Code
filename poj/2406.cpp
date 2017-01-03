#include <cstdio>
#include <cstring>

using namespace std;

char s[1000010];
int pi[1000010];

void calc_pi()
{
	int l = strlen(s), p = 0;
	pi[0] = 0;
	for (int i = 1; i < l; i++)
	{
		while (p > 0 && s[p] != s[i])
		{
			p = pi[p - 1];
		}
		if (s[p] == s[i])
		{
			p++;
		}
		pi[i] = p;
	}
}

int main()
{
	while (true)
	{
		scanf("%s", s);
		if (s[0] == '.')
		{
			return 0;
		}
		calc_pi();
		int len = strlen(s);
		int p = len;
		while (p > 0 && len % (len - pi[p - 1]) != 0)
		{
			p = pi[p - 1];
		}
		printf("%d\n", len / (len - pi[p - 1]));
	}
	return 0;
}
