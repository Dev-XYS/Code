#include <cstdio>
#include <set>

#define INF 2147483647

using namespace std;

set<int> s;

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

int main()
{
	int n, x, ans = 0, min;
	set<int>::iterator it;
	scanf("%d", &n);
	scanf("%d", &x);
	s.insert(x);
	ans += x;
	while (--n)
	{
		scanf("%d", &x);
		it = s.lower_bound(x);
		min = INF;
		if (it != s.end())
		{
			if (abs(*it - x) < min)
			{
				min = abs(*it - x);
			}
		}
		if (it != s.begin())
		{
			it--;
			if (abs(*it - x) < min)
			{
				min = abs(*it - x);
			}
		}
		ans += min;
		s.insert(x);
	}
	printf("%d", ans);
	return 0;
}
