#include <cstdio>
#include <cstring>

using namespace std;

char s[10010], t[1000010];
int pi[10010];

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

int KMP()
{
	calc_pi();
	int l = strlen(t), sl = strlen(s), p = 0, res = 0;
	for (int i = 0; i < l; i++)
	{
		while (p > 0 && t[i] != s[p])
		{
			p = pi[p - 1];
		}
		if (t[i] == s[p])
		{
			p++;
		}
		if (p == sl)
		{
			res++;
			p = pi[p - 1];
		}
	}
	return res;
}

int main()
{
	int casen;
	scanf("%d", &casen);
	while (casen--)
	{
		scanf("%s%s", s, t);
		printf("%d\n", KMP());
	}
	return 0;
}
