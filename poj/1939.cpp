// Problem Name: Diplomatic License
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
		printf("%d", n);
		for (int i = 0; i < n - 1; i++)
		{
			printf(" %.6f %.6f", (double)(V[i].x + V[i + 1].x) / 2, (double)(V[i].y + V[i + 1].y) / 2);
		}
		printf(" %.6f %.6f\n", (double)(V[n - 1].x + V[0].x) / 2, (double)(V[n - 1].y + V[0].y) / 2);
	}
	return 0;
}
