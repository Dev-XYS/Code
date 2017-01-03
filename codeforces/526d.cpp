#include <cstdio>
#include <cstring>

using namespace std;

char s[1000010];
int l, k, pi[1000010];

void calc_pi()
{
	int p = 0;
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
	scanf("%d%d", &l, &k);
	scanf("%s", s);
	calc_pi();
	for (int i = 0; i < l; i++)
	{
		int R = (i + 1) / (i + 1 - pi[i]);
		if ((i + 1) % (i + 1 - pi[i]) == 0)
		{
			if (R / k >= R % k)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		else
		{
			if (R / k > R % k)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
	}
	return 0;
}
