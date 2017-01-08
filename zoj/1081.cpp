#include <cstdio>

typedef long long ll;

using namespace std;

struct point
{
	ll x, y;
	point() { }
	point(ll _x, ll _y) : x(_x), y(_y) { }
}d[110];

struct segment
{
	point s, t;
	segment() { }
	segment(point _s, point _t) : s(_s), t(_t) { }
}s[110];

ll abs(ll a)
{
	return a < 0 ? -a : a;
}

ll cross(segment a, segment b)
{
	return (a.s.x - a.t.x) * (b.s.y - b.t.y) - (a.s.y - a.t.y) * (b.s.x - b.t.x);
}

bool intersect(segment a, segment b)
{
	return cross(a, segment(a.s, b.s)) * cross(a, segment(a.s, b.t)) <= 0LL && cross(b, segment(b.s, a.s)) * cross(b, segment(b.s, a.t)) <= 0LL;
}

bool onsegment(segment a, point b)
{
	return abs(b.x - a.s.x) + abs(b.x - a.t.x) == abs(a.s.x - a.t.x) && (a.s.x - b.x) * (a.t.y - b.y) == (a.s.y - b.y) * (a.t.x - b.x);
}

int main()
{//if (intersect(segment(point(3, 1), point(4, 4)), segment(point(2, 2), point(10, 2))) == true) printf("true\n"); else printf("false\n");
	int n, m, casen = 0;
	point e;
	while (scanf("%d%d", &n, &m) == 2)
	{
		if (casen != 0)
		{
			printf("\n");
		}
		printf("Problem %d:\n", ++casen);
		for (int i = 0; i < n; i++)
		{
			scanf("%lld%lld", &d[i].x, &d[i].y);
		}
		for (int i = 0; i < n; i++)
		{
			if (d[i].y > d[(i + 1) % n].y)
			{
				s[i] = segment(d[i], d[(i + 1) % n]);
			}
			else
			{
				s[i] = segment(d[(i + 1) % n], d[i]);
			}
		}
		while (m--)
		{
			int cnt = 0;
			scanf("%lld%lld", &e.x, &e.y);
			for (int i = 0; i < n; i++)
			{
				if (onsegment(s[i], e) == true)
				{
					printf("Within\n");
					goto END;
				}
			}
			for (int i = 0; i < n; i++)
			{
				if (s[i].s.y != s[i].t.y)
				{
					if (e.y == s[i].s.y && e.x <= s[i].s.x)
					{
						cnt++;
					}
					else if (e.y != s[i].t.y)
					{
						if (intersect(segment(e, point(100000000LL, e.y)), s[i]) == true)
						{//printf("intersect\n");
							cnt++;
						}
					}
				}
			}
			if (cnt % 2 == 0)
			{
				printf("Outside\n");
			}
			else
			{
				printf("Within\n");
			}
		END:;
		}
	}
	return 0;
}
