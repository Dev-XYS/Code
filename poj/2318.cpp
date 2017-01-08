#include <cstdio>
#include <cstring>

typedef long long ll;

using namespace std;

struct point
{
	ll x, y;
	point() { }
	point(ll _x, ll _y) : x(_x), y(_y) { }
};

struct segment
{
	point s, t;
	segment() { }
	segment(point _s, point _t) : s(_s), t(_t) { }
}d[5010];

int n, m, ans[5010];
ll x1, y1, x2, y2;

ll cross(segment a, segment b)
{
	return (a.s.x - a.t.x) * (b.s.y - b.t.y) - (a.s.y - a.t.y) * (b.s.x - b.t.x);
}

int main()
{
	ll u, l, x, y;
	while (scanf("%d%d%lld%lld%lld%lld", &n, &m, &x1, &y1, &x2, &y2) == 6)
	{
		memset(ans, 0, sizeof(ans));
		d[0] = segment(point(x1, y1), point(x1, y2));
		for (int i = 1; i <= n; i++)
		{
			scanf("%lld%lld", &u, &l);
			d[i] = segment(point(u, y1), point(l, y2));
		}
		while (m--)
		{
			scanf("%lld%lld", &x, &y);
			int _l = 0, _r = n;
			while (_l < _r)
			{
				int mid = (_l + _r + 1) >> 1;
				if (cross(segment(point(x, y), d[mid].s), segment(point(x, y), d[mid].t)) >= 0)
				{
					_l = mid;
				}
				else
				{
					_r = mid - 1;
				}
			}
			ans[_r]++;
		}
		for (int i = 0; i <= n; i++)
		{
			printf("%d: %d\n", i, ans[i]);
		}
		printf("\n");
	}
	return 0;
}
