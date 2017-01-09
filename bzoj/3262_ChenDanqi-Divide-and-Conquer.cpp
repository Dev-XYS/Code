#include <cstdio>
#include <algorithm>

#define printf(...); printf(__VA_ARGS__);fflush(stdout);

#define LOWBIT(x) ((x) & (-(x)))

#define INF 1000000000
#define ELEMENT_COUNT 100010
#define MAX_PROPERTY 200010

using namespace std;

struct point
{
	int a, b, c, cnt, res;
}d[ELEMENT_COUNT];

int n, k, f[MAX_PROPERTY], cnt[ELEMENT_COUNT];

void init(int p)
{
	while (p <= k)
	{
		f[p] = 0;
		p += LOWBIT(p);
	}
}

void modify(int p, int x)
{
	while (p <= k)
	{//printf("modify\n");
		f[p] += x;
		p += LOWBIT(p);
	}
}

int query(int p)
{
	int res = 0;
	while (p > 0)
	{
		res += f[p];
		p -= LOWBIT(p);
	}
	return res;
}

bool operator < (const point &x, const point &y)
{
	if (x.b != y.b) return x.b < y.b;
	return x.c <= y.c;
}

void cdq(int l, int r)
{//printf("cdq : l = %d, r = %d.\n", l, r);
	if (l == r)
	{
		d[l].res += d[l].cnt - 1;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	static point dl[ELEMENT_COUNT], dr[ELEMENT_COUNT];
	for (int i = l; i <= mid; i++)
	{
		dl[i] = d[i];
	}
	for (int i = mid + 1; i <= r; i++)
	{
		dr[i] = d[i];
	}
	dl[mid + 1].b = dr[r + 1].b = INF;
	int pl = l, pr = mid + 1;
	for (int i = l; i <= r; i++)
	{//printf("merge : i = %d.\n", i);
		if (dl[pl] < dr[pr])
		{
			modify(dl[pl].c, dl[pl].cnt);
			d[i] = dl[pl++];
		}
		else
		{
			dr[pr].res += query(dr[pr].c);
			d[i] = dr[pr++];
		}
	}
	for (int i = l; i <= mid; i++)
	{
		init(dl[i].c);
	}//printf("init result :");for (int i = 1; i <= k; i++) {printf(" %d", f[i]);} printf("\n");
}

bool operator == (const point &x, const point &y)
{
	return x.a == y.a && x.b == y.b && x.c == y.c;
}

int unique()
{
	int p = 0, sc = 1;
	for (int i = 1; i <= n; i++)
	{
		if (d[i + 1] == d[i])
		{
			sc++;
			continue;
		}
		d[i].cnt = sc;
		d[++p] = d[i];
		sc = 1;
	}
	return p;
}

bool _point_x_cmp_(point x, point y)
{
	if (x.a != y.a) return x.a < y.a;
	if (x.b != y.b) return x.b < y.b;
	return x.c < y.c;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &d[i].a, &d[i].b, &d[i].c);
	}
	sort(d + 1, d + n + 1, _point_x_cmp_);
	int _n = unique();//for (int i = 1; i <= n; i++) {printf("(%d, %d, %d) : cnt = %d\n", d[i].a, d[i].b, d[i].c, d[i].cnt);}
	cdq(1, _n);//printf("cdq finished.\n");
	for (int i = 1; i <= _n; i++)
	{
		cnt[d[i].res] += d[i].cnt;
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", cnt[i]);
	}
	return 0;
}
