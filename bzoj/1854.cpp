// Problem Name: [SCOI2010] 游戏

#include <cstdio>

using namespace std;

int n, fa[10010];
bool vis[10010];

inline void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

void init_dsu()
{
	for (int i = 1; i <= 10000; i++)
	{
		fa[i] = i;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = getrt(fa[x]);
}

void merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx > rty) swap(rtx, rty);
	vis[rtx] = true;
	fa[rtx] = rty;
}

int main()
{
	int a, b;
	scanf("%d", &n);
	init_dsu();
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &a, &b);
		if (getrt(a) != getrt(b)) merge(a, b);
		else vis[getrt(a)] = true;
	}
	for (int i = 1; i <= 10001; i++)
	{
		if (vis[i] == false)
		{
			printf("%d", i - 1);
			break;
		}
	}
	return 0;
}
