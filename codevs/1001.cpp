#include <cstdio>
#include <algorithm>

#define INF 10000000000000000LL

typedef long long ll;

using namespace std;

struct frac
{
	ll a, b; // a / b
	frac(ll _a = 0, ll _b = 0) : a(_a), b(_b) { }
	bool operator < (const frac &x) { return a * x.b < b * x.a; }
};

struct raw_edge
{
	int u, v, x;
}R[5010];

int ivc, iec, s, t, fa[510], size[510];

void init_dsu()
{
	for (int i = 1; i <= ivc; i++)
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

void merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx != rty)
	{
		if (size[rtx] < size[rty])
		{
			fa[rtx] = rty;
			size[rty] += size[rtx];
		}
		else
		{
			fa[rty] = rtx;
			size[rtx] += size[rty];
		}
	}
}

bool _raw_edge_x_cmp_(const raw_edge &a, const raw_edge &b)
{
	return a.x < b.x;
}

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].x);
	}
	scanf("%d%d", &s, &t);
	sort(R, R + iec, _raw_edge_x_cmp_);
	frac min = frac(INF, 1);
	for (int i = 0; i < iec; i++)
	{
		init_dsu();
		for (int j = i; j < iec; j++)
		{
			merge(R[j].u, R[j].v);
			if (getrt(s) == getrt(t))
			{
				if (frac(R[j].x, R[i].x) < min)
				{
					min = frac(R[j].x, R[i].x);
				}
				goto NEXT;
			}
		}
		break;
	NEXT:;
	}
	if (min.a == INF)
	{
		printf("IMPOSSIBLE");
	}
	else
	{
		ll g = gcd(min.a, min.b);
		if (min.b / g != 1) printf("%lld/%lld", min.a / g, min.b / g);
		else printf("%lld", min.a / g);
	}
	return 0;
}
