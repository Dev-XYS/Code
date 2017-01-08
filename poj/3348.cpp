#include <cstdio>
#include <algorithm>

using namespace std;

struct point
{
	int x, y;
	point() { }
	point(int _x, int _y) : x(_x), y(_y) { }
}d[10010];

struct segment
{
	point s, t;
	segment() { }
	segment(point _s, point _t) : s(_s), t(_t) { }
};

int n, S[10010], sp = 0;
point corner;

int cross(segment a, segment b)
{
	return (a.s.x - a.t.x) * (b.s.y - b.t.y) - (a.s.y - a.t.y) * (b.s.x - b.t.x);
}

int dist(point a, point b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool _point_cmp(point a, point b)
{
	int cr = cross(segment(corner, a), segment(corner, b));
	if (cr == 0)
	{
		return dist(corner, a) < dist(corner, b);
	}
	return cr > 0;
}

void Graham()
{
	int mo = 0;
	for (int i = 1; i < n; i++)
	{
		if (d[i].x < d[mo].x)
		{
			mo = i;
		}
		else if (d[i].x == d[mo].x && d[i].y < d[mo].y)
		{
			mo = i;
		}
	}
	corner = d[mo];
	sort(d, d + n, _point_cmp);
	d[n] = d[0];
	S[sp++] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (sp >= 2 && cross(segment(d[S[sp - 2]], d[S[sp - 1]]), segment(d[S[sp - 1]], d[i])) < 0)
		{
			sp--;
		}
		S[sp++] = i;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &d[i].x, &d[i].y);
	}
	Graham();
	int res = 0;
	for (int i = 1; i < sp; i++)
	{
		res += cross(segment(point(0, 0), d[S[i - 1]]), segment(point(0, 0), d[S[i]]));
	}
	if (res < 0) res = -res;
	res /= 100;
	printf("%d", res);
	return 0;
}
