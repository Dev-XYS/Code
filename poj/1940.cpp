// Problem Name: Polygon Programming with Ease
// Source: Ulm Local 2002

#include <cstdio>
#include <vector>

typedef long long ll;

using namespace std;

struct point
{
	ll x, y;
	point(ll _x = 0, ll _y = 0) : x(_x), y(_y) { }
};

int main()
{
	int n;
	while (scanf("%d", &n) > 0)
	{
		vector<point> V;
		ll x, y;
		for (int i = 0; i < n; i++)
		{
			scanf("%lld%lld", &x, &y);
			V.push_back(point(x, y));
		}
		vector<double> X;
		double sumx = 0;
		for (int i = 0; i < n; i++)
		{
			sumx += V[i].x;
		}
		for (int i = 1; i < n; i += 2)
		{
			sumx -= V[i].x * 2;
		}
		X.push_back(sumx);
		for (int i = 1; i < n; i++)
		{
			X.push_back((double)V[i - 1].x * 2 - X[i - 1]);
		}
		vector<double> Y;
		double sumy = 0;
		for (int i = 0; i < n; i++)
		{
			sumy += V[i].y;
		}
		for (int i = 1; i < n; i += 2)
		{
			sumy -= V[i].y * 2;
		}
		Y.push_back(sumy);
		for (int i = 1; i < n; i++)
		{
			Y.push_back((double)V[i - 1].y * 2 - Y[i - 1]);
		}
		printf("%d", n);
		for (int i = 0; i < n; i++)
		{
			printf(" %.6f %.6f", X[i], Y[i]);
		}
		printf("\n");
	}
	return 0;
}
