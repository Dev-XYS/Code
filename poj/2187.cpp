#include <cstdio>
#include <algorithm>

using namespace std;

struct point
{
	int x, y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) { }
}p[50010];

struct segment
{
	point s, t;
	segment(point _s = point(), point _t = point()) : s(_s), t(_t) { }
}s[50010];

int n, S[50010], sp = 0;

int cross(const segment &a, const segment &b)
{
	return (a.s.x - a.t.x) * (b.s.y - b.t.y) - (a.s.y - a.t.y) * (b.s.x - b.t.x);
}

int sqrdist(const point &a, const point &b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool _segment_cmp_(const segment &a, const segment &b)
{
	int cr = cross(a, b);
	if (cr != 0) return cr > 0;
	return sqrdist(a.s, a.t) < sqrdist(b.s, b.t);
}

void Graham()
{
	int corner = 0;
	for (int i = 0; i < n; i++)
	{
		if (p[i].x < p[corner].x)
		{
			corner = i;
		}
		else if (p[i].x == p[corner].x && p[i].y < p[corner].y)
		{
			corner = i;
		}
	}
	for (int i = 0; i < n; i++)
	{
		s[i] = segment(p[corner], p[i]);
	}
	sort(s, s + n, _segment_cmp_);
	for (int i = 0; i < n; i++)
	{
		while (sp > 1 && cross(segment(s[S[sp - 2]].t, s[S[sp - 1]].t), segment(s[S[sp - 1]].t, s[i].t)) <= 0)
		{
			sp--;
		}
		S[sp++] = i;
	}
	S[sp++] = 0;
}

int solve()
{
	int k = 1, ans = 0;
	for (int i = 1; i < sp; i++)
	{
		while (cross(segment(s[S[k + 1]].t, s[S[i - 1]].t), segment(s[S[k + 1]].t, s[S[i]].t)) >= cross(segment(s[S[k]].t, s[S[i - 1]].t), segment(s[S[k]].t, s[S[i]].t)))
		{
			ans = max(ans, max(sqrdist(s[S[k]].t, s[S[i - 1]].t), sqrdist(s[S[k]].t, s[S[i]].t)));
			k = (k + 1) % (sp - 1);
		}
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	Graham();
	if (sp == 3)
	{
		printf("%d", sqrdist(s[S[0]].t, s[S[1]].t));
	}
	else
	{
		printf("%d", solve());
	}
	return 0;
}
