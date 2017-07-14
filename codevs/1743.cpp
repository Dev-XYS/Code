// Problem Name: 反转卡片

#include <cstdio>
#include <cstdlib>
#include <utility>

using namespace std;

struct node
{
	node *lch, *rch;
	int key, pr, size;
	bool rev;
	node(int _key, int _size);
}*root, *nil;

node::node(int _key = 0, int _size = 1) : lch(nil), rch(nil), key(_key), pr(rand()), size(_size), rev(false) { }

int n;

void init()
{
	nil = new node(0, 0);
	root = nil;
}

void update(node *u)
{
	u->size = u->lch->size + u->rch->size + 1;
}

void push_down(node *u)
{
	if (u->rev == true)
	{
		swap(u->lch, u->rch);
		u->lch->rev ^= true;
		u->rch->rev ^= true;
		u->rev = false;
	}
}

pair<node*, node*> split(node *u, int k)
{
	if (u == nil)
	{
		return make_pair(nil, nil);
	}
	push_down(u);
	if (k <= u->lch->size)
	{
		pair<node*, node*> res = split(u->lch, k);
		u->lch = res.second;
		update(u);
		return make_pair(res.first, u);
	}
	else
	{
		pair<node*, node*> res = split(u->rch, k - u->lch->size - 1);
		u->rch = res.first;
		update(u);
		return make_pair(u, res.second);
	}
}

node* merge(node *u, node *v)
{
	if (u == nil)
	{
		return v;
	}
	if (v == nil)
	{
		return u;
	}
	if (u->pr > v->pr)
	{
		push_down(u);
		u->rch = merge(u->rch, v);
		update(u);
		return u;
	}
	else
	{
		push_down(v);
		v->lch = merge(u, v->lch);
		update(v);
		return v;
	}
}

void insert(int x)
{
	node *u = new node(x);
	root = merge(root, u);
}

int get_first()
{
	node *u, *next = root;
	bool rev = false;
	do
	{
		u = next;
		rev ^= u->rev;
		next = rev == false ? u->lch : u->rch;
	} while (next != nil);
	return u->key;
}

void print_tree(node*, bool);

void dfs(node *u)
{
	if (u != nil)
	{
		printf("(");
		dfs(u->lch);
		printf("%d%c", u->key, u->rev == false ? 'F' : 'T');
		dfs(u->rch);
		printf(")");
	}
}

void reverse(int l)
{
	pair<node*, node*> res = split(root, l);
	/*dfs(res.first);
	printf("\n");
	dfs(res.second);
	printf("\n");*/
	//print_tree(res.first, false);
	//printf("\n");
	//print_tree(res.second, false);
	//printf("\n");
	res.first->rev ^= true;
	root = merge(res.first, res.second);
}

void print_tree(node *u, bool rev)
{
	if (u != nil)
	{
		rev ^= u->rev;
		//printf("print_tree : %d, rev = %s\n", u->key, rev == true ? "true" : "false");
		if (rev == false)
		{
			print_tree(u->lch, false);
			printf("%d ", u->key);
			print_tree(u->rch, false);
		}
		else
		{
			print_tree(u->rch, true);
			printf("%d ", u->key);
			print_tree(u->lch, true);
		}
	}
}

void print_tree()
{
	print_tree(root, false);
	printf("\n");
}

int main()
{
	scanf("%d", &n);
	init();
	int x;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		insert(x);
	}
	for (int i = 0; i < 100000; i++)
	{
		//printf("i = %d\n", i);
		int first = get_first();
		//printf("first = %d\n", first);
		if (first == 1)
		{
			printf("%d\n", i);
			return 0;
		}
		reverse(first);
		/*print_tree();
		dfs(root);
		printf("\n");*/
	}
	printf("-1\n");
	return 0;
}
