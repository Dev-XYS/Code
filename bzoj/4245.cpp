// Problem Name: OR-XOR
// Problem Author: Claris

#include <cstdio>

typedef long long ll;

using namespace std;

int n, m;
ll d[500010], s[500010];
bool cannot[500010];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &d[i]);
	}
	ll ans = 0;
	for (int k = 62; k >= 0; k--)
	{
		s[0] = d[0] & (1LL << k);
		for (int i = 1; i < n; i++)
		{
			s[i] = s[i - 1] ^ (d[i] & (1LL << k));
		}
		int cnt = 0;
		for (int i = 0; i < n && cnt < m; i++)
		{
			if (cannot[i] == false && s[i] == 0)
			{
				cnt++;
			}
		}
		if (cnt >= m && s[n - 1] == 0)
		{
			for (int i = 0; i < n; i++)
			{
				if (s[i] != 0)
				{
					cannot[i] = true;
				}
			}
		}
		else
		{
			ans += 1LL << k;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
