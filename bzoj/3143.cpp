// Problem Name: 游走
// Source: [HNOI2013]

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n, m, deg[510];
vector<int> E[510];
long double a[510][510], res[510], exp[250010];

inline long double _abs(long double x)
{
	return x < 0 ? -x : x;
}

void solve()
{
	for (int i = 0; i < n; i++)
	{
		int mi = i;
		for (int j = i + 1; j < n; j++)
		{
			if (_abs(a[j][i]) > _abs(a[mi][i])) mi = j;
		}
		for (int j = i; j <= n; j++)
		{
			swap(a[i][j], a[mi][j]);
		}
		for (int j = i + 1; j < n; j++)
		{
			for (int k = n; k >= i; k--)
			{
				a[j][k] -= a[i][k] * (a[j][i] / a[i][i]);
			}
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		long double x = a[i][n];
		for (int j = i + 1; j < n; j++)
		{
			x -= a[i][j] * res[j];
		}
		res[i] = x / a[i][i];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		u--, v--;
		E[u].push_back(v);
		E[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < E[i].size(); j++)
		{
			if (E[i][j] != n - 1) a[i][E[i][j]] = 1.0f / (long double)deg[E[i][j]];
		}
		a[i][i] = -1;
	}
	a[0][n] = -1;
	a[n - 1][n - 1] = 1;
	a[n - 1][n] = 0;
	solve();//for (int i = 0; i < n; i++) printf("res[%d] = %.3lf\n", i, res[i]);
	int ec = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < E[i].size(); j++)
		{
			exp[ec++] = res[i] / (long double)deg[i] + res[E[i][j]] / (long double)deg[E[i][j]];
		}
	}
	sort(exp, exp + ec);//for (int i = 0; i < ec; i++) printf("exp[%d] = %.3lf\n", i, exp[i]);
	long double ans = 0;
	for (int i = 0; i < ec; i += 2)
	{//printf("+= %.3lf * %d\n", exp[i], m - (i >> 1));
		ans += exp[i] * (long double)(m - (i >> 1));
	}
	printf("%.3lf\n", (double)ans);
	return 0;
}
