#include <cstdio>
#include <cmath>
#include <queue>

typedef long long ll;

using namespace std;

struct queue_node
{
	int ord;
	double key;
	queue_node(int _ord = 0, double _key = 0) : ord(_ord), key(_key) { }
};

int n, Y, u, w[100010], v[100010], del[100010];
priority_queue<queue_node> Q;

inline bool operator < (const queue_node &x, const queue_node &y)
{
	return x.key > y.key;
}

double dist(int x, int y)
{
	return sqrt((ll)x * (ll)x + (ll)y * (ll)y);
}

int main()
{
	scanf("%d%d%d", &n, &Y, &u);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &w[i]);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &v[i]);
	}
	for (int i = 0; i < n; i++)
	{
		Q.push(queue_node(i, (dist(w[i], 1) - w[i]) / (double)v[i]));
	}
	double ans = 0;
	for (int i = 0; i < Y; i++)
	{
		queue_node nd = Q.top();
		Q.pop();
		if (nd.key > 1.0f / (double)u)
		{
			ans = (Y - i) / (double)u;
			break;
		}
		del[nd.ord]++;
		Q.push(queue_node(nd.ord, (dist(w[nd.ord], del[nd.ord] + 1) - dist(w[nd.ord], del[nd.ord])) / (double)v[nd.ord]));
	}
	for (int i = 0; i < n; i++)
	{
		ans += dist(w[i], del[i]) / (double)v[i];
	}
	printf("%.4lf", ans);
	return 0;
}
