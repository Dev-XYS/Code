// Problem Name: ricehub
// Source: [IOI2011]

#include <cstdio>

typedef long long ll;

using namespace std;

int n, L, x[100010];
ll B;

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline void check_min(ll &x, ll y)
{
	if (y < x) x = y;
}

ll cost(int len)
{
	ll res = 0, c = 0;
	for (int i = 0; i < len; i++)
	{
		c += abs(x[len >> 1] - x[i]);
	}
	res = c;
	for (int i = 1; i + len <= n; i++)
	{
		c -= x[i - 1 + (len >> 1)] - x[i - 1];
		c += x[i + len - 1] - x[i + (len >> 1)];
		c += (ll)(x[i + (len >> 1)] - x[i - 1 + (len >> 1)]) * ((len >> 1) - ((len - 1) >> 1));
		check_min(res, c);
	}
	return res;
}

int main()
{
	scanf("%d%d%lld", &n, &L, &B);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	int l = 1, r = n;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (cost(mid) <= B) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
