#include <cstdio>
#include <cstring>
#include <queue>

#define NIL 0
#define ALPHABET_SIZE 26
#define STRING_LENGTH 2000010
#define PATTERN_COUNT 1010
#define PATTERN_LENGTH 60
#define NODE_COUNT 60010

using namespace std;

struct node
{
	int id;
	node *next[ALPHABET_SIZE], *fail, *last;
	node();
	void* operator new (size_t);
}*root, pool[NODE_COUNT];

int idc = 0;
char s[PATTERN_COUNT][PATTERN_LENGTH], t[STRING_LENGTH];
int len[PATTERN_COUNT], cnt[PATTERN_COUNT];

node::node() : id(0), fail(NIL), last(NIL)
{
	memset(next, 0, sizeof(next));
}

int top = 0;
void* node::operator new (size_t)
{
	return pool + top++;
}

void init_trie()
{
	top = 0;
	idc = 0;
	root = new node;
}

void insert(char *s)
{
	int l = strlen(s), x;
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		x = s[i] - 'A';
		if (cur->next[x] == NIL)
		{
			cur->next[x] = new node;
		}
		cur = cur->next[x];
	}
	cur->id = ++idc;
}

void init_fail()
{
	queue<node*> Q;
	root->fail = root;
	root->last = root;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->next[i] != NIL)
		{
			root->next[i]->fail = root;
			root->next[i]->last = root;
			Q.push(root->next[i]);
		}
		else
		{
			root->next[i] = root;
		}
	}
	while (!Q.empty())
	{
		node *cur = Q.front();
		Q.pop();
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (cur->next[i] != NIL)
			{
				cur->next[i]->fail = cur->fail->next[i];
				cur->next[i]->last = cur->next[i]->fail->id > 0 ? cur->next[i]->fail : cur->next[i]->fail->last;
				Q.push(cur->next[i]);
			}
			else
			{
				cur->next[i] = cur->fail->next[i];
			}
		}
	}
}

void print(node *cur, int shift)
{
	while (cur != root)
	{
		cnt[cur->id]++;
		cur = cur->last;
	}
}

void ac_automation()
{
	int l = strlen(t);
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		if (!(t[i] >= 'A' && t[i] <= 'Z'))
		{
			cur = root;
		}
		else
		{
			cur = cur->next[t[i] - 'A'];
		}
		if (cur->id > 0)
		{
			print(cur, i);
		}
		else
		{
			print(cur->last, i);
		}
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) > 0)
	{
		init_trie();
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s[i]);
			len[i] = strlen(s[i]);
			insert(s[i]);
			cnt[i] = 0;
		}
		init_fail();
		gets(t);
		gets(t);
		ac_automation();
		for (int i = 1; i <= n; i++)
		{
			if (cnt[i] > 0)
			{
				printf("%s: %d\n", s[i], cnt[i]);
			}
		}
	}
	return 0;
}
