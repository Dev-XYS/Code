// Problem Name: 直径
// Source: [SDOI2013]

#include <cstdio>

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
	ll dis;
}V[200010];

struct edge
{
	int endp, next, w;
	bool ond;
}E[400010];

int n, ec = 2, S[200010], sp, dia[200010], dl;
bool found;
ll total, ps[200010];

inline void check_min(int &x, int y)
{
	if (y < x) x = y;
}

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

inline void check_max(ll &x, ll y)
{
	if (y > x) x = y;
}

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void dfs_far(int u, int fa, ll dis)
{
	V[u].dis = dis;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			dfs_far(E[cur].endp, u, dis + E[cur].w);
		}
	}
}

void dfs_mark(int u, int fa, int tar)
{
	if (u == tar)
	{
		for (int i = 0; i < sp; i++)
		{
			E[S[i]].ond = E[S[i] ^ 1].ond = true;
			dia[i] = S[i];
		}
		dl = sp;
		found = true;
	}
	for (int cur = V[u].first; cur != 0 && found == false; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			S[sp++] = cur;
			dfs_mark(E[cur].endp, u, tar);
			sp--;
		}
	}
}

ll get_diameter()
{
	dfs_far(1, 0, 0);//printf("dfs_far finished\n");
	int s = 1;
	for (int i = 2; i <= n; i++)
	{
		if (V[i].dis > V[s].dis)
		{
			s = i;
		}
	}
	dfs_far(s, 0, 0);//printf("dfs_far finished\n");
	int t = 1;
	for (int i = 2; i <= n; i++)
	{
		if (V[i].dis > V[t].dis)
		{
			t = i;
		}
	}
	dfs_mark(s, 0, t);//printf("dfs_mark finished\n");
	return V[t].dis;
}

ll dfs_dis(int u, int fa)
{//printf("dis_dis : %d\n", u);
	ll res = 0;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].ond == false && E[cur].endp != fa)
		{
			check_max(res, dfs_dis(E[cur].endp, u) + E[cur].w);
		}
	}
	return res;
}

int get_cnt()
{//printf("dl = %d\n", dl);
	ps[0] = E[dia[0]].w;
	for (int i = 1; i < dl; i++)
	{
		ps[i] = ps[i - 1] + E[dia[i]].w;
	}
	total = ps[dl - 1];//for (int i = 0; i < dl; i++) printf("ps[%d] = %lld\n", i, ps[i]); printf("total = %lld\n", total);
	int l = 0, r = dl;
	for (int i = 0; i < dl - 1; i++)
	{
		ll maxdis = dfs_dis(E[dia[i]].endp, 0);//printf("maxdis = %lld\n", maxdis);
		if (maxdis == ps[i]) check_max(l, i + 1);
		if (maxdis == total - ps[i]) check_min(r, i + 1);
		//printf("total - ps[%d] = %lld\n", i, total - ps[i]);
	}
	return r - l;
}

int main()
{
	scanf("%d", &n);
	int u, v, w;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	printf("%lld\n", get_diameter());
	printf("%d\n", get_cnt());
	return 0;
}
