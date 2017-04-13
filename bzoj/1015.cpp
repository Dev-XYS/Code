// Problem Name: 星球大战 starwar
// Source: [JSOI2008]

#include <cstdio>
#include <vector>

using namespace std;

struct raw_edge
{
	int u, v;
}R[200010];

int ivc, iec, k, fa[400010], size[400010], ops[400010], res[400010];
bool del[400010];
vector<int> E[400010];

void init_dsu()
{
	for (int i = 0; i < ivc; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = getrt(fa[x]);
}

int merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty) return 0;
	int sx = size[rtx], sy = size[rty];
	if (sx < sy)
	{
		fa[rtx] = rty;
		size[rty] += sx;
	}
	else
	{
		fa[rty] = rtx;
		size[rtx] += sy;
	}
	return 1;
}

int main()
{
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &R[i].u, &R[i].v);
		E[R[i].u].push_back(R[i].v);
		E[R[i].v].push_back(R[i].u);
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &ops[i]);
		del[ops[i]] = true;
	}
	init_dsu();
	int cnt = ivc - k;
	for (int i = 0; i < iec; i++)
	{
		if (del[R[i].u] == false && del[R[i].v] == false)
		{
			cnt -= merge(R[i].u, R[i].v);
		}
	}
	for (int i = k - 1; i >= 0; i--)
	{
		res[i] = cnt;
		cnt++;
		for (int j = 0; j < E[ops[i]].size(); j++)
		{
			if (del[E[ops[i]][j]] == false) cnt -= merge(ops[i], E[ops[i]][j]);
		}
		del[ops[i]] = false;
	}
	printf("%d\n", cnt);
	for (int i = 0; i < k; i++)
	{
		printf("%d\n", res[i]);
	}
	return 0;
}
