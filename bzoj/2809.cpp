#include <cstdio>
#include <algorithm>

#define NODE_COUNT 200000

typedef long long ll;

using namespace std;

struct vertex
{
	int first, c, l;
}V[100010];

struct edge
{
	int endp, next;
}E[100010];

int ivc, m, ec = 0;
ll ans = 0LL;

void add_edge(int u, int v)
{
	E[++ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
}
	
namespace LeftTree
{
	struct node
	{
		node *lch, *rch;
		int key, dist;
		node(int _key = 0, int _dist = 0);
		void* operator new (size_t);
	}*nil, pool[NODE_COUNT];

	node::node(int _key, int _dist) : key(_key), dist(_dist)
	{
		lch = rch = nil;
	}

	int top = 0;
	void* node::operator new (size_t)
	{
		return pool + top++;
	}

	void init()
	{
		top = 0;
		nil = new node;
	}

	void merge(node *&u, node *&o)
	{//printf("merge\n");
		if (o == nil)
		{
			return;
		}
		if (u == nil)
		{
			swap(u, o);
			return;
		}
		if (u->key < o->key)
		{
			swap(u, o);
		}
		merge(u->rch, o);
		if (u->lch->dist < u->rch->dist)
		{
			swap(u->lch, u->rch);
		}
		u->dist = u->rch->dist + 1;
	}

	int extract_max(node *&rt)
	{
		int res = rt->key;
		merge(rt->lch, rt->rch);
		rt = rt->lch;
		return res;
	}
}

using namespace LeftTree;

int chsize;
ll chsum;
node* DFS(int u)
{//printf("DFS : %d\n", u);
	int size = 1;
	ll sum = (ll)V[u].c;
	node *rt = new node(V[u].c);
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		node *o = DFS(E[cur].endp);
		size += chsize;
		sum += chsum;
		merge(rt, o);
	}
	while (sum > m)
	{//printf("while : sum = %lld\n", sum);
		size--;
		sum -= extract_max(rt);
	}
	if ((ll)size * (ll)V[u].l > ans)
	{
		ans = (ll)size * (ll)V[u].l;
	}//printf("FINISH : %d\n", u);
	chsize = size;
	chsum = sum;
	return rt;
}

int main()
{
	int b, c, l;
	scanf("%d%d", &ivc, &m);
	scanf("%d%d%d", &b, &c, &l);
	V[1].c = c;
	V[1].l = l;
	for (int i = 2; i <= ivc; i++)
	{
		scanf("%d%d%d", &b, &c, &l);
		V[i].c = c;
		V[i].l = l;
		add_edge(b, i);
	}
	init();
	DFS(1);
	printf("%lld", ans);
	return 0;
}
