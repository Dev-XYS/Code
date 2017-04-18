// Problem Name: Minimal string
// Source: Educational Codeforces Round 19, Problem C

#include <cstdio>
#include <cstring>

using namespace std;

char s[100010], t[100010], u[100010];
int cnt[256], tp, up;

int main()
{
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		cnt[s[i]]++;
	}
	char cur = 'a';
	for (int i = 0; i < len; i++)
	{
		while (cnt[cur] == 0) cur++;
		while (tp > 0 && t[tp - 1] <= cur) u[up++] = t[--tp];
		if (s[i] == cur) u[up++] = s[i];
		else t[tp++] = s[i];
		cnt[s[i]]--;
	}
	for (int i = tp - 1; i >= 0; i--)
	{
		u[up++] = t[i];
	}
	printf("%s\n", u);
	return 0;
}
