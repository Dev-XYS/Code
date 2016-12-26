#include <cstdio>

using namespace std;

struct node
{
	node *ch[2];
	int size, v;
	bool rev;
	node(int _size = 0, int _v = 0);
	void* operator new (size_t);
}*root, *nil, pool[100010];
int top = 0;

int n, m, d[100010];

node::node(int _size, int _v) : size(_size), v(_v), rev(false)
{
	ch[0] = ch[1] = nil;
}

void* node::operator new (size_t)
{
	return pool + top++;
}

inline void swap(node *&x, node *&y)
{
	node *temp = x;
	x = y;
	y = temp;
}

void init()
{
	nil = new node(0, 0);
	nil->ch[0] = nil->ch[1] = nil;
}

void rotate(node *&u, int dir)
{
	u->size -= u->ch[dir]->ch[dir]->size + 1;
	u->ch[dir]->size += u->ch[dir ^ 1]->size + 1;
	node *o = u->ch[dir];
	u->ch[dir] = o->ch[dir ^ 1];
	o->ch[dir ^ 1] = u;
	u = o;
}

int cmp(int ikey, int ukey)
{
	if (ikey == ukey)
		return -1;
	return ikey < ukey ? 0 : 1;
}

void build(node *&u, int l, int r)
{
	if (l > r)
	{
		return;
	}
	if (l == r)
	{
		u = new node(1, d[l]);
	}
	else
	{
		int mid = (l + r) >> 1;
		u = new node(r - l + 1, d[mid]);
		build(u->ch[0], l, mid - 1);
		build(u->ch[1], mid + 1, r);
	}
}

void find_kth(node *&u, int k)
{
	if (u->rev == true)
	{
		u->rev = false;
		u->ch[0]->rev ^= 1;
		u->ch[1]->rev ^= 1;
		swap(u->ch[0], u->ch[1]);
	}
	int k0 = cmp(k, u->ch[0]->size + 1);
	if (k0 == -1)
	{
		return;
	}
	if (k0 == 1)
	{
		k -= u->ch[0]->size + 1;
	}
	if (u->ch[k0]->rev == true)
	{
		u->ch[k0]->rev = false;
		u->ch[k0]->ch[0]->rev ^= 1;
		u->ch[k0]->ch[1]->rev ^= 1;
		swap(u->ch[k0]->ch[0], u->ch[k0]->ch[1]);
	}
	int k1 = cmp(k, u->ch[k0]->ch[0]->size + 1);
	if (k1 == -1)
	{
		rotate(u, k0);
		return;
	}
	find_kth(u->ch[k0]->ch[k1], k1 == 1 ? k - (u->ch[k0]->ch[0]->size + 1) : k);
	if (k0 == k1)
	{
		rotate(u, k0);
	}
	else
	{
		rotate(u->ch[k0], k1);
	}
	rotate(u, k0);
}

int rpt = 0;
void print(node *u, int rev)
{
	if (u != nil)
	{
		rev ^= u->rev;
		print(u->ch[rev], rev);
		d[rpt++] = u->v;
		print(u->ch[rev ^ 1], rev);
	}
}

int main()
{
	int l, r;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		d[i + 1] = i;
	}
	init();
	build(root, 1, n + 2);
	while (m--)
	{
		scanf("%d%d", &l, &r);
		if (l == r) continue;
		find_kth(root, l);
		find_kth(root->ch[1], r - l + 2);
		root->ch[1]->ch[0]->rev ^= 1;
	}
	print(root, 0);
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", d[i]);
	}
	return 0;
}
