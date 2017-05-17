// Problem Name: 阿狸的打字机
// Source: [NOI2011]

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define LOWBIT(x) ((x) & (-(x)))

#define NIL 0

using namespace std;

struct query
{
	int x, ord;
	query(int _x, int _ord) : x(_x), ord(_ord) { }
};

struct node
{
	node *next[26], *fail;
	vector<int> id;
	vector<node*> ch;
	int dfn, right;
	node() : fail(NIL), ch() { memset(next, 0, sizeof(next)); }
}*root;

char s[100010];
int m, sc, dfn, ans[100010];
node *pos[100010];
vector<query> qs[100010];
int f[100010];

void add(int p)
{
	while (p <= dfn)
	{
		f[p]++;
		p += LOWBIT(p);
	}
}

void sub(int p)
{
	while (p <= dfn)
	{
		f[p]--;
		p += LOWBIT(p);
	}
}

int sum(int p)
{
	int res = 0;
	while (p > 0)
	{
		res += f[p];
		p -= LOWBIT(p);
	}
	return res;
}

void build()
{
	int len = strlen(s);
	root = new node;
	static node *S[100010];
	int sp = 0;
	S[sp++] = root;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == 'B') sp--;
		else if (s[i] == 'P') S[sp - 1]->id.push_back(++sc), pos[sc] = S[sp - 1];
		else
		{
			int x = s[i] - 'a';
			if (S[sp - 1]->next[x] == NIL) S[sp - 1]->next[x] = new node;
			S[sp] = S[sp - 1]->next[x], sp++;
		}
	}
}

void init_fail()
{
	queue<node*> Q;
	root->fail = root;
	for (int i = 0; i < 26; i++)
	{
		if (root->next[i] != NIL)
		{
			root->next[i]->fail = root, root->ch.push_back(root->next[i]);
			Q.push(root->next[i]);
		}
	}
	while (!Q.empty())
	{
		node *u = Q.front();
		Q.pop();
		for (int i = 0; i < 26; i++)
		{
			if (u->next[i] != NIL)
			{
				node *p = u->fail;
				while (p != root && p->next[i] == NIL) p = p->fail;
				if (p->next[i] != NIL) u->next[i]->fail = p->next[i], p->next[i]->ch.push_back(u->next[i]);
				else u->next[i]->fail = p, p->ch.push_back(u->next[i]);
				Q.push(u->next[i]);
			}
		}
	}
}

void dfs_fail(node *u)
{
	u->dfn = ++dfn;
	for (int i = 0; i < (int)u->ch.size(); i++)
	{
		dfs_fail(u->ch[i]);
	}
	u->right = dfn;
}

void dfs_trie(node *u)
{
	add(u->dfn);
	for (int i = 0; i < (int)u->id.size(); i++)
	{
		for (int j = 0; j < (int)qs[u->id[i]].size(); j++)
		{
			ans[qs[u->id[i]][j].ord] = sum(pos[qs[u->id[i]][j].x]->right) - sum(pos[qs[u->id[i]][j].x]->dfn - 1);
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (u->next[i] != NIL) dfs_trie(u->next[i]);
	}
	sub(u->dfn);
}

int main()
{
	scanf("%s%d", s, &m);
	int x, y;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &x, &y);
		qs[y].push_back(query(x, i));
	}
	build();
	init_fail();
	dfs_fail(root);
	dfs_trie(root);
	for (int i = 0; i < m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
