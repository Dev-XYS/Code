#include <cstdio>

#define INF 1e9

using namespace std;

struct status
{
	char s[3][3];
	char* operator [] (const int &x) { return s[x]; }
};

inline char other(char x)
{
	return x == 'F' ? 'G' : 'F';
}

int count_non_white(status stat)
{
	int res = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (stat[i][j] != '.') res++;
		}
	}
	return res;
}

int count(status stat, char x)
{
	int res = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (stat[i][j] != x) goto NEXT_ROW;
		}
		res++;
	NEXT_ROW:;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (stat[j][i] != x) goto NEXT_COLUMN;
		}
		res++;
	NEXT_COLUMN:;
	}
	for (int i = 0; i < 3; i++)
	{
		if (stat[i][i] != x) goto NEXT;
	}
	res++;
NEXT:
	for (int i = 0; i < 3; i++)
	{
		if (stat[i][2 - i] != x) goto END;
	}
	res++;
END:;
	return res;
}

int dfs(status stat, int cnt, char cur)
{
	if (cnt == 9) return count(stat, 'F') - count(stat, 'G');
	int best = (cur == 'F' ? -INF : INF);
	status next;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (stat[i][j] == '.')
			{
				next = stat;
				next[i][j] = cur;
				int d = dfs(next, cnt + 1, other(cur));
				if (cur == 'F')
				{
					if (d > best) best = d;
				}
				else
				{
					if (d < best) best = d;
				}
			}
		}
	}
	return best;
}

int main()
{
	int T;
	scanf("%d", &T);
	status init;
	while (T--)
	{
		for (int i = 0; i < 3; i++)
		{
			scanf("%s", init[i]);
		}
		printf("%d\n", dfs(init, count_non_white(init), 'F'));
	}
	return 0;
}
