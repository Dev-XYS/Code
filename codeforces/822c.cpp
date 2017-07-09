#include <cstdio>
#include <algorithm>
#include <set>

#define INF 2000000001

using namespace std;

struct interval
{
	int l, r, cost;
	int duration() { return r - l + 1; }
}dl[200010], dr[200010];

int n, x;
multiset<int> S[200010];

inline void check_min(int &x, int y)
{
	if (y < x) x = y;
}

inline bool _interval_l_cmp_(const interval &x, const interval &y)
{
	return x.l < y.l;
}

inline bool _interval_r_cmp_(const interval &x, const interval &y)
{
	return x.r < y.r;
}

int main()
{
	scanf("%d%d", &n, &x);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &dl[i].l, &dl[i].r, &dl[i].cost);
		dr[i] = dl[i];
	}
	sort(dl, dl + n, _interval_l_cmp_);
	sort(dr, dr + n, _interval_r_cmp_);
	for (int i = 0; i < n; i++)
	{
		S[dl[i].duration()].insert(dl[i].cost);
	}
	int ans = INF;
	int first = 0;
	for (int i = 0; i < n; i++)
	{
		while (first < n && dl[first].l <= dr[i].r)
		{
			int d = dl[first].duration();
			S[d].erase(S[d].lower_bound(dl[first].cost));
			first++;
		}
		if (first >= n)
		{
			break;
		}
		int d = x - dr[i].duration();
		if (d > 0 && S[d].size() > 0)
		{
			check_min(ans, dr[i].cost + *S[d].begin());
		}
	}
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}
