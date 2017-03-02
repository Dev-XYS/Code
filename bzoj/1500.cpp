// Problem Name: [NOI2005] 维修数列

#include <cstdio>
#include <cassert>

#define ensure(x) assert(x)

#define INF 1000000000
#define NONE 0x7FFFFFFF

using namespace std;

struct node
{
	node *ch[2];
	int size, v, same, sum, fix[2], ms;
	bool rev;
	node(int _size = 0, int _v = 0);
}*root, *nil;

int n, m, d[500010];

node::node(int _size, int _v) : size(_size), v(_v), same(NONE), sum(0), ms(0), rev(false)
{
	ch[0] = ch[1] = nil;
	fix[0] = fix[1] = 0;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int max(int x, int y, int z)
{
	return max(max(x, y), z);
}

inline void swap(node *&x, node *&y)
{
	node *temp = x;
	x = y;
	y = temp;
}

inline void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

void init()
{
	nil = new node(0, 0);
	nil->ch[0] = nil->ch[1] = nil;
	nil->ms = -INF;
}

void update(node *u)
{
	u->size = u->ch[0]->size + u->ch[1]->size + 1;
	u->sum = u->ch[0]->sum + u->v + u->ch[1]->sum;
	u->fix[0] = max(u->ch[0]->fix[0], u->ch[0]->sum + u->v + u->ch[1]->fix[0]);
	u->fix[1] = max(u->ch[1]->fix[1], u->ch[1]->sum + u->v + u->ch[0]->fix[1]);
	u->ms = max(u->ch[0]->ms, u->ch[0]->fix[1] + u->v + u->ch[1]->fix[0], u->ch[1]->ms);
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

int cmp(int ikey, int ukey)
{
	if (ikey == ukey) return -1;
	return ikey < ukey ? 0 : 1;
}

void push_down(node *u)
{
	if (u->same != NONE)
	{
		if (u->ch[0] != nil)
		{
			u->ch[0]->same = u->ch[0]->v = u->same;
			u->ch[0]->sum = u->same * u->ch[0]->size;
			u->ch[0]->fix[0] = u->ch[0]->fix[1] = u->same < 0 ? 0 : u->ch[0]->sum;
			u->ch[0]->ms = u->same < 0 ? u->v : u->same * u->ch[0]->size;
		}
		if (u->ch[1] != nil)
		{
			u->ch[1]->same = u->ch[1]->v = u->same;
			u->ch[1]->sum = u->same * u->ch[1]->size;
			u->ch[1]->fix[0] = u->ch[1]->fix[1] = u->same < 0 ? 0 : u->ch[1]->sum;
			u->ch[1]->ms = u->same < 0 ? u->v : u->same * u->ch[1]->size;
		}
		u->same = NONE;
	}
	if (u->rev == true)
	{
		u->rev = false;
		u->ch[0]->rev ^= 1;
		u->ch[1]->rev ^= 1;
		swap(u->ch[0], u->ch[1]);
		swap(u->ch[0]->fix[0], u->ch[0]->fix[1]);
		swap(u->ch[1]->fix[0], u->ch[1]->fix[1]);
	}
}

void build(node *&u, int l, int r)
{
	if (l <= r)
	{
		int mid = (l + r) >> 1;
		u = new node(0, d[mid]);
		build(u->ch[0], l, mid - 1);
		build(u->ch[1], mid + 1, r);
		update(u);
	}
}

void find_kth(node *&u, int k)
{
	push_down(u);
	int k0 = cmp(k, u->ch[0]->size + 1);
	if (k0 == -1)
	{
		return;
	}
	if (k0 == 1)
	{
		k -= u->ch[0]->size + 1;
	}
	push_down(u->ch[k0]);
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

void remove(node *u)
{
	if (u != nil)
	{
		remove(u->ch[0]);
		remove(u->ch[1]);
		delete u;
	}
}

void print(node *u, bool rev, int same)
{
	if (u != nil)
	{
		print(u->ch[rev ^ u->rev], rev ^ u->rev, same == NONE ? u->same : same);
		printf("%d ", same == NONE ? u->v : same);
		print(u->ch[rev ^ u->rev ^ 1], rev ^ u->rev, same == NONE ? u->same : same);
	}
}

int main()
{
	char op[20];
	int posi, tot, c;
	init();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	d[0] = -INF;
	d[n + 1] = -INF;
	build(root, 0, n + 1);
	while (m--)
	{
		scanf("%s", op);
		switch (op[2])
		{
		case 'S':
			scanf("%d%d", &posi, &tot);
			for (int i = 1; i <= tot; i++)
			{
				scanf("%d", &d[i]);
			}
			node *o;
			build(o, 1, tot);
			find_kth(root, posi + 1);
			find_kth(root->ch[1], 1);
			root->ch[1]->ch[0] = o;
			update(root->ch[1]);
			update(root);
			break;
		case 'L':
			scanf("%d%d", &posi, &tot);
			find_kth(root, posi);
			find_kth(root->ch[1], tot + 1);
			remove(root->ch[1]->ch[0]);
			root->ch[1]->ch[0] = nil;
			update(root->ch[1]);
			update(root);
			break;
		case 'K':
			scanf("%d%d%d", &posi, &tot, &c);
			find_kth(root, posi);
			find_kth(root->ch[1], tot + 1);
			root->ch[1]->ch[0]->same = root->ch[1]->ch[0]->v = c;
			root->ch[1]->ch[0]->sum = c * root->ch[1]->ch[0]->size;
			root->ch[1]->ch[0]->fix[0] = root->ch[1]->ch[0]->fix[1] = c < 0 ? 0 : root->ch[1]->ch[0]->sum;
			root->ch[1]->ch[0]->ms = c < 0 ? c : root->ch[1]->ch[0]->sum;
			update(root->ch[1]);
			update(root);
			break;
		case 'V':
			scanf("%d%d", &posi, &tot);
			find_kth(root, posi);
			find_kth(root->ch[1], tot + 1);
			root->ch[1]->ch[0]->rev ^= 1;
			swap(root->ch[1]->ch[0]->fix[0], root->ch[1]->ch[0]->fix[1]);
			update(root->ch[1]);
			update(root);
			break;
		case 'T':
			scanf("%d%d", &posi, &tot);
			if (tot == 0)
			{
				printf("0\n");
				break;
			}
			find_kth(root, posi);
			find_kth(root->ch[1], tot + 1);
			printf("%d\n", root->ch[1]->ch[0]->sum);
			break;
		case 'X':
			if (root->size == 2)
			{
				printf("0\n");
				break;
			}
			update(root);
			printf("%d\n", root->ms);
			break;
		}//print(root, 0, root->same);printf("\n");
		ensure(nil->size == 0 && nil->v == 0 && nil->sum == 0 && nil->fix[0] == 0 && nil->fix[1] == 0 && nil->ms == -INF && nil->same == NONE);
	}
	return 0;
}
