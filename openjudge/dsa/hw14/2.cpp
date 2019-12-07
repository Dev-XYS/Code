// Problem Name: Binary Search Heap Construction

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

struct node {
	node *l, *r;
	char *label;
	int priority;
}N[50000];

int n;
char s[10000]; /* assume label lengths are less than 10000 characters */

node *merge(node *u, node *v) {
	if (u == NULL) return v;
	if (v == NULL) return u;
	if (u->priority > v->priority) {
		u->r = merge(u->r, v);
		return u;
	}
	else {
		v->l = merge(u, v->l);
		return v;
	}
}

inline bool _cmp_(const node &x, const node &y) {
	return strcmp(x.label, y.label) < 0;
}

node *build(int l, int r) {
	if (l == r) return N + l;
	int mid = (l + r) / 2;
	return merge(build(l, mid), build(mid + 1, r));
}

void print_and_release(node *u) {
	if (u == NULL) return;
	putchar('(');
	print_and_release(u->l);
	printf("%s/%d", u->label, u->priority);
	delete[] u->label;
	print_and_release(u->r);
	putchar(')');
}

int main() {
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			N[i].l = N[i].r = NULL;
			scanf(" %[a-z]/%d", s, &N[i].priority);
			N[i].label = new char[strlen(s) + 1];
			strcpy(N[i].label, s);
		}
		sort(N, N + n, _cmp_);
		print_and_release(build(0, n - 1));
		puts("");
	}
	return 0;
}
