#include <cstdio>
#include <cstring>

#define NIL 0

using namespace std;

struct node
{
	node *ch[4];
	int cnt;
	node() { memset(ch, 0, sizeof(ch)); cnt = 0; }
	void* operator new (size_t);
}*root, pool[400010];
int top = 0;

void* node::operator new (size_t)
{
	return pool + top++;
}

int cnt[20010];

inline int sorter(char ch)
{
	switch (ch)
	{
	case 'A':
		return 0;
	case 'G':
		return 1;
	case 'T':
		return 2;
	case 'C':
		return 3;
	default:
		return -1;
	}
}

void insert(char *s)
{
	node *u = root;
	int l = strlen(s);
	for (int i = 0; i < l - 1; i++)
	{
		if (u->ch[sorter(s[i])] == NIL)
		{
			u->ch[sorter(s[i])] = new node;
		}
		u = u->ch[sorter(s[i])];
	}
	u->cnt++;
}

void DFS(node *u)
{
	if (u != NIL)
	{
		cnt[u->cnt]++;
		for (int i = 0; i < 4; i++)
		{
			DFS(u->ch[i]);
		}
	}
}

int main()
{
	int n, l;
	char t[30];
	while (true)
	{
		scanf("%d%d", &n, &l);
		if (n == 0 && l == 0)
		{
			break;
		}
		top = 0;
		root = new node;
		for (int i = 0; i < n; i++)
		{
			scanf("%s", t);
			insert(t);
		}
		memset(cnt, 0, sizeof(cnt));
		DFS(root);
		for (int i = 1; i <= n; i++)
		{
			printf("%d\n", cnt[i]);
		}
	}
	return 0;
}
