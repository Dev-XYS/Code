// Problem Name: 校门外的区间
// Source: [SDOI2008]

#include <cstdio>
#include <cstring>

#define NIL 0

using namespace std;

struct node
{
	node *lch, *rch;
	bool rev;
	int same;
	node() : lch(NIL), rch(NIL), rev(false), same(-1) { }
}*root;

struct interval
{
	int l, r;
	interval(int _l = 0, int _r = 0) : l(_l), r(_r) { }
};

const int n = 65535 * 2;
bool exist[n + 10], empty = true;

interval get_interval(char *s)
{
	int p = 1, l = 0, r = 0;
	while ('0' <= s[p] && s[p] <= '9')
	{
		l = l * 10 + (s[p] - '0');
		p++;
	}
	p++;
	while ('0' <= s[p] && s[p] <= '9')
	{
		r = r * 10 + (s[p] - '0');
		p++;
	}
	return interval(s[0] == '[' ? l * 2 : l * 2 + 1, s[p] == ']' ? r * 2 : r * 2 - 1);
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

void push_down(node *u)
{
	if (u->same != -1)
	{
		u->lch->rev = u->rch->rev = false;
		u->lch->same = u->rch->same = u->same;
		u->same = -1;
	}
	else if (u->rev == true)
	{
		if (u->lch->same != -1) u->lch->same ^= 1;
		else u->lch->rev ^= 1;
		if (u->rch->same != -1) u->rch->same ^= 1;
		else u->rch->rev ^= 1;
		u->rev = false;
	}
}

void make_same(node *u, int l, int r, int ql, int qr, int v)
{
	if (l == ql && r == qr)
	{
		if (l != r) push_down(u);
		else u->rev = false;
		u->same = v;
		return;
	}
	push_down(u);
	int mid = (l + r) >> 1;
	if (qr <= mid) make_same(u->lch, l, mid, ql, qr, v);
	else if (ql > mid) make_same(u->rch, mid + 1, r, ql, qr, v);
	else
	{
		make_same(u->lch, l, mid, ql, mid, v);
		make_same(u->rch, mid + 1, r, mid + 1, qr, v);
	}
}

void reverse(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		if (l != r)
		{
			push_down(u);
			u->rev ^= 1;
		}
		else
		{
			if (u->same != -1) u->same ^= 1;
			else u->rev ^= 1;
		}
		return;
	}
	push_down(u);
	int mid = (l + r) >> 1;
	if (qr <= mid) reverse(u->lch, l, mid, ql, qr);
	else if (ql > mid) reverse(u->rch, mid + 1, r, ql, qr);
	else
	{
		reverse(u->lch, l, mid, ql, mid);
		reverse(u->rch, mid + 1, r, mid + 1, qr);
	}
}

void make_same(int l, int r, int v)
{
	make_same(root, 0, n, l, r, v);
}

void reverse(int l, int r)
{
	reverse(root, 0, n, l, r);
}

void print(node *u, int l, int r)
{
	if (l == r)
	{
		if ((u->same ^ u->rev) == 1) exist[l] = true;
		return;
	}
	push_down(u);
	int mid = (l + r) >> 1;
	print(u->lch, l, mid);
	print(u->rch, mid + 1, r);
}

void print()
{
	for (int i = 0; i <= n; )
	{
		if (exist[i] == true)
		{
			printf("%c%d,", (i & 1) == 0 ? '[' : '(', i >> 1);
			while (exist[i] == true) i++;
			printf("%d%c ", i >> 1, ((i - 1) & 1) == 0 ? ']' : ')');
			empty = false;
		}
		else i++;
	}
}

int main()
{
	build(root, 0, n);
	root->same = 0;
	char op[10], itv[20];
	while (scanf("%s%s", op, itv) > 0)
	{
		interval u = get_interval(itv);
		int l = u.l, r = u.r;
		if (l > r) continue;
		if (op[0] == 'U')
		{
			make_same(l, r, 1);
		}
		else if (op[0] == 'I')
		{
			if (l - 1 >= 0) make_same(0, l - 1, 0);
			if (r + 1 <= n) make_same(r + 1, n, 0);
		}
		else if (op[0] == 'D')
		{
			make_same(l, r, 0);
		}
		else if (op[0] == 'C')
		{
			if (l - 1 >= 0) make_same(0, l - 1, 0);
			reverse(l, r);
			if (r + 1 <= n) make_same(r + 1, n, 0);
		}
		else
		{
			reverse(l, r);
		}
	}
	print(root, 0, n);
	print();
	if (empty == true) printf("empty set");
	return 0;
}
