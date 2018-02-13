// Problem Name: Robot Vacuum Cleaner
// Source: Codeforces Round #461 (Div. 2), Problem D

#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;

using namespace std;

struct str
{
	int s, t;
}d[100010];

int n;
ll ans;
char t[100010];

inline bool _str_cmp_(const str &x, const str &y)
{
	return (ll)x.s * y.t > (ll)x.t * y.s;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", t);
		int len = strlen(t);
		for (int j = 0; j < len; j++)
		{
			if (t[j] == 's')
			{
				d[i].s++;
			}
			else
			{
				d[i].t++;
				ans += d[i].s;
			}
		}
	}
	sort(d, d + n, _str_cmp_);
	ll ts = d[0].s;
	for (int i = 1; i < n; i++)
	{
		ans += ts * d[i].t;
		ts += d[i].s;
	}
	printf("%lld\n", ans);
	return 0;
}
