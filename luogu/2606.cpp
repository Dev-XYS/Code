// Problem Name: 排列计数 Perm
// Source: [ZJOI2010]

#include <cstdio>

typedef long long ll;

using namespace std;

struct dfs_return_info
{
	int size, res;
	dfs_return_info(int _size = 0, int _res = 0) : size(_size), res(_res) { }
};

int n, p, fact[1000010], inv[1000010], fact_inv[1000010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	int to = min(n + 1, p);
	fact[0] = 1;
	for (int i = 1; i < to; i++)
	{
		fact[i] = (ll)fact[i - 1] * i % p;
	}
	inv[0] = 1;
	inv[1] = 1;
	for (int i = 2; i < to; i++)
	{
		inv[i] = -(ll)(p / i) * inv[p % i] % p;
		if (inv[i] < 0) inv[i] += p;
	}
	fact_inv[0] = inv[0];
	for (int i = 1; i < to; i++)
	{
		fact_inv[i] = (ll)fact_inv[i - 1] * inv[i] % p;
	}
}

inline int _C(int n, int m)
{
	return (ll)fact[n] * fact_inv[n - m] % p * fact_inv[m] % p;
}

int C(int n, int m)
{
	int res = 1;
	while (n / p > 0)
	{
		res = (ll)res * _C(n % p, m % p) % p;
		n /= p, m /= p;
	}
	return res;
}

dfs_return_info dfs(int u)
{
	if (u > n) return dfs_return_info(0, 1);
	dfs_return_info l = dfs(u << 1);
	dfs_return_info r = dfs((u << 1) + 1);
	return dfs_return_info(l.size + r.size + 1, (ll)_C(l.size + r.size, l.size) * l.res % p * r.res % p);
}

int main()
{
	scanf("%d%d", &n, &p);
	init();
	printf("%d\n", dfs(1).res);
	return 0;
}
