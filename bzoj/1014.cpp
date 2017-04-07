// Problem Name: 火星人 prefix
// Source: [JSOI2008]

#include <cstdio>
#include <cstring>

#define MOD 998244353LL

typedef long long ll;

using namespace std;

struct node
{
	node *ch[2];
	int size;
	char s;
	ll hash;
	node(char _s, ll _hash = 0);
}*root, *nil;

node::node(char _s, ll _hash) : size(1), s(_s), hash(_hash)
{
	ch[0] = ch[1] = nil;
}

char str[100010];
int m, len;
ll pow26[100010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	nil = new node('\0', 0);
	nil->size = 0;
	pow26[0] = 1;
	for (int i = 1; i <= 100005; i++)
	{
		pow26[i] = pow26[i - 1] * 26 % MOD;
	}
}

inline void update(node *u)
{
	u->size = u->ch[0]->size + u->ch[1]->size + 1;
	u->hash = (u->ch[0]->hash * pow26[u->ch[1]->size + 1] + u->s * pow26[u->ch[1]->size] + u->ch[1]->hash) % MOD;
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

void build(node *&u, int l, int r)
{
	if (l <= r)
	{
		int mid = (l + r) >> 1;
		u = new node(str[mid]);
		build(u->ch[0], l, mid - 1);
		build(u->ch[1], mid + 1, r);
		update(u);
	}
}

inline int cmp(int ikey, int ukey)
{
	if (ikey == ukey) return -1;
	return ikey < ukey ? 0 : 1;
}

void find_kth(node *&u, int k)
{
	int k0 = cmp(k, u->ch[0]->size + 1);
	if (k0 == -1) return;
	if (k0 == 1) k -= u->ch[0]->size + 1;
	int k1 = cmp(k, u->ch[k0]->ch[0]->size + 1);
	if (k1 == -1) goto ROTATE;
	if (k1 == 1) k -= u->ch[k0]->ch[0]->size + 1;
	find_kth(u->ch[k0]->ch[k1], k);
	if (k0 == k1) rotate(u, k0);
	else rotate(u->ch[k0], k1);
ROTATE: rotate(u, k0);
}

int query(int x, int y)
{
	int l = 0, r = min(len - x, len - y) + 1;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		ll hash1, hash2;
		find_kth(root, x);
		find_kth(root->ch[1], mid + 1);
		hash1 = root->ch[1]->ch[0]->hash;
		find_kth(root, y);
		find_kth(root->ch[1], mid + 1);
		hash2 = root->ch[1]->ch[0]->hash;
		if (hash1 == hash2) l = mid;
		else r = mid - 1;
	}
	return l;
}

void modify(int pos, char x)
{
	find_kth(root, pos + 1);
	root->s = x;
	update(root);
}

void insert(int pos, char x)
{
	find_kth(root, pos + 1);
	find_kth(root->ch[1], 1);
	root->ch[1]->ch[0] = new node(x, (ll)x);
	update(root->ch[1]);
	update(root);
	len++;
}

int main()
{
	char op[10], temp[10];
	int x, y;
	scanf("%s%d", str + 1, &m);
	init();
	build(root, 0, (len = strlen(str + 1)) + 1);
	while (m--)
	{
		scanf("%s", op);
		if (op[0] == 'Q')
		{
			scanf("%d%d", &x, &y);
			printf("%d\n", query(x, y));
		}
		else if (op[0] == 'R')
		{
			scanf("%d%s", &x, temp);
			modify(x, temp[0]);
		}
		else
		{
			scanf("%d%s", &x, temp);
			insert(x, temp[0]);
		}
	}
	return 0;
}
