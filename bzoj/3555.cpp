// Problem Name: 企鹅QQ
// Source: [CTSC2014]

#include <cstdio>
#include <algorithm>

#define MOD 999999999997LL

typedef long long ll;

using namespace std;

int n, l, sigma, ans;
char s[30010][210];
ll pow[210], oh[30010], dh[30010];

void init_pow()
{
	pow[0] = 1;
	for (int i = 1; i < l; i++)
	{
		pow[i] = pow[i - 1] * 256LL % MOD;
	}
}

int main()
{
	scanf("%d%d%d", &n, &l, &sigma);
	init_pow();
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s[i]);
		for (int j = 0; j < l; j++)
		{
			oh[i] = (oh[i] + (ll)s[i][j] * pow[j]) % MOD;
		}
	}
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dh[j] = ((oh[j] - (ll)s[j][i] * pow[i]) % MOD + MOD) % MOD;
		}
		sort(dh, dh + n);
		dh[n] = -1LL;
		int start = 0;
		for (int j = 1; j <= n; j++)
		{
			if (dh[j] != dh[start]) ans += (j - start) * (j - start - 1) >> 1, start = j;
		}
	}
	printf("%d", ans);
	return 0;
}
