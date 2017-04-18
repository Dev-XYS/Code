// Problem Name: 数学作业
// Source: [HNOI2011]

#include <cstdio>
#include <cstring>

typedef long long ll;

using namespace std;

struct matrix
{
	int num[3][3];
	matrix() { memset(num, 0, sizeof(num)); }
	int* operator [] (int x) { return num[x]; }
	const int* operator [] (int x) const { return num[x]; }
};

ll n, p;

matrix operator * (const matrix &x, const matrix &y)
{
	matrix res;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				res[i][j] = ((ll)res[i][j] + (ll)x[i][k] * (ll)y[k][j]) % p;
			}
		}
	}
	return res;
}

ll qpow(ll x, ll y)
{//printf("qpow : y = %lld\n", y);
	if (y == 0) return 1;
	ll h = qpow(x * x % p, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x % p;
}

ll pow(ll x, int y)
{//printf("pow : y = %d\n", y);
	if (y == 0) return 1;
	ll h = pow(x * x, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x;
}

matrix qpow(const matrix &x, ll y)
{//printf("matrix qpow : y = %lld\n", y);
	if (y == 1) return x;
	matrix h = qpow(x * x, y >> 1);
	if ((y & 1) == 0) return h;
	else return h * x;
}

int log10(ll x)
{
	int res = -1;
	while (x > 0) res++, x /= 10;
	return res;
}

ll get(int k, ll cnt)
{//printf("get : k = %d, cnt = %lld\n", k, cnt);
	matrix base;
	base[0][0] = (int)qpow(10, k);
	base[0][1] = 1;
	base[0][2] = 0;
	base[1][0] = 0;
	base[1][1] = 1;
	base[1][2] = 1;
	base[2][0] = 0;
	base[2][1] = 0;
	base[2][2] = 1;
	base = qpow(base, cnt);
	return (qpow(10, k - 1) * base[0][1] + base[0][2]) % p;
}

int main()
{
	scanf("%lld%lld", &n, &p);
	if (n == 0)
	{
		printf("0\n");
		return 0;
	}
	int digits = log10(n);//printf("digits = %d\n", digits);
	ll ans = 0, zero = 0;
	if (digits > 0) ans = get(digits + 1, n - pow(10, digits) + 1), zero = qpow(qpow(10, (digits + 1)), n - pow(10, digits) + 1);
	else ans = get(1, n), zero = qpow(10, n) % p;//printf("init ans = %lld\n", ans);
	for (int i = digits; i >= 2; i--)
	{//printf("zero = %lld\n", zero);
		ans = (ans + get(i, pow(10, i) - pow(10, i - 1)) * zero) % p;
		zero = zero * qpow(qpow(10, i), pow(10, i) - pow(10, i - 1)) % p;
		n -= pow(10, i);
	}
	if (digits >= 1) ans = (ans + get(1, 9) * zero) % p;
	printf("%lld\n", ans);
	return 0;
}
