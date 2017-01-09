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
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double solve(int l, int r)
{//printf("solve : l = %d, r = %d.\n", l, r);
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
		}//printf("b = %d, e = %d.\n", b, e);
		e = mid + 1;
		while (e <= r && d[e].x - d[mid + 1].x < dis)
		{
			a[e] = d[e];
			e++;
		}
		sort(a + b + 1, a + e, _point_y_cmp_);
		for (int i = b + 1; i < e; i++)
		{
			for (int k = 1; k < 6 && i + k < e; k++)
			{//printf("update min : i = %d, k = %d : dist(%d, %d) = %.2f.\n", i, k, i, i + k, dist(a[i], a[i + k]));
				ans = min(ans, dist(a[i], a[i + k]));
			}
		}
		ans = min(ans, dis);
		/*int mid = (l + r) >> 1;
		double dis = min(solve(l, mid), solve(mid + 1, r));
		for (int i = l; i <= mid; i++)
		{
			for (int k = mid + 1; k <= mid + 5 && k <= r; k++)
			{
				ans = min(ans, dist(d[i], d[k]));
			}
		}
		ans = min(ans, dis);*/
	}
	return ans;
}

int main()
{
	while (scanf("%d", &n))
	{
		if (n == 0) break;
		for (int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &d[i].x, &d[i].y);
		}
		sort(d, d + n, _point_x_cmp_);
		printf("%.2f\n", sqrt(solve(0, n - 1)) / 2.0f);
	}
	return 0;
}
