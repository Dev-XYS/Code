// Problem Name: 狡猾的商人
// Source: [HNOI2005]

#include <cstdio>

using namespace std;

int T, n, m, fa[110], delta[110];

void init_dsu()
{
	for (int i = 0; i <= n; i++)
	{
		fa[i] = i;
		delta[i] = 0;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return getrt(fa[x]);
}

int query(int x)
{
	if (fa[x] == x) return 0;
	return delta[x] + query(fa[x]);
}

int main()
{
	int l, r, a;
	scanf("%d", &T);
	while (T--)
	{
		int fault = false;
		scanf("%d%d", &n, &m);
		init_dsu();
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d%d", &l, &r, &a);
			if (getrt(l - 1) == getrt(r))
			{
				if (query(r) - query(l - 1) != a) fault = true;
			}
			else
			{
				int rtr = getrt(r);
				delta[rtr] = a - query(r);
				fa[rtr] = l - 1;
			}
		}
		printf("%s\n", fault == false ? "true" : "false");
	}
	return 0;
}
