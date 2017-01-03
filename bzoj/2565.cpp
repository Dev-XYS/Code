#include <cstdio>
#include <cstring>

using namespace std;

char t[1000010], s[2000010];
int l, mx, p, r[2000010], right[2000010];

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
	scanf("%s", s);
	int len = strlen(s);
	t[0] = '!';
	t[1] = '#';
	l = 2;
	for (int i = 0; i < len; i++)
	{
		t[l++] = s[i];
		t[l++] = '#';
	}
	t[l] = '?';
	manacher();
	for (int i = 1; i < l; i++)
	{
		for (int j = i + r[i] - 1; j >= i; j--)
		{
			if (right[j] == 0)
			{
				right[j] = j - i + 1;
			}
			else
			{
				break;
			}
		}
	}//for (int i = 1; i < l; i++) printf("%d ", right[i]);printf("\n");
	int ans = 0;
	for (int i = 1; i < l; i++)
	{
		if (r[i] + right[i - r[i] + 1] > ans)
		{
			ans = r[i] + right[i - r[i] + 1];
		}
	}
	printf("%d", ans - 2);
	return 0;
}
