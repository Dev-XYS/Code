// Problem Name: [CQOI2009] 中位数图

#include <cstdio>

using namespace std;

int n, b, d[100010], left[200010];

int main()
{
	scanf("%d%d", &n, &b);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	int pos;
	for (pos = 0; pos < n; pos++)
	{
		if (d[pos] == b) break;
	}
	int c = 100000;
	for (int i = pos - 1; i >= 0; i--)
	{
		if (d[i] < b) left[--c]++;
		else left[++c]++;
	}
	c = 100000;
	long long ans = 1 + left[100000];
	for (int i = pos + 1; i < n; i++)
	{
		if (d[i] > b) ans += (long long)left[--c];
		else ans += (long long)left[++c];
		if (c == 100000) ans++;
	}
	printf("%lld", ans);
	return 0;
}
