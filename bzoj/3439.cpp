// Problem Name: Kpm的MC密码
// Source: Kpmcup#0 By Greens

#include <cstdio>
#include <cstring>

#define NIL 0

using namespace std;

struct snode
{
	snode *lch, *rch;
	int cnt;
	snode(int _cnt = 0) : lch(NIL), rch(NIL), cnt(_cnt) { }
};

struct tnode
{
	tnode *next[26];
	snode *tree;
	int cnt;
	tnode(int _cnt = 0) : cnt(_cnt) { memset(next, 0, sizeof(next)); }
}*root;

int n;
char temp[300010];
tnode *end[300010];

void init()
{
	root = new tnode;
}

void modify(snode *&u, int l, int r, int p)
{
	if (u == NIL) u = new snode;
	if (l == r) u->cnt++;
	else
	{
		u->cnt++;
		int mid = (l + r) >> 1;
		if (p <= mid) modify(u->lch, l, mid, p);
		else modify(u->rch, mid + 1, r, p);
	}
}

tnode* insert(char *s, int ord)
{
	int len = strlen(s);
	tnode *cur = root;
	modify(cur->tree, 1, n, ord);
	for (int i = len - 1; i >= 0; i--)
	{
		int x = s[i] - 'a';
		if (cur->next[x] == NIL) cur->next[x] = new tnode;
		cur = cur->next[x];
		modify(cur->tree, 1, n, ord);
	}
	return cur;
}

int find_kth(snode *u, int l, int r, int k)
{
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (u->lch == NIL) return find_kth(u->rch, mid + 1, r, k);
	if (u->lch->cnt < k) return find_kth(u->rch, mid + 1, r, k - u->lch->cnt);
	return find_kth(u->lch, l, mid, k);
}

int find_kth(tnode *u, int k)
{
	if (u->tree->cnt < k) return -1;
	return find_kth(u->tree, 1, n, k);
}

int main()
{
	scanf("%d", &n);
	init();
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", temp);
		end[i] = insert(temp, i);
	}
	int k;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &k);
		printf("%d\n", find_kth(end[i], k));
	}
	return 0;
}
