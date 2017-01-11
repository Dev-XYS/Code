#include <cstdio>

#define INF 1000000000
#define POOL_SIZE 200000

using namespace std;

struct node
{
	node *ch[2];
	int key, size, cnt;
	node(int _key = 0, int _size = 0, int _cnt = 0);
	void* operator new (size_t);
}*root, *nil, pool[POOL_SIZE];

node::node(int _key, int _size, int _cnt) : key(_key), size(_size), cnt(_cnt)
{
	ch[0] = ch[1] = nil;
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
	root = nil;
}

void update(node *u)
{
	u->size = u->ch[0]->size + u->ch[1]->size + u->cnt;
}

void rotate(node *&u, int dir)
{
	node *o = u->ch[dir];
	u->ch[dir] = o->ch[dir ^ 1];
	o->ch[dir ^ 1] = u;
	u = o;
	update(u->ch[dir ^ 1]);
	update(u);
}

int cmpi(int ikey, int ukey)
{
	if (ikey == ukey) return -1;
	return ikey <= ukey ? 0 : 1;
}

void insert(node *&u, int key)
{
	if (u == nil)
	{
		u = new node(key, 1, 1);
		return;
	}
	int k0 = cmpi(key, u->key), k1;
	if (k0 == -1)
	{
		u->size++;
		u->cnt++;
		return;
	}
	if (u->ch[k0] == nil)
	{
		u->ch[k0] = new node(key, 1, 1);
		goto END;
	}
	k1 = cmpi(key, u->ch[k0]->key);
	if (k1 == -1)
	{
		u->ch[k0]->size++;
		u->ch[k0]->cnt++;
		goto END;
	}
	insert(u->ch[k0]->ch[k1], key);
	if (k0 == k1)
	{
		rotate(u, k0);
	}
	else
	{
		rotate(u->ch[k0], k1);
	}
END:
	rotate(u, k0);
}

int cmpf(int ikey, int ukey)
{
	if (ikey == ukey) return -1;
	return ikey < ukey ? 0 : 1;
}

void find(node *&u, int key)
{
	int k0 = cmpf(key, u->key);
	if (k0 == -1)
	{
		return;
	}
	int k1 = cmpf(key, u->ch[k0]->key);
	if (k1 == -1)
	{
		goto END;
	}
	find(u->ch[k0]->ch[k1], key);
	if (k0 == k1)
	{
		rotate(u, k0);
	}
	else
	{
		rotate(u->ch[k0], k1);
	}
END:
	rotate(u, k0);
}

int cmps(int isize, int uchsize, int cnt)
{
	if (isize > uchsize && isize <= uchsize + cnt) return -1;
	return isize <= uchsize ? 0 : 1;
}

void splay(node *&u, int kth)
{
	int k0 = cmps(kth, u->ch[0]->size, u->cnt), k1;
	if (k0 == -1)
	{
		return;
	}
	if (k0 == 1)
	{
		kth -= u->ch[0]->size + u->cnt;
	}
	k1 = cmps(kth, u->ch[k0]->ch[0]->size, u->ch[k0]->cnt);
	if (k1 == -1)
	{
		goto END;
	}
	if (k1 == 1)
	{
		kth -= u->ch[k0]->ch[0]->size + u->ch[k0]->cnt;
	}
	splay(u->ch[k0]->ch[k1], kth);
	if (k0 == k1)
	{
		rotate(u, k0);
	}
	else
	{
		rotate(u->ch[k0], k1);
	}
END:
	rotate(u, k0);
}

void remove()
{
	if (root->cnt > 1) root->size--, root->cnt--; else
	if (root->ch[0] == nil)
	{
		root = root->ch[1];
	}
	else
	{
		splay(root->ch[0], root->ch[0]->size);
		root->ch[0]->ch[1] = root->ch[1];
		root = root->ch[0];
		update(root);
	}
}

int pre(node *u, int key)
{
	if (u == nil) return -INF;
	if (key <= u->key)
	{
		return pre(u->ch[0], key);
	}
	else
	{
		int res = pre(u->ch[1], key);
		return u->key > res ? u->key : res;
	}
}

int suf(node *u, int key)
{
	if (u == nil) return INF;
	if (key >= u->key)
	{
		return suf(u->ch[1], key);
	}
	else
	{
		int res = suf(u->ch[0], key);
		return u->key < res ? u->key : res;
	}
}

int main()
{
	int n, op, x;
	scanf("%d", &n);
	init();
	insert(root, -INF);
	insert(root, INF);
	while (n--)
	{
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%d", &x);
			insert(root, x);
			break;
		case 2:
			scanf("%d", &x);
			find(root, x);
			remove();
			break;
		case 3:
			scanf("%d", &x);
			find(root, x);
			printf("%d\n", root->ch[0]->size);
			break;
		case 4:
			scanf("%d", &x);
			splay(root, x + 1);
			printf("%d\n", root->key);
			break;
		case 5:
			scanf("%d", &x);
			printf("%d\n", pre(root, x));
			break;
		case 6:
			scanf("%d", &x);
			printf("%d\n", suf(root, x));
			break;
		}
	}
	return 0;
}
