// Problem Name: 麻将
// Source: [JSOI2007]

#include <cstdio>
#include <cstring>

using namespace std;

int n, m, cnt[410], _cnt[410], ans[410], ac;

bool check(int x)
{
	for (int i = 1; i <= n; i++)
	{
		memcpy(_cnt, cnt, sizeof(cnt));
		_cnt[x]++;
		if (_cnt[i] >= 2) _cnt[i] -= 2;
		else continue;
		for (int j = 1; j <= n + 2; j++)
		{
			if (_cnt[j] < 0) goto NEXT;
			_cnt[j + 1] -= _cnt[j] % 3;
			_cnt[j + 2] -= _cnt[j] % 3;
		}
		return true;
        NEXT:;
	}
	return false;
}

int main()
{
	scanf("%d%d", &n, &m);
	int x;
	for (int i = 3 * m; i >= 0; i--)
	{
		scanf("%d", &x);
		cnt[x]++;
	}
	int has = false;
	for (int i = 1; i <= n; i++)
	{
		if (check(i) == true) ans[ac++] = i, has = true;
	}
	if (has == false) printf("NO");
	else
	{
		printf("%d", ans[0]);
		for (int i = 1; i < ac; i++)
		{
			printf(" %d", ans[i]);
		}
	}
	return 0;
}
