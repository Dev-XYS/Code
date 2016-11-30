#include <cstdio>
#include <cstring>
#include <queue>

#define NIL 0
#define ALPHABET_SIZE 26

using namespace std;

struct node
{
	int cnt;
	node *next[ALPHABET_SIZE], *fail, *last;
	int id;
	bool matched;
	node();
}*root;

int idc = 1, ans;
node *tree[500010];
char t[1000010];

node::node() : cnt(0), fail(NIL), last(NIL), id(idc), matched(false)
{
	memset(next, 0, sizeof(next));
	tree[idc++] = this;
}

void init_trie()
{
	root = new node;
}

void insert(char *s)
{
	int l = strlen(s), x;
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		x = s[i] - 'a';
		if (cur->next[x] == NIL)
		{
			cur->next[x] = new node;
		}
		cur = cur->next[x];
	}
	cur->cnt++;
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
				cur->next[i]->last = cur->next[i]->fail->cnt > 0 ? cur->next[i]->fail : cur->next[i]->fail->last;
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
		//printf("matched with shift %d\n", shift);
		cur->matched = true;
		cur = cur->last;
	}
}

void ac_automation()
{
	int l = strlen(t);
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		cur = cur->next[t[i] - 'a'];
		if (cur->cnt > 0)
		{
			print(cur, i);
		}
		else
		{
			print(cur->last, i);
		}
	}
}

void debug()
{
	for (int i = 1; i < idc; i++)
	{
		printf("node %d :\n", i);
		for (int j = 0; j < ALPHABET_SIZE; j++)
		{
			printf("    next[%c] -> %d\n", (char)(j + 'a'), tree[i]->next[j]->id);
		}
		printf("    fail -> %d\n", tree[i]->fail->id);
		printf("    last -> %d\n", tree[i]->last->id);
	}
}

int main()
{
	int tc, n;
	char s[100];
	scanf("%d", &tc);
	while (tc--)
	{
		init_trie();
		scanf("%d", &n);
		while (n--)
		{
			scanf("%s", s);
			insert(s);
		}
		init_fail();
		scanf("%s", t);
		ac_automation();
		ans = 0;
		for (int i = 1; i < idc; i++)
		{
			if (tree[i]->matched == true)
			{
				ans += tree[i]->cnt;
			}
			delete tree[i];
		}
		printf("%d\n", ans);
		idc = 1;
	}
	return 0;
}
