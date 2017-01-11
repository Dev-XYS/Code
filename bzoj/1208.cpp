#include <cstdio>
#include <set>

#define INF 100000000000000000000LL

typedef long long ll;

using namespace std;

int n, which;
set<ll> s;

int main()
{
	int op;
	ll x, min, ans = 0;
	set<ll>::iterator it, get;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%lld", &op, &x);
		if (which == op)
		{
			s.insert(x);
		}
		else if (s.empty())
		{
			which = op;
			s.insert(x);
		}
		else
		{
			min = INF;
			it = s.lower_bound(x);
			if (it != s.end())
			{
				if (*it - x < min)
				{
					min = *it - x;
					get = it;
				}
			}
			if (it != s.begin())
			{
				it--;
				if (x - *it <= min)
				{
					min = x - *it;
					get = it;
				}
			}
			ans += min;
			s.erase(get);
		}
	}
	printf("%lld", ans % 1000000LL);
	return 0;
}
