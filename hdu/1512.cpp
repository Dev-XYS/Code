// Problem Name: Monkey King

#include <cstdio>
#include <algorithm>

using namespace std;

struct node
{
	node *lch, *rch, *fa;
	int key, dis;
	node(int _key = 0, int _dis = 0);
	void* operator new (size_t s);
}*nil, pool[100010];
int top;

node::node(int _key, int _dis) : lch(nil), rch(nil), fa(nil), key(_key), dis(_dis) { }

void* node::operator new (size_t s) { return pool + top++; }

int n, m;

void global_init()
{
	nil = pool;
	nil->lch = nil->rch = nil->fa = nil;
	nil->dis = -1;
}

void init()
{
	top = 1;
}

inline void update(node *u)
{
	if (u->lch->dis < u->rch->dis)
	{
		swap(u->lch, u->rch);
	}
	u->dis = u->rch->dis + 1;
}

node* join(node *u, node *v)
{
	if (u == nil)
	{
		return v;
	}
	if (v == nil)
	{
		return u;
	}
	if (u->key > v->key)
	{
		u->rch = join(u->rch, v);
		u->rch->fa = u;
		update(u);
		return u;
	}
	else
	{
		v->rch = join(v->rch, u);
		v->rch->fa = v;
		update(v);
		return v;
	}
}

node* getrt(node *u)
{
	while (u->fa != nil)
	{
		u = u->fa;
	}
	return u;
}

int main()
{
	global_init();
	while (scanf("%d", &n) > 0)
	{
		init();
		int x;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x);
			new node(x, 0);
		}
		scanf("%d", &m);
		int u, v;
		while (m--)
		{
			scanf("%d%d", &u, &v);
			node *rtu = getrt(pool + u), *rtv = getrt(pool + v);
			if (rtu == rtv)
			{
				printf("-1\n");
			}
			else
			{
				node *o;
				o = join(rtu->lch, rtu->rch);
				o->fa = nil;
				rtu->lch = rtu->rch = nil;
				rtu->key >>= 1;
				rtu = join(o, rtu);
				o = join(rtv->lch, rtv->rch);
				o->fa = nil;
				rtv->lch = rtv->rch = nil;
				rtv->key >>= 1;
				rtv = join(o, rtv);
				o = join(rtu, rtv);
				printf("%d\n", o->key);
			}
		}
	}
	return 0;
}
