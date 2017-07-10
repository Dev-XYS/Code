#include <cstdio>
#include <cstring>

using namespace std;

int k, len, cnt[1000010], cc, minc;
char s[1000010];

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

void pre()
{
	len = strlen(s);
	int l = 0;
	for (int i = 0; i <= len; i++)
	{
		l++;
		if (s[i] == ' ' || s[i] == '-')
		{
			check_max(minc, l);
			cnt[cc++] = l;
			l = 0;
		}
		else if (s[i] == 0)
		{
			check_max(minc, l - 1);
			cnt[cc++] = l - 1;
		}
	}
}

bool check(int w)
{
	int line = 0, lc = 1;
	for (int i = 0; i < cc; i++)
	{
		if (line + cnt[i] <= w)
		{
			line += cnt[i];
		}
		else
		{
			line = cnt[i];
			lc++;
		}
	}
	return lc <= k;
}

int solve()
{
	int l = minc, r = len;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid) == true)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	return l;
}

int main()
{
	scanf("%d", &k);
	gets(s);
	gets(s);
	pre();
	printf("%d\n", solve());
	return 0;
}
