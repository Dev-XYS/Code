// Problem Name: 树
// Source: [JLOI2012]

#include <cstdio>

using namespace std;

struct vertex
{
	int first, c;
}V[100010];

struct edge
{
	int endp, next;
}E[200010];

int ivc, value, ec = 2, S[100010], sp = 0, ans = 0;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

bool check()
{
	int l = 0, r = sp;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (S[sp] - S[mid] <= value) r = mid;
		else l = mid + 1;
	}
	return S[sp] - S[l] == value;
}

void dfs(int u, int fa)
{
	S[sp + 1] = S[sp] + V[u].c;
	sp++;
	if (check() == true) ans++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa) dfs(E[cur].endp, u);
	}
	sp--;
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &value);
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%d", &V[i].c);
	}
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	printf("%d", ans);
	return 0;
}
