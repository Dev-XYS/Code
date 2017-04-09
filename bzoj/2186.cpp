// Problem Name: 沙拉公主的困惑
// Source: [SDOI2008]

#include <cstdio>

typedef long long ll;

using namespace std;

int T, R, n[10010], m[10010], maxn, fact[10000010], prime[1000010], pc, div[10000010], s[1000010];

ll qpow(ll x, int y)
{
	if (y == 0) return 1;
	if (y == 1) return x;
	ll h = qpow(x, y >> 1);
	h = h * h % (ll)R;
	if ((y & 1) == 0) return h;
	else return h * x % (ll)R;
}

inline int mul_inv(int x)
{
	return (int)qpow(x, R - 2);
}

void sieve()
{
	fact[0] = 1;
	for (int i = 1; i <= maxn; i++)
	{
		fact[i] = (ll)fact[i - 1] * (ll)i % (ll)R;
	}
	for (int i = 2; i <= maxn; i++)
	{
		if (div[i] == 0) prime[++pc] = i, div[i] = i;
		for (int j = 1; j <= pc && (ll)i * (ll)prime[j] <= maxn; j++)
		{
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j]) break;
		}
	}
	for (int i = 1; i <= pc; i++)
	{
		s[i] = ((ll)s[i - 1] - (ll)(s[i - 1] + 1) * (ll)mul_inv(prime[i])) % (ll)R;
	}
}

int binary_search(int x)
{
	int l = 0, r = pc;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (x >= prime[mid]) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main()
{
	scanf("%d%d", &T, &R);
	for (int i = 0; i < T; i++)
	{
		scanf("%d%d", &n[i], &m[i]);
		if (n[i] > maxn) maxn = n[i];
	}
	sieve();
	for (int i = 0; i < T; i++)
	{
		printf("%d\n", (int)(((ll)(s[binary_search(m[i])] + 1) * (ll)fact[n[i]] % (ll)R + (ll)R) % (ll)R));
	}
	return 0;
}
