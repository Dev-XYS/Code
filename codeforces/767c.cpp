#include <cstdio>

using namespace std;

struct vertex
{
	int first, w, sum;
	bool del;
}V[1000010];

struct edge
{
	int endp, next;
}E[1000010];

int ivc, ec = 1, part, cut[2], id;
bool found = false;

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	V[u].sum = V[u].w;
	for (int cur = V[u].first; cur != 0 && found == false; cur = E[cur].next)
	{
		if (V[E[cur].endp].del == false)
		{
			DFS(E[cur].endp);
			V[u].sum += V[E[cur].endp].sum;
		}
	}
	if (V[u].sum == part && found == false)
	{
		V[u].del = true;
		cut[id] = u;
		found = true;
	}
}

int main()
{
	int p, w, sum = 0, root;
	scanf("%d", &ivc);
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%d%d", &p, &w);
		V[i].w = w;
		sum += w;
		if (p != 0) add_edge(p, i);
		else root = i;
	}
	if (sum % 3 != 0)
	{
		printf("-1");
	}
	else
	{
		part = sum / 3;
		id = 0;
		DFS(root);
		if (found == false)
		{
			printf("-1");
			return 0;
		}
		found = false;
		id = 1;
		DFS(root);
		if (found == false)
		{
			printf("-1");
			return 0;
		}
		if (cut[0] != root && cut[1] != root) printf("%d %d", cut[0], cut[1]);
		else printf("-1");
	}
	return 0;
}
