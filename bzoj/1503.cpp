#include <cstdio>

#define POOL_SIZE 100010

using namespace std;

struct node
{
	node *ch[2];
	int key, size;
	node(int _key = 0, int _size = 0);
	void* operator new (size_t);
}*root, *nil, pool[POOL_SIZE];

node::node(int _key, int _size) : key(_key), size(_size)
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
	u->size = u->ch[0]->size + u->ch[1]->size + 1;
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
	return ikey <= ukey ? 0 : 1;
}

void insert(node *&u, int key)
{
	if (u == nil)
	{
		u = new node(key, 1);
		return;
	}
	int k0 = cmpi(key, u->key), k1;
	if (u->ch[k0] == nil)
	{
		u->ch[k0] = new node(key, 1);
		goto END;
	}
	k1 = cmpi(key, u->ch[k0]->key);
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

int cmps(int isize, int usize)
{
	if (isize == usize)
	{
		return -1;
	}
	return isize < usize ? 0 : 1;
}

void splay(node *&u, int kth)
{
	int k0 = cmps(kth, u->ch[0]->size + 1), k1;
	if (k0 == -1)
	{
		return;
	}
	if (k0 == 1)
	{
		kth -= u->ch[0]->size + 1;
	}
	k1 = cmps(kth, u->ch[k0]->ch[0]->size + 1);
	if (k1 == -1)
	{
		goto END;
	}
	if (k1 == 1)
	{
		kth -= u->ch[k0]->ch[0]->size + 1;
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

int main()
{
	char op[10];
	int n, min, delta = 0, leave = 0, k;
	scanf("%d%d", &n, &min);
	init();
	while (n--)
	{
		scanf("%s%d", op, &k);
		switch (op[0])
		{
		case 'I':
			if (k < min) ;
			else insert(root, k - delta);
			break;
		case 'A':
			delta += k;
			break;
		case 'S':
			delta -= k;
			if (root != nil) splay(root, 1);
			while (root->key + delta < min)
			{
				remove();
				leave++;
				if (root != nil) splay(root, 1);
				else break;
			}
			break;
		case 'F':
			if (k > root->size)
			{
				printf("-1\n");
			}
			else
			{
				splay(root, root->size - k + 1);
				printf("%d\n", root->key + delta);
			}
			break;
		}
	}
	printf("%d", leave);
	return 0;
}
