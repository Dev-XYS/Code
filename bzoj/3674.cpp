// Problem Name: 可持久化并查集加强版

#include <cstdio>
#include <vector>

#define NIL 0

using namespace std;

/* class : persistent_array begins */
/* Author : Dev-XYS */

#define PAF_START1          0x00000001
#define PAF_START0          0x00000002
#define PAF_UNIFORM         0x00000004
#define PAF_INCREASING      0x00000008

class persistent_array
{
private:
	struct node
	{
		node *lch, *rch;
		int value;
		node(int _value = 0) : value(_value) { lch = rch = NIL; }
	};

	int last_edition;
	vector<node*> root;

	void _M_build(node *&u, int l, int r, int start, int step);
	void _M_modify(node *&u, node *old, int l, int r, int p, int x);
	int _M_query(node *u, int l, int r, int p);

public:
	int size;

	persistent_array();
	persistent_array(int len, unsigned short flags);
	void duplicate(int edition);
	void duplicate();
	void modify(int p, int x);
	int query(int k, int p);
	int operator [] (int p);
};

void persistent_array::_M_build(node *&u, int l, int r, int start, int step)
{
	u = new node();
	if (l == r) u->value = start + step * (l - 1);
	else
	{
		int mid = (l + r) >> 1;
		_M_build(u->lch, l, mid, start, step);
		_M_build(u->rch, mid + 1, r, start, step);
	}
}

void persistent_array::_M_modify(node *&u, node *old, int l, int r, int p, int x)
{
	u = new node();
	if (l == r) u->value = x;
	else
	{
		int mid = (l + r) >> 1;
		if (p <= mid)
		{
			u->rch = old->rch;
			_M_modify(u->lch, old->lch, l, mid, p, x);
		}
		else
		{
			u->lch = old->lch;
			_M_modify(u->rch, old->rch, mid + 1, r, p, x);
		}
	}
}

int persistent_array::_M_query(node *u, int l, int r, int p)
{
	if (l == r) return u->value;
	else
	{
		int mid = (l + r) >> 1;
		if (p <= mid) return _M_query(u->lch, l, mid, p);
		else return _M_query(u->rch, mid + 1, r, p);
	}
}

persistent_array::persistent_array()
{
	size = 0;
	last_edition = -1;
}

persistent_array::persistent_array(int len, unsigned short flags)
{
	size = len;
	last_edition = 0;
	int start_value = 0, step_value = 0;
	if (flags & 0x0001) start_value = 1;
	if (flags & 0x0008) step_value = 1;
	root.push_back(NIL);
	_M_build(root[0], 1, len, start_value, step_value);
}

void persistent_array::duplicate(int edition)
{
	root.push_back(root[edition]);
	last_edition++;
}

void persistent_array::duplicate()
{
	duplicate(last_edition);
}

void persistent_array::modify(int p, int x)
{
	root.push_back(NIL);
	_M_modify(root[last_edition + 1], root[last_edition], 1, size, p, x);
	last_edition++;
}

int persistent_array::query(int k, int p)
{
	return _M_query(root[k], 1, size, p);
}

int persistent_array::operator [] (int p)
{
	return query(last_edition, p);
}

/* class : persistent_array ends */

persistent_array fa, size;

int getrt(int x)
{
	if (fa[x] == x) return x;
	return getrt(fa[x]);
}

void merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty)
	{
		fa.duplicate();
		size.duplicate();
		return;
	}
	int sx = size[x], sy = size[y];
	if (sx < sy)
	{
		fa.modify(rtx, rty);
		size.modify(y, sx + sy);
	}
	else
	{
		fa.modify(rty, rtx);
		size.modify(x, sx + sy);
	}
}

void roll_back(int edition)
{
	fa.duplicate(edition);
	size.duplicate(edition);
}

int query(int x, int y)
{
	fa.duplicate();
	size.duplicate();
	return getrt(x) == getrt(y) ? 1 : 0;
}

int main()
{
	int n, m, lastans = 0;
	scanf("%d%d", &n, &m);
	fa = persistent_array(n, PAF_START1 | PAF_INCREASING);
	size = persistent_array(n, PAF_START1 | PAF_UNIFORM);
	int op, a, b, k;
	while (m--)
	{
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%d%d", &a, &b);
			a ^= lastans;
			b ^= lastans;
			merge(a, b);
			break;
		case 2:
			scanf("%d", &k);
			k ^= lastans;
			roll_back(k);
			break;
		case 3:
			scanf("%d%d", &a, &b);
			a ^= lastans;
			b ^= lastans;
			printf("%d\n", lastans = query(a, b));
			break;
		}
	}
	return 0;
}
