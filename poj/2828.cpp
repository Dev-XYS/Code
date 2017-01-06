#include <cstdio>

#define POOL_SIZE 200010

using namespace std;

struct node
{
	int size, value;
	node *ch[2];
	node(int _size = 0, int _value = 0);
	void* operator new (size_t);
}*root, *nil, pool[POOL_SIZE];

node::node(int _size, int _value) : size(_size), value(_value)
{
	ch[0] = ch[1] = nil;
}

int top;
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

void rotate(node *&u, int dir)
{
	int x = dir ^ 1;
	node *o = u->ch[dir];
	u->ch[dir] = o->ch[x];
	o->ch[x] = u;
	u = o;
	u->ch[x]->size = u->ch[x]->ch[0]->size + u->ch[x]->ch[1]->size + 1;
	u->size = u->ch[0]->size + u->ch[1]->size + 1;
}

inline int compare(int ikey, int ukey)
{
	return ikey <= ukey ? 0 : 1;
}	

void insert(node *&u, int k, int value)
{
	if (u == nil)
	{
		u = new node(1, value);
		return;
	}
	int k0 = compare(k, u->ch[0]->size + 1);
	if (k0 == 1)
	{
		k -= u->ch[0]->size + 1;
	}
	if (u->ch[k0] == nil)
	{
		u->ch[k0] = new node(1, value);
	}
	else
	{
		int k1 = compare(k, u->ch[k0]->ch[0]->size + 1);
		if (k1 == 1)
		{
			k -= u->ch[k0]->ch[0]->size + 1;
		}
		insert(u->ch[k0]->ch[k1], k, value);
		if (k0 == k1)
		{
			rotate(u, k0);
		}
		else
		{
			rotate(u->ch[k0], k1);
		}
	}
	rotate(u, k0);
}

inline int readint()
{
	int res = 0;
	char c;
	do
	{
		c = getchar();
	} while (!(c >= '0' && c <= '9'));
	do
	{
		res = res * 10 + (c - '0');
		c = getchar();
	} while (c >= '0' && c <= '9');
	return res;
}

void print(node *u)
{
	if (u != nil)
	{
		print(u->ch[0]);
		printf("%d ", u->value);
		print(u->ch[1]);
	}
}

int main()
{
	int n, pos, val;
	while (scanf("%d", &n) > 0)
	{
		init();
		for (int i = 0; i < n; i++)
		{
			pos = readint();
			val = readint();
			insert(root, pos + 1, val);
		}
		print(root);
		printf("\n");
	}
	return 0;
}
