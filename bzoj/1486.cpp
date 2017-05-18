// Problem Name: 最小圈
// Source: [HNOI2009]

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct vertex
{
	int first;
}V[3010];

struct edge
{
	int endp, next;
	double w;
}E[10010];

int n, m, ec = 1, cnt[3010];
double w[10010], dis[3010];
bool vis[3010], inq[3010];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

bool spfa()
{
	queue<int> Q;
	memset(vis, 0, sizeof(vis));
	memset(inq, 0, sizeof(inq));
	memset(cnt, 0, sizeof(cnt));
	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= n; i++)
	{
		if (vis[i] == false)
		{
			Q.push(i), vis[i] = true, inq[i] = true;
			while (!Q.empty())
			{
				int u = Q.front();
				Q.pop(), inq[u] = false;
				if (cnt[u]++ == n) return true;
				for (int cur = V[u].first; cur != 0; cur = E[cur].next)
				{
					double newdis = dis[u] + E[cur].w;
					if (newdis < dis[E[cur].endp])
					{
						dis[E[cur].endp] = newdis;
						if (inq[E[cur].endp] == false) Q.push(E[cur].endp), vis[E[cur].endp] = true, inq[E[cur].endp] = true;
					}
				}
			}
		}
	}
	return false;
}

bool flag, ins[3010];
void dfs(int u)
{
	if (ins[u] == true)
	{
		flag = true;
		return;
	}
	vis[u] = true;
	ins[u] = true;
	for (int cur = V[u].first; cur != 0 && flag == false; cur = E[cur].next)
	{
		double newdis = dis[u] + E[cur].w;
		if (newdis < dis[E[cur].endp])
		{
			dis[E[cur].endp] = newdis;
			dfs(E[cur].endp);
		}
	}
	ins[u] = false;
}

bool check()
{
	flag = false;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= n; i++)
	{
		if (vis[i] == false)
		{
			memset(ins, 0, sizeof(ins));
			dfs(i);
			if (flag == true) return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%lf", &u, &v, &w[i]);
		add_edge(u, v);
	}
	double l = -1e7, r = 1e7;
	while (r - l >= 1e-10)
	{
		double mid = (l + r) / 2;
		for (int i = 1; i <= m; i++)
		{
			E[i].w = w[i] - mid;
		}
		if (check() == true) r = mid;
		else l = mid;
	}
	printf("%.8lf\n", l);
	return 0;
}
