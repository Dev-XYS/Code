#include <cstdio>
#include <algorithm>

using namespace std;

struct segment
{
	int a, b;
}s[100];

bool _segment_cmp(segment x, segment y)
{
	return x.a < y.a;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &s[i].a, &s[i].b);
		if (s[i].a > s[i].b)
		{
			int temp = s[i].a;
			s[i].a = s[i].b;
			s[i].b = temp;
		}
	}
	sort(s, s + n, _segment_cmp);
	int right = -1000, cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i].a >= right)
		{
			right = s[i].b;
			cnt++;
		}
		else if (s[i].b < right)
		{
			right = s[i].b;
		}
	}
	printf("%d", cnt);
	return 0;
}
