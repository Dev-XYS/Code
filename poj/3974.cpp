#include <cstdio>
#include <cstring>

using namespace std;

char t[1000010], s[2000010];
int l, mx, p, r[2000010];

int manacher()
{
	int x;
	mx = p = 0;
	for (int i = 1; i < l; i++)
	{
		if (i >= mx)
		{
			x = 1;
		}
		else
		{
			if (i + r[p * 2 - i] > mx)
			{
				x = mx - i;
			}
			else
			{
				x = r[p * 2 - i];
			}
		}
		while (t[i + x] == t[i - x])
		{
			x++;
		}
		r[i] = x;
		if (i + x > mx)
		{
			mx = i + x;
			p = i;
		}
	}
	int res = 0;
	for (int i = 1; i < l; i++)
	{
		if (r[i] > res)
		{
			res = r[i];
		}
	}
	return res;
}

int main()
{
	int casen = 0;
	while (true)
	{
		memset(t, 0, sizeof(t));
		scanf("%s", s);
		if (s[0] == 'E')
		{
			break;
		}
		l = 2;
		t[0] = '!';
		t[1] = '#';
		int len = strlen(s);
		for (int i = 0; i < len; i++)
		{
			t[l++] = s[i];
			t[l++] = '#';
		}
		t[l] = '?';
		printf("Case %d: %d\n", ++casen, manacher() - 1);
	}
	return 0;
}
