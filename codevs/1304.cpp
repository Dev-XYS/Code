#include <cstdio>

typedef long long ll;

using namespace std;

struct vertex
{
	int first, ideg, size, topo;
}V[1500010];

struct edge
{
	int endp, next;
}E[1500010];

int ivc, ec = 1, p, fac[1500010], inv[1500010];

ll qpow(ll x, int y)
{
	if (y == 1) return x;
	ll t = qpow(x, y >> 1);
	t = t * t % (ll)p;
	if ((y & 1) == 0) return t;
	else return t * x % (ll)p;
}

void init()
{
	fac[0] = 1;
	for (int i = 1; i <= ivc; i++)
	{
		fac[i] = (int)((ll)fac[i - 1] * (ll)i % (ll)p);
	}
	inv[ivc] = qpow(fac[ivc], p - 2);
	for (int i = ivc - 1; i >= 1; i--)
	{
		inv[i] = (int)((ll)inv[i + 1] * (ll)(i + 1) % (ll)p);
	}
}

void add_edge(int u, int v)
{
	V[v].ideg++;
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	ll x = 1LL;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		DFS(E[cur].endp);
		V[u].size += V[E[cur].endp].size;
		x = x * (ll)V[E[cur].endp].topo % (ll)p;
		x = x * (ll)inv[V[E[cur].endp].size] % (ll)p;
	}
	x = x * (ll)fac[V[u].size] % (ll)p;
	V[u].topo = (int)x;
	V[u].size++;
}

int main()
{
	int x, y;
	scanf("%d%d", &ivc, &p);
	init();
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &x, &y);
		add_edge(x, y);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].ideg == 0)
		{
			DFS(i);
			printf("%d", V[i].topo);
			break;
		}
	}
	return 0;
}
