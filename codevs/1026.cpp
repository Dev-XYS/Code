#include <cstdio>
#include <cstring>

using namespace std;

int r, c, n;
char map[50][55], op[10];
bool pos[50][50], last[50][50];

int main()
{
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++)
	{
		scanf("%s", map[i]);
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (map[i][j] == '*')
			{
				pos[i][j] = true;
				map[i][j] = '.';
				goto FOUND;
			}
		}
	}
FOUND:
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", op);
		memcpy(last, pos, sizeof(pos));
		memset(pos, false, sizeof(pos));
		if (op[0] == 'N')
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (last[i][j] == true)
					{
						for (int k = i - 1; k >= 0 && map[k][j] != 'X'; k--)
						{
							pos[k][j] = true;
						}
					}
				}
			}
		}
		else if (op[0] == 'S')
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (last[i][j] == true)
					{
						for (int k = i + 1; k < r && map[k][j] != 'X'; k++)
						{
							pos[k][j] = true;
						}
					}
				}
			}
		}
		else if (op[0] == 'W')
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (last[i][j] == true)
					{
						for (int k = j - 1; k >= 0 && map[i][k] != 'X'; k--)
						{
							pos[i][k] = true;
						}
					}
				}
			}
		}
		else if (op[0] == 'E')
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (last[i][j] == true)
					{
						for (int k = j + 1; k < c && map[i][k] != 'X'; k++)
						{
							pos[i][k] = true;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (pos[i][j] == true)
			{
				printf("*");
			}
			else
			{
				printf("%c", map[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}
