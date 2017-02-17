#include <cstdio>
#include <cstring>

#define NIL 0
#define ALPHABET_SIZE 26

using namespace std;

struct node
{
	node *next[ALPHABET_SIZE], *parent;
	int len;
	node(int _len = 0) : len(_len) { memset(next, 0, sizeof(next)), parent = NIL; }
}*root, *last;

char a[100010], b[100010];
int la, lb;

void init()
{
	root = new node(0);
	last = root;
}

void extend(int x)
{
	node *p = last;
	node *np = new node(p->len + 1);
	while (p != NIL && p->next[x] == NIL)
	{
		p->next[x] = np;
		p = p->parent;
	}
	if (p == NIL)
	{
		np->parent = root;
	}
	else
	{
		node *q = p->next[x];
		if (q->len == p->len + 1)
		{
			np->parent = q;
		}
		else
		{
			node *nq = new node;
			*nq = *q;
			nq->len = p->len + 1;
			q->parent = np->parent = nq;
			while (p != NIL && p->next[x] == q)
			{
				p->next[x] = nq;
				p = p->parent;
			}
		}
	}
	last = np;
}

int main()
{
	scanf("%s%s", a, b);
	la = strlen(a), lb = strlen(b);
	init();
	for (int i = 0; i < la; i++)
	{
		extend(a[i] - 'a');
	}
	int len = 0, ans = 0;
	node *u = root;
	for (int i = 0; i < lb; i++)
	{
		int x = b[i] - 'a';
		if (u->next[x] != NIL) u = u->next[x], len++;
		else
		{
			while (u != NIL && u->next[x] == NIL)
			{
				u = u->parent;
			}
			if (u == NIL) u = root, len = 0;
			else len = u->len + 1, u = u->next[x];
		}
		if (len > ans) ans = len;
	}
	printf("%d", ans);
	return 0;
}
