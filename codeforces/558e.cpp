// Problem Name: A Simple Task
// Source: Codeforces Round #312 (Div. 2), Problem E

#include <cstdio>
#include <cstring>
#include <algorithm>

#define NIL 0

using namespace std;

struct array
{
	int cnt[26];
	array() {
		memset(cnt, 0, sizeof(cnt));
	}
	int& operator [] (int index) {
		return cnt[index];
	}
	array operator + (const array &x) {
		array res = *this;
		for (int i = 0; i < 26; i++)
		{
			res.cnt[i] += x.cnt[i];
		}
		return res;
	}
}cnt;

struct node
{
	node *lch, *rch;
	int lazy;
	array cnt;
	node() : lch(NIL), rch(NIL), lazy(-1), cnt() { }
}*root;

int n, q;
char s[100010];

void refresh(node *u, int l, int r, array &cnt, int k)
{
	int len = r - l + 1;
	if (k == 1)
	{
		for (int i = 0; i <= 25; i++)
		{
			u->cnt[i] = min(len, cnt[i]);
			len -= u->cnt[i];
			cnt[i] -= u->cnt[i];
		}
	}
	else
	{
		for (int i = 25; i >= 0; i--)
		{
			u->cnt[i] = min(len, cnt[i]);
			len -= u->cnt[i];
			cnt[i] -= u->cnt[i];
		}
	}
	u->lazy = k;
}

void update(node *u)
{
	u->cnt = u->lch->cnt + u->rch->cnt;
}

void push_down(node *u, int l, int r)
{
	if (u->lazy != -1)
	{
		array cnt = u->cnt;
		int mid = (l + r) >> 1;
		refresh(u->lch, l, mid, cnt, u->lazy);
		refresh(u->rch, mid + 1, r, cnt, u->lazy);
		u->lazy = -1;
	}
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->cnt[s[l] - 'a'] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(u->lch, l, mid);
	build(u->rch, mid + 1, r);
	update(u);
}

array query(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->cnt;
	}
	push_down(u, l, r);
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		return query(u->lch, l, mid, ql, qr);
	}
	else if (ql > mid)
	{
		return query(u->rch, mid + 1, r, ql, qr);
	}
	else
	{
		return query(u->lch, l, mid, ql, mid) + query(u->rch, mid + 1, r, mid + 1, qr);
	}
}

void modify(node *u, int l, int r, int ql, int qr, int k)
{
	if (l == ql && r == qr)
	{
		refresh(u, l, r, cnt, k);
		return;
	}
	push_down(u, l, r);
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		modify(u->lch, l, mid, ql, qr, k);
	}
	else if (ql > mid)
	{
		modify(u->rch, mid + 1, r, ql, qr, k);
	}
	else
	{
		modify(u->lch, l, mid, ql, mid, k);
		modify(u->rch, mid + 1, r, mid + 1, qr, k);
	}
	update(u);
}

char find(array cnt)
{
	for (int i = 0; i <= 25; i++)
	{
		if (cnt[i] > 0)
		{
			return i + 'a';
		}
	}
}

void answer(node *u, int l, int r)
{
	if (l == r)
	{
		printf("%c", find(u->cnt));
		return;
	}
	push_down(u, l, r);
	int mid = (l + r) >> 1;
	answer(u->lch, l, mid);
	answer(u->rch, mid + 1, r);
}

int main()
{
	scanf("%d%d%s", &n, &q, s + 1);
	build(root, 1, n);
	int l, r, k;
	while (q--)
	{
		scanf("%d%d%d", &l, &r, &k);
		cnt = query(root, 1, n, l, r);
		modify(root, 1, n, l, r, k);
	}
	answer(root, 1, n);
	return 0;
}
