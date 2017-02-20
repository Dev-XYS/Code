#include <cstdio>
#include <queue>

using namespace std;

struct vertex
{
	int first, dfn, low, col, dis, ideg, vis, cnt, block;
	bool dvis;
}V[100010];

struct edge
{
	int endp, next;
}E[1000010];

struct raw_edge
{
	int u, v;
	raw_edge(int _u = 0, int _v = 0) : u(_u), v(_v) { }
}R[1000010];

int ivc, iec, MOD, ec = 1, dfn = 1, col = 1, S[100010], sp = 0;
bool ins[100010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	V[u].dfn = V[u].low = dfn++;
	S[sp++] = u, ins[u] = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp);
			V[u].low = min(V[u].low, V[E[cur].endp].low);
		}
		else if (ins[E[cur].endp] == true)
		{
			V[u].low = min(V[u].low, V[E[cur].endp].low);
		}
	}
	if (V[u].low == V[u].dfn)
	{
		int temp;
		do
		{
			temp = S[--sp], ins[temp] = false;
			V[temp].col = col;
		} while (temp != u);
		col++;
	}
}

void build_dag()
{
	int _ec = 0;
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].col != V[i].col)
			{
				R[_ec++] = raw_edge(V[i].col, V[E[cur].endp].col);
			}
		}
		V[i].first = 0;
		V[V[i].col].block++;
	}
	ec = 1;
	for (int i = 0; i < _ec; i++)
	{
		add_edge(R[i].u, R[i].v);
		V[R[i].v].ideg++;
	}
}

void topo(int u)
{
	if (V[u].dvis == false)
	{
		V[u].dvis = true;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			topo(E[cur].endp);
		}
		S[sp++] = u;
	}
}

int main()
{
	int u, v;
	scanf("%d%d%d", &ivc, &iec, &MOD);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].dfn == 0) DFS(i);
	}
	build_dag();
	sp = 0;
	for (int i = 1; i < col; i++)
	{
		if (V[i].dvis == false) topo(i), V[i].dis = V[i].block;
	}
	for (int i = sp - 1; i >= 0; i--)
	{
		for (int cur = V[S[i]].first; cur != 0; cur = E[cur].next)
		{
			if (V[S[i]].dis + V[E[cur].endp].block > V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = V[S[i]].dis + V[E[cur].endp].block;
			}
		}
	}
	int maxdis = 0;
	for (int i = 1; i < col; i++)
	{
		if (V[i].dis > maxdis) maxdis = V[i].dis;
	}
	for (int i = 0; i < sp; i++)
	{
		for (int cur = V[S[i]].first; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].vis != S[i] && V[S[i]].dis + V[E[cur].endp].block == V[E[cur].endp].dis)
			{
				V[E[cur].endp].vis = S[i];
				V[S[i]].cnt = (V[S[i]].cnt + V[E[cur].endp].cnt) % MOD;
			}
		}
		if (V[S[i]].dis == maxdis) V[S[i]].cnt = 1;
	}
	int ans = 0;
	for (int i = 1; i < col; i++)
	{
		if (V[i].ideg == 0) ans = (ans + V[i].cnt) % MOD;
	}
	printf("%d\n%d", maxdis, ans);
	return 0;
}
