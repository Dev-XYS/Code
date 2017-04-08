// Problem Name: Palindromes
// Source: [APIO2014]

#include <cstdio>
#include <cstring>

#define NIL 0
#define ALPHABET_SIZE 26
#define STRING_LENGTH 300010

using namespace std;

struct node
{
	node *next[ALPHABET_SIZE], *fail;
	int start, len, cnt;
	node (int _start = 0, int _len = 0, int _cnt = 1) : fail(NIL), start(_start), len(_len), cnt(_cnt) { memset(next, 0, sizeof(next)); }
	void* operator new (size_t);
}*root, *empty, *last, pool[STRING_LENGTH];
int top = 0;

void* node::operator new (size_t)
{
	return pool + top++;
}

char str[STRING_LENGTH];
int len;

void extend(char x, int pos)
{
	node *u = last;
	while (str[pos] != str[pos - u->len - 1]) u = u->fail;
	if (u->next[x] == NIL)
	{
		node *cur = new node(pos - u->len - 1, u->len + 2);
		u->next[x] = cur;
		u = u->fail;
		if (u == NIL) cur->fail = empty;
		else
		{
			while (str[pos] != str[pos - u->len - 1]) u = u->fail;
			cur->fail = u->next[x];
		}
		last = cur;
	}
	else u->next[x]->cnt++, last = u->next[x];
}

void build()
{
	str[0] = '\xFF';
	root = new node(0, -1);
	empty = new node(0, 0);
	empty->fail = root;
	last = empty;
	for (int i = 1; i <= len; i++)
	{
		extend(str[i] - 'a', i);
	}
}

void print_substring(int l, int r)
{
	printf("\t");
	for (int i = l; i <= r; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");
}

void dfs(node *u)
{
	if (u->len > 0) print_substring(u->start, u->start + u->len - 1);
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (u->next[i] != NIL) dfs(u->next[i]);
	}
}

int main()
{
	scanf("%s", str + 1);
	len = strlen(str + 1);
	build();
	for (int i = top - 1; i > 0; i--)
	{
		pool[i].fail->cnt += pool[i].cnt;
	}
	long long ans = 0;
	for (int i = 1; i < top; i++)
	{
		if ((long long)pool[i].len * (long long)pool[i].cnt > ans) ans = (long long)pool[i].len * (long long)pool[i].cnt;
	}
	printf("%lld", ans);
	return 0;
}
