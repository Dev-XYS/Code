#include <cstdio>

using namespace std;

int n, m, q, pi[200010], c[200010];
char a[200010], b[200010];

void calc_pi()
{
	pi[0] = 0;
	int q = 0;
	for (int i = 1; i < m; i++)
	{
		while (q > 0 && b[i] != b[q])
		{
			q = pi[q - 1];
		}
		if (b[i] == b[q]) q++;
		pi[i] = q;
	}
}

void kmp_matcher()
{
	calc_pi();
	int q = 0;
	for (int i = 0; i < n; i++)
	{
		while (q > 0 && a[i] != b[q])
		{
			q = pi[q - 1];
		}
		if (a[i] == b[q]) q++;
		c[q]++;
		if (q == m) q = pi[q - 1];
	}
}

int main()
{
	scanf("%d%d%d%s%s", &n, &m, &q, a, b);
	kmp_matcher();
	for (int i = m - 1; i >= 0; i--)
	{
		c[pi[i]] += c[i + 1];
	}
	for (int i = 0; i < m; i++)
	{
		c[i] -= c[i + 1];
	}
	int x;
	while (q--)
	{
		scanf("%d", &x);
		printf("%d\n", c[x]);
	}
	return 0;
}
