// Problem Name: Bill的挑战
// Source: [SDOI2009]

#include <cstdio>
#include <cstring>

#define MOD 1000003

typedef long long ll;

using namespace std;

int T, n, k, len, C[20][20], choice[20], co[20][20];
char s[20][60];

void init_C()
{
	for (int i = 0; i < 20; i++)
	{
		C[i][0] = 1;
	}
	for (int i = 1; i < 20; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
}

void ex_gcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0) x = 1, y = 0;
	else
	{
		ex_gcd(b, a % b, x, y);
		ll temp = x;
		x = y;
		y = temp - a / b * y;
	}
}

int mul_inv(int x)
{
	ll a, b;
	ex_gcd((ll)((x + MOD) % MOD), MOD, a, b);
	return (int)(a % MOD);
}

int mod_div(int x, int y)
{
	return (int)((ll)x * (ll)mul_inv(y) % (ll)MOD);
}

int main()
{
	init_C();
	scanf("%d", &T);
	while (T--)
	{
		memset(choice, 0, sizeof(choice));
		memset(co, 0, sizeof(co));
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s[i]);
		}
		len = strlen(s[0]);
		for (int i = (1 << n) - 1; i >= 0; i--)
		{
			int res = 1, c = 0, x;
			for (int l = 0; l < len; l++)
			{
				char ch = '?';
				int x = i;
				for (int p = 0; p < n; p++)
				{
					if ((x & 1) == 1)
					{
						if (s[p][l] != '?')
						{
							if (ch == '?') ch = s[p][l];
							else if (ch != s[p][l]) goto NEXT;
						}
					}
					x >>= 1;
				}
				if (ch == '?') (res *= 26) %= MOD;
			}
			x = i;
			while (x > 0)
			{
				if ((x & 1) == 1) c++;
				x >>= 1;
			}
			(choice[c] += res) %= MOD;
		NEXT:;
		}
		bool plus = true;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (plus == true) co[i][j] = (co[i - 1][j] + C[j][i]) % MOD;
				else co[i][j] = (co[i - 1][j] - C[j][i]) % MOD;
			}
			plus ^= true;
		}
		plus = false;
		for (int i = 2; i <= n; i++)
		{
			if (plus == true) choice[i] = (choice[i - 1] + choice[i]) % MOD;
			else choice[i] = (choice[i - 1] - choice[i]) % MOD;
			plus ^= true;
		}
		for (int i = n; i > 1; i--)
		{
			(choice[i] -= choice[i - 1]) %= MOD;
		}
		for (int i = n; i >= 1; i--)
		{
			for (int j = n; j > i; j--)
			{
				(choice[i] -= (int)((ll)(co[i][j] - co[i - 1][j]) * (ll)choice[j] % MOD)) %= MOD;
			}
			choice[i] = mod_div(choice[i], (co[i][i] - co[i - 1][i]) % MOD);
		}
		for (int i = 1; i <= n; i++)
		{
			(choice[0] -= choice[i]) %= MOD;
		}
		printf("%d\n", choice[k] < 0 ? choice[k] + MOD : choice[k]);
	}
	return 0;
}
