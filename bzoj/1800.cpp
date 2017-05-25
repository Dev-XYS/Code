// Problem name: 飞行棋 fly
// Source: [AHOI2009]

#include <cstdio>

using namespace std;

int n, s[50];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &s[i]);
		s[i + n] = s[i];
	}
	for (int i = 1; i <= n * 2; i++)
	{
		s[i] += s[i - 1];
	}
	int ans = 0;
	for (int a = 1; a <= n; a++)
	{
		for (int b = a + 1; b <= n * 2; b++)
		{
			for (int c = b + 1; c <= n * 2; c++)
			{
				for (int d = c + 1; d < a + n; d++)
				{
					if (s[b] - s[a] == s[d] - s[c] && ((s[c] - s[b]) << 1) == (s[n] - ((s[b] - s[a]) << 1))) ans++;
				}
			}
		}
	}
	printf("%d\n", ans >> 2);
	return 0;
}
