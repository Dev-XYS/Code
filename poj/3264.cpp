#include <cstdio>

#define ELEMENT_COUNT 50010
#define NODE_COUNT 100010

using namespace std;

struct result
{
	int min, max;
	result(int _min = 0, int _max = 0) : min(_min), max(_max) { }
};

struct node
{
	node *lch, *rch;
	int min, max;
	node(int _min = 0, int _max = 0) : min(_min), max(_max) { lch = rch = 0; }
	void* operator new (size_t);
}*root, pool[NODE_COUNT];

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

int n, m;
int d[ELEMENT_COUNT];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->min = d[l];
		u->max = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		u->min = min(u->lch->min, u->rch->min);
		u->max = max(u->lch->max, u->rch->max);
	}
}

result query(node *u, int l, int r, int s, int t)
{
	if (l == s && r == t)
	{
		return result(u->min, u->max);
	}
	else
	{
		int mid = (l + r) >> 1;
		result res;
		if (t <= mid)
		{
			res = query(u->lch, l, mid, s, t);
		}
		else if (s > mid)
		{
			res = query(u->rch, mid + 1, r, s, t);
		}
		else
		{
			result a = query(u->lch, l, mid, s, mid), b = query(u->rch, mid + 1, r, mid + 1, t);
			res = result(min(a.min, b.min), max(a.max, b.max));
		}
		u->min = min(u->lch->min, u->rch->min);
		u->max = max(u->lch->max, u->rch->max);
		return res;
	}
}

int main()
{
	int l, r;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build(root, 1, n);
	while (m--)
	{
		scanf("%d%d", &l, &r);
		result res = query(root, 1, n, l, r);
		printf("%d\n", res.max - res.min);
	}
	return 0;
}
