// Problem Name: Corporative Network
// Source: Southeastern Europe 2004

#include <cstdio>

using namespace std;

int T, n, fa[20010], sum[20010];

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	int rt = getrt(fa[x]);
	sum[x] += sum[fa[x]];
	return fa[x] = rt;
}

void init_dsu()
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		sum[i] = 0;
	}
}

int main()
{
	char op[10];
	int a, b;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		init_dsu();
		while (true)
		{
			scanf("%s", op);
			if (op[0] == 'O') break;
			if (op[0] == 'E')
			{
				scanf("%d", &a);
				getrt(a);
				printf("%d\n", sum[a]);
			}
			else
			{
				scanf("%d%d", &a, &b);
				fa[a] = b;
				sum[a] = abs(a - b) % 1000;
			}
		}
	}
	return 0;
}
