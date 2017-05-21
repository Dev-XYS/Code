// Problem Name: 荷马史诗
// Source: [NOI2015]
// Algorithm: k进制哈夫曼编码（Huffman Coding）

#include <cstdio>
#include <queue>

typedef long long ll;

using namespace std;

struct queue_node
{
	ll w;
	int depth;
	queue_node(ll _w = 0, int _depth = 0) : w(_w), depth(_depth) { }
};

inline bool operator < (const queue_node &x, const queue_node &y)
{
	if (x.w == y.w) return x.depth > y.depth;
	return x.w > y.w;
}

int main()
{
	priority_queue<queue_node> Q;
	int n, k;
	scanf("%d%d", &n, &k);
	ll w;
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &w);
		Q.push(queue_node(w, 0));
	}
	for (int i = (k - 1) - ((n - 1) % (k - 1) == 0 ? k - 1 : (n - 1) % (k - 1)); i > 0; i--)
	{
		Q.push(queue_node(0, 0));
	}
	ll total = 0;
	while (Q.size() > 1)
	{
		ll wsum = 0;
		int depth = 0;
		for (int i = 0; i < k; i++)
		{
			queue_node u = Q.top();
			Q.pop();
			wsum += u.w;
			if (u.depth > depth) depth = u.depth;
			total += u.w;
		}
		Q.push(queue_node(wsum, depth + 1));
	}
	printf("%lld\n%d\n", total, Q.top().depth);
	return 0;
}
