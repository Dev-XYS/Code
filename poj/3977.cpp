#include <cstdio>
#include <map>

typedef long long ll;

using namespace std;

int n;
ll d[50];
map<ll, int> M;

inline ll abs(ll x)
{
	return x < 0 ? -x : x;
}

int main()
{
	while (scanf("%d", &n))
	{
		if (n == 0) break;
		ll minsum = 10000000000000000LL;
		int mincnt = 50;
		M.clear();
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &d[i]);
		}
		for (int i = (1 << (n / 2)) - 1; i > 0; i--)
		{
			int x = i, k = 0, c = 0;
			ll sum = 0LL;
			while (x > 0)
			{
				if ((x & 1) == 1)
				{
					sum += d[k];
					c++;
				}
				k++;
				x >>= 1;
			}
			if (M[sum] == 0) M[sum] = c;
			else if (c < M[sum]) M[sum] = c;
			if (abs(sum) < minsum)
			{
				minsum = abs(sum);
				mincnt = c;
			}
			else if (abs(sum) == minsum)
			{
				if (c < mincnt)
				{
					mincnt = c;
				}
			}
		}
		if (M[0] == 0) M[0] = 0;
		for (int i = (1 << (n - (n / 2))) - 1; i >= 0; i--)
		{
			int x = i, k = n / 2, c = 0;
			ll sum = 0LL;
			while (x > 0)
			{
				if ((x & 1) == 1)
				{
					sum += d[k];
					c++;
				}
				k++;
				x >>= 1;
			}
			map<ll, int>::iterator it = M.lower_bound(-sum);
			if (it == M.end())
			{
				goto UPPER_BOUND;
			}
			if (it->second + c == 0)
			{
				goto UPPER_BOUND;
			}
			if (abs(it->first + sum) < minsum)
			{
				minsum = abs(it->first + sum);
				mincnt = it->second + c;
			}
			else if (abs(it->first + sum) == minsum)
			{
				if (it->second + c < mincnt)
				{
					mincnt = it->second + c;
				}
			}
		UPPER_BOUND:
			it--;
			if (it->second + c == 0)
			{
				goto END;
			}
			if (abs(it->first + sum) < minsum)
			{
				minsum = abs(it->first + sum);
				mincnt = it->second + c;
			}
			else if (abs(it->first + sum) == minsum)
			{
				if (it->second + c < mincnt)
				{
					mincnt = it->second + c;
				}
			}
		END:;
		}
		printf("%lld %d\n", minsum, mincnt);
	}
	return 0;
}
