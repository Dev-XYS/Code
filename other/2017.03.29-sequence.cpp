#include <cstdio>

typedef long long ll;

using namespace std;

int n, m, sp;
ll x[100010], f[100010], s[100010];

int binary_search(ll v)
{
	int l = 0, r = sp - 1;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (x[mid] < v) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main()
{
	ll temp;
	scanf("%d%d", &n, &m);
	x[sp++] = 0;
	x[sp++] = n;
	for (int i = 1; i <= m; i++)
	{
		scanf("%lld", &temp);
		while (sp > 0 && temp <= x[sp - 1]) sp--;
		x[sp++] = temp;
	}
	f[sp - 1] = 1;
	for (int i = sp - 1; i > 0; i--)
	{
		ll k = x[i];
		while (true)
		{
			int j = binary_search(k);
			if (j == 0) break;
			f[j] += k / x[j] * f[i];
			k %= x[j];
		}
		s[k] += f[i];
	}
	for (int i = n - 1; i >= 0; i--)
	{
		s[i] += s[i + 1];
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%lld ", s[i]);
	}
	return 0;
}
