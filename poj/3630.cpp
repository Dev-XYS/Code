#include <cstdio>
#include <cstring>

#define NIL 0

using namespace std;

struct node
{
	node *ch[10];
	bool has;
	node() { memset(ch, 0, sizeof(ch)); has = false; }
	void* operator new (size_t);
}*root, pool[100010];
int top = 0;

void* node::operator new (size_t)
{
	return pool + top++;
}

bool ans = false;

void insert(char *s)
{
	node *u = root;
	int l = strlen(s);
	for (int i = 0; i < l - 1; i++)
	{
		if (u->ch[s[i] - '0'] == NIL)
		{
			u->ch[s[i] - '0'] = new node;
		}
		u = u->ch[s[i] - '0'];
		if (u->has == true)
		{
			ans = true;
		}
	}
	if (u->ch[s[l - 1] - '0'] != NIL)
	{
		ans = true;
	}
	else
	{
		u->ch[s[l - 1] - '0'] = new node;
	}
	u->ch[s[l - 1] - '0']->has = true;
}

int main()
{
	int casen, n;
	char t[20];
	scanf("%d", &casen);
	while (casen--)
	{
		top = 0;
		root = new node;
		ans = false;
		scanf("%d", &n);
		while (n--)
		{
			scanf("%s", t);
			insert(t);
		}
		printf("%s\n", ans == false ? "YES" : "NO");
	}
	return 0;
}
