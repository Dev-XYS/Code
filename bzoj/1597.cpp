// Problem Name: 土地购买
// Source: USACO 2008 Mar (Gold)

#include <cstdio>
#include <algorithm>

typedef long long ll;

using namespace std;

struct item
{
	int a, b;
}d[200010];

int n, sp = 1, Q[200010], hp = 0, tp = 0;
item S[200010];
ll dp[200010];

inline bool _item_cmp_(const item &x, const item &y)
{
	if (x.a == y.a) return x.b < y.b;
	return x.a < y.a;
}

inline double get_k(int i, int j)
{
	return (double)(dp[i] - dp[j]) / (double)(S[i + 1].b - S[j + 1].b);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &d[i].a, &d[i].b);
	}
	sort(d, d + n, _item_cmp_);
	for (int i = 0; i < n; i++)
	{
		while (sp > 1 && S[sp - 1].b <= d[i].b) sp--;
		S[sp++] = d[i];
	}
	tp++;
	for (int i = 1; i < sp; i++)
	{
		while (tp - hp >= 2 && get_k(Q[hp], Q[hp + 1]) >= -S[i].a) hp++;
		dp[i] = dp[Q[hp]] + (ll)S[i].a * (ll)S[Q[hp] + 1].b;
		while (tp - hp >= 2 && get_k(Q[tp - 2], Q[tp - 1]) <= get_k(Q[tp - 1], i)) tp--;
		Q[tp++] = i;
	}
	printf("%lld", dp[sp - 1]);
	return 0;
}
