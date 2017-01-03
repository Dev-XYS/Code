#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>

typedef long long ll;

using namespace std;

namespace Hash
{
	const ll L = 1000003LL;
	const ll S = 100000LL;
	struct node
	{
		int next;
		ll key, v;
	}pool[S];
	int first[L];
	int pc;

	void init()
	{
		pc = 0;
		memset(first, 0, sizeof(first));
	}

	void insert(ll key, ll v)
	{
		pool[++pc].next = first[key % L];
		first[key % L] = pc;
		pool[pc].key = key;
		pool[pc].v = v;
	}

	ll query(ll key)
	{
		for (int cur = first[key % L]; cur != 0; cur = pool[cur].next)
		{
			if (pool[cur].key == key)
			{
				return pool[cur].v;
			}
		}
		return -1;
	}
}

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	else
	{
		ll gcd = exgcd(b, a % b, x, y);
		ll temp = x;
		x = y;
		y = temp - a / b * y;
		return gcd;
	}
}

ll mul_inv(int x, int mod)
{
	ll a, b;
	exgcd(x, mod, a, b);
	return (a % mod + mod) % mod;
}

ll bsgs(ll a, ll b, ll c)
{
	ll g, d = 1LL, n = 0LL;
	while ((g = gcd(a, c)) != 1)
	{
		if (b % g != 0)
		{
			return -1;
		}
		n++;
		b /= g;
		c /= g;
		d = d * (a / g) % c;
	}
	b = b * mul_inv(d, c) % c;
	
	int m = (int)sqrt(c);
	ll u = b, u0 = 1LL;
	Hash::init();
	for (int i = 1; i <= m; i++)
	{
		u = u * a % c;
		if (Hash::query(u) != -1LL)
		{
			break;
		}
		Hash::insert(u, i);
		u0 = u0 * a % c;
	}

	u = 1LL;
	for (ll i = m; i - c < m; i += m)
	{
		u = u * u0 % c;
		if (Hash::query(u) != -1)
		{
			return i - Hash::query(u) + n;
		}
	}
	return -1;
}

int main()
{
	ll a, b, c;
	while (true)
	{
		scanf("%lld%lld%lld", &a, &c, &b);
		if (a == 0 && b == 0 && c == 0)
		{
			break;
		}
		ll ans = bsgs(a, b, c);
		if (ans == -1)
		{
			printf("No Solution\n");
		}
		else
		{
			printf("%lld\n", ans);
		}
	}
	return 0;
}
