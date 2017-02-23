#include <cstdio>
#include <cstring>
#include <algorithm>

#define MOD 31011

using namespace std;

struct raw_edge
{
	int u, v, w;
}R[1010];

int ivc, iec, fa[110], size[110], _fa[110], sfa[110];

void init_dsu(int *f)
{
	for (int i = 1; i <= ivc; i++)
	{
		f[i] = i;
	}
}

int getrt(int x, int *f)
{
	if (f[x] == x) return x;
	return getrt(f[x], f);
}

void merge(int rtx, int rty, int *f)
{
	f[rty] = rtx;
}

bool _raw_edge_w_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.w < y.w;
}

int main()
{
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].w);
	}
	sort(R, R + iec, _raw_edge_w_cmp_);
	int total = 0, ans = 1;
	int start = 0, end = 0;
	init_dsu(fa);
	for (int i = 1; i <= iec && total < ivc - 1; i++)
	{
		if (R[i].w != R[i - 1].w)
		{
			end = i - 1;
			memcpy(_fa, fa, sizeof(fa));
			int cnt = 0;
			for (int k = start; k <= end; k++)
			{
				int rtu = getrt(R[k].u, fa), rtv = getrt(R[k].v, fa);
				if (rtu != rtv)
				{
					merge(rtu, rtv, fa);
					cnt++;
					total++;
				}
			}
			int kind = 0;
			for (int k = (1 << (end - start + 1)) - 1; k >= 0; k--)
			{
				memcpy(sfa, _fa, sizeof(_fa));
				int x = k, c = 0;
				while (x > 0)
				{
					if ((x & 1) == 1) c++;
					x >>= 1;
				}
				if (c != cnt) continue;
				x = k;
				int p = start;
				while (x > 0)
				{
					if ((x & 1) == 1)
					{
						int rtu = getrt(R[p].u, sfa), rtv = getrt(R[p].v, sfa);
						if (rtu != rtv)
						{
							merge(rtu, rtv, sfa);
						}
						else
						{
							goto NOT;
						}
					}
					p++;
					x >>= 1;
				}
				kind++;
			NOT:;
			}
			ans = ans * kind % MOD;
			start = i;
		}
	}
	if (total < ivc - 1) printf("0");
	else printf("%d", ans);
	return 0;
}
