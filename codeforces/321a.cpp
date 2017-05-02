#include <cstdio>
#include <cstring>

using namespace std;

struct point
{
	int x, y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) { }
}d[110];

int a, b;
char s[110];

int main()
{
	scanf("%d%d%s", &a, &b, s + 1);
	int len = strlen(s + 1);
	d[0] = point(0, 0);
	int x = 0, y = 0;
	for (int i = 1; i <= len; i++)
	{
		if (s[i] == 'U')
		{
			y++;
		}
		else if (s[i] == 'D')
		{
			y--;
		}
		else if (s[i] == 'L')
		{
			x--;
		}
		else
		{
			x++;
		}
		d[i] = point(x, y);
	}
	int _x, _y;
	for (int i = 0; i <= len; i++)
	{
		_x = a - d[i].x, _y = b - d[i].y;
		if (x == 0)
		{
			if (y == 0)
			{
				if (_x == 0 && _y == 0) goto YES;
			}
			else
			{
				if (_x == 0 && _y % y == 0 && _y / y >= 0) goto YES;
			}
		}
		else
		{
			if (y == 0)
			{
				if (_y == 0 && _x % x == 0 && _x / x >= 0) goto YES;
			}
			else
			{
				if (_x % x == 0 && _y % y == 0 && _y / y == _x / x && _x / x >= 0) goto YES;
			}
		}
	}
	goto NO;
YES:
	printf("Yes");
	return 0;
NO:
	printf("No");
	return 0;
}
