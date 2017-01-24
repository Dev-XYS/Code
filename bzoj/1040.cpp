#include <cstdio>

typedef long long ll;

using namespace std;

struct vertex
{
	int first, w;
	ll ch, nch;
	bool vis;
}V[1000010];

struct edge
{
	int endp, next;
}E[2000010];

int n, ec = 2, cy1, cy2, ce, select;

inline ll max(ll x, ll y)
{
	return x > y ? x : y;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void circle(int u, int pe)
{//printf("circle : %d\n", u);
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if ((cur ^ pe) != 1)
		{
			if (V[E[cur].endp].vis == true)
			{
				cy1 = u;
				cy2 = E[cur].endp;
				ce = cur;
			}
			else
			{
				circle(E[cur].endp, cur);
			}
		}
	}
}

void DFS(int u, int pe)
{//printf("DFS : %d\n", u);
	V[u].ch = V[u].w;
	V[u].nch = 0;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if ((cur ^ pe) != 1 && (cur ^ ce) != 1 && cur != ce)
		{
			if (E[cur].endp == select) continue;
			DFS(E[cur].endp, cur);
			V[u].ch += V[E[cur].endp].nch;
			V[u].nch += max(V[E[cur].endp].ch, V[E[cur].endp].nch);
		}
	}
}

int main()
{
	int v;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &V[i].w, &v);
		add_edge(i, v);
		add_edge(v, i);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (V[i].vis == false)
		{
			circle(i, 0);//printf("cy1 = %d, cy2 = %d\n", cy1, cy2);
			select = cy1;
			DFS(cy1, 0);//for (int k = 1; k <= n; k++) printf("V[%d].ch = %lld, V[%d].nch = %lld\n", k, V[k].ch, k, V[k].nch);
			ll cy1max = V[cy1].nch;
			select = cy2;
			DFS(cy2, 0);
			ll cy2max = V[cy2].nch;
			ans += max(cy1max, cy2max);
		}
	}
	printf("%lld", ans);
	return 0;
}
