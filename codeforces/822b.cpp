#include <cstdio>
#include <cstring>

#define INF 1000000000

using namespace std;

int ls, lt, ans = INF, apos[1010], pos[1010];
char s[1010], t[1010];

int main()
{
	scanf("%d%d%s%s", &ls, &lt, s, t);
	for (int i = 0; i + ls <= lt; i++)
	{
		int cnt = 0;
		for (int j = 0; j < ls; j++)
		{
			if (s[j] != t[i + j])
			{
				pos[cnt++] = j;
			}
		}
		if (cnt < ans)
		{
			ans = cnt;
			memcpy(apos, pos, sizeof(pos));
		}
	}
	printf("%d\n", ans);
	for (int i = 0; i < ans; i++)
	{
		printf("%d ", apos[i] + 1);
	}
	return 0;
}
