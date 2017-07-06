#include <cstdio>
#include <cstring>

#define MOD 1000000007

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
}V[1000010];

struct edge
{
	int endp, next;
}E[1000010];

int T, len, ec, pi[1000010], S[1000010], ans;
char s[1000010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void init()
{
	ans = 1;
	ec = 1;
	for (int i = 0; i <= len; i++)
	{
		V[i].first = 0;
	}
}

void compute_prefix_function()
{
	pi[0] = 0;
	int q = 0;
	add_edge(0, 1);
	for (int i = 1; i < len; i++)
	{
		while (s[i] != s[q] && q > 0) q = pi[q - 1];
		if (s[i] == s[q]) q++;
		pi[i] = q;
		add_edge(q, i + 1);
	}
}

void dfs(int u, int depth)
{
	S[depth] = u;
	int l = 0, r = depth;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (S[mid] <= (u >> 1))
		{
			l = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	ans = (ll)ans * (l + 1) % MOD;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		dfs(E[cur].endp, depth + 1);
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s);
		len = strlen(s);
		init();
		compute_prefix_function();
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
