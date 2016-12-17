#include <cstdio>
#include <cstring>

#define MAX_COUNT 1000

typedef long long ll;

using namespace std;

ll S[MAX_COUNT], ans[MAX_COUNT];
int sp = 0;
bool found = false;

inline ll max(ll x, ll y)
{
	return x > y ? x : y;
}

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

ll ax, bx;
void frac_sub(ll a, ll b, ll k)
{
	ax = a * k - b;
	bx = b * k;
	ll g = gcd(ax, bx);
	ax /= g;
	bx /= g;
}

void DFS(ll a, ll b, int k, ll l)
{
	if (k == 1)
	{
		if (a == 1 && b > l)
		{
			S[sp] = b;
			if (b < ans[sp] || ans[sp] == 0)
			{
				memcpy(ans, S, sizeof(ans));
			}
			found = true;
		}
	}
	else
	{
		for (ll i = max(l + 1, (b - 1) / a + 1); a * i < b * k; i++)
		{
			frac_sub(a, b, i);
			S[sp++] = i;
			DFS(ax, bx, k - 1, i);
			sp--;
		}
	}
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	ll g = gcd(a, b);
	a /= g;
	b /= g;
	for (int i = 1; ; i++)
	{
		DFS(a, b, i, 0);
		if (found == true)
		{
			for (int j = 0; j < i; j++)
			{
				printf("%lld ", ans[j]);
			}
			break;
		}
	}
	return 0;
}
