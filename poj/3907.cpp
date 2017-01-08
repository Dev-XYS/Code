#include <cstdio>

using namespace std;

struct point
{
	double x, y;
	point() { }
	point(double _x, double _y) : x(_x), y(_y) { }
}d[1000];

struct segment
{
	point s, t;
	segment() { }
	segment(point _s, point _t) : s(_s), t(_t) { }
};

double cross(segment a, segment b)
{
	return (a.s.x - a.t.x) * (b.s.y - b.t.y) - (a.s.y - a.t.y) * (b.s.x - b.t.x);
}

int main()
{	
	int n;
	while (true)
	{
		scanf("%d", &n);
		if (n == 0)
		{
			break;
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &d[i].x, &d[i].y);
		}
		double res = 0.0f;
		for (int i = 0; i < n; i++)
		{
			res += cross(segment(point(0.0f, 0.0f), d[i]), segment(point(0.0f, 0.0f), d[(i + 1) % n]));
		}
		if (res < 0.0f) res = -res;
		res /= 2;
		if (res - (double)(int)res <= 0.5f)
		{
			printf("%d\n", (int)res);
		}
		else
		{
			printf("%d\n", (int)res + 1);
		}
	}
	return 0;
}
