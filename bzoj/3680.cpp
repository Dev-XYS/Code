// Problem Name: 吊打XXX
// Problem Author: wangxz

#include <cstdio>
#include <cmath>

using namespace std;

struct point
{
	double x, y;
	point(double _x = 0, double _y = 0) : x(_x), y(_y) { }
}d[10010];

struct vector
{
	double x, y;
	vector(double _x = 0, double _y = 0) : x(_x), y(_y) { }
	double length() { return sqrt(x * x + y * y); }
};

int n, g[10010];

inline double sqr(double x)
{
	return x * x;
}

inline double sqr_dist(point a, point b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

inline double dist(point a, point b)
{
	return sqrt(sqr_dist(a, b));
}

vector get_direction(point center)
{
	double dx = 0, dy = 0;
	for (int i = 0; i < n; i++)
	{
		double dis = dist(center, d[i]);
		if (dis == 0) continue;
		dx += (center.x - d[i].x) / dis * g[i];
		dy += (center.y - d[i].y) / dis * g[i];
	}
	return vector(dx, dy);
}

int main()
{
	scanf("%d", &n);
	double sx = 0, sy = 0, sg = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%lf%lf%d", &d[i].x, &d[i].y, &g[i]);
		sx += d[i].x * g[i];
		sy += d[i].y * g[i];
		sg += g[i];
	}
	point center = point(sx / sg, sy / sg);
	vector dir;
	double step = 100000;
	do
	{
		dir = get_direction(center);
		center.x -= dir.x / sg * step;
		center.y -= dir.y / sg * step;
		step *= 0.95;
	} while (step >= 1e-4);
	printf("%.3lf %.3lf\n", center.x, center.y);
	return 0;
}
