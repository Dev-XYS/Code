// Problem Name: CGCDSSQ
// Source: Bayan 2015 Contest Warm Up, Problem D

#include <cstdio>
#include <map>

typedef long long ll;

using namespace std;

int n, q, st[100010][18], log[100010];
map<int, ll> M;

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void init_st()
{
	for (int k = 1; (1 << k) <= n; k++)
	{
		for (int i = 0; i + (1 << k) <= n + 1; i++)
		{
			st[i][k] = gcd(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
		}
	}
}

inline int log2(int x)
{
	int res = -1;
	while (x > 0)
	{
		res++;
		x >>= 1;
	}
	return res;
}

void init_log()
{
	for (int i = 0; i < n; i++)
	{
		log[i] = log2(i);
	}
}

inline int get_gcd(int l, int r)
{
	int k = log[r - l + 1];
	return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

int binary_search(int start, int l, int r, int x)
{
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (get_gcd(start, mid) >= x) l = mid + 1;
		else r = mid;
	}
	return l;
}

void solve()
{
	init_st();
	init_log();
	for (int i = 0; i < n; i++)
	{
		int s = i;
		while (s < n)
		{
			int g = get_gcd(i, s);
			int p = binary_search(i, s, n, g);
			M[g] += p - s;
			s = p;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &st[i][0]);
	}
	solve();
	scanf("%d", &q);
	int x;
	while (q--)
	{
		scanf("%d", &x);
		printf("%I64d\n", M[x]);
	}
	return 0;
}
