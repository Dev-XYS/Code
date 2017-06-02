// Problem Name: 上升序列
// Source: [HAOI2007]

#include <cstdio>

using namespace std;

int n, a[10010], dp[10010], maxlen, m;

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

void dynamic_programming()
{
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] < a[j])
			{
				check_max(dp[i], dp[j]);
			}
		}
		check_max(maxlen, ++dp[i]);
	}
}

void solve(int len)
{
	if (len > maxlen)
	{
		printf("Impossible\n");
	}
	else
	{
		int ca = -1;
		for (int i = 0; i < n && len > 0; i++)
		{
			if (a[i] > ca && dp[i] >= len)
			{
				if (len > 1)
				{
					printf("%d ", a[i]);
				}
				else
				{
					printf("%d\n", a[i]);
				}
				ca = a[i];
				len--;
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	dynamic_programming();
	scanf("%d", &m);
	int l;
	while (m--)
	{
		scanf("%d", &l);
		solve(l);
	}
	return 0;
}
