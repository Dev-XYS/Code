#include <cstdio>
#include <cmath>
#include <algorithm>

#define fINF 10e9
#define ELEMENT_COUNT 100010

using namespace std;

struct point
{
	double x, y;
}d[ELEMENT_COUNT];

int n;

bool _point_x_cmp_(point a, point b)
{
	if (a.x != b.x) return a.x < b.x;
	return a.y > b.y;
}

bool _point_y_cmp_(point a, point b)
{
	return a.y > b.y;
}

double min(double a, double b)
{
	return a < b ? a : b;
}

double dist(point &a, point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double solve(int l, int r)
{
	double ans = fINF;
	static point a[ELEMENT_COUNT];
	if (l < r)
	{
		int mid = (l + r) >> 1;
		double dis = min(solve(l, mid), solve(mid + 1, r));
		int b = mid, e = mid + 1;
		while (b >= l && d[mid].x - d[b].x < dis)
		{
			a[b] = d[b];
			b--;
		}
		e = mid + 1;
		while (e <= r && d[e].x - d[mid + 1].x < dis)
		{
			a[e] = d[e];
			e++;
		}
		sort(a + b + 1, a + e, _point_y_cmp_);
		for (int i = b + 1; i < e; i++)
		{
			for (int j = i + 1; j <= i + 5 && j < e; j++)
			{
				for (int k = j + 1; k <= i + 5 && k < e; k++)
				{
					ans = min(ans, dist(a[i], a[j]) + dist(a[j], a[k]) + dist(a[k], a[i]));
				}
			}
		}
		ans = min(ans, dis);
	}
	return ans;
}

int main()
{
	while (scanf("%d", &n) > 0)
	{
		if (n == 0) break;
		for (int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &d[i].x, &d[i].y);
		}
		sort(d, d + n, _point_x_cmp_);
		printf("%.6f\n", solve(0, n - 1));
	}
	return 0;
}
