// Problem Name: 败方树
// Description: 败方树的构建及更新

#include <cstdio>
#include <vector>

using namespace std;

struct node {
	node *p;
	int loser, winner, stamp;
	node() { }
	node(int loser, int winner) : p(NULL), loser(loser), winner(winner), stamp(0) { }
}**initial, **tree[20];

int tc[20], height, gstamp = 1;

void build(node **d, int n) {
	tree[height] = d;
	tc[height++] = n;
	if (n == 1) return;
	node **next = new node *[(n + 1) / 2];
	for (int i = 0; i + 1 < n; i += 2) {
		next[i / 2] = new node(max(d[i]->winner, d[i + 1]->winner), min(d[i]->winner, d[i + 1]->winner));
		d[i]->p = next[i / 2];
		d[i + 1]->p = next[i / 2];
	}
	if (n % 2 == 1) {
		next[n / 2] = d[n - 1];
	}
	build(next, (n + 1) / 2);
}

void update(int h, int p) {
	if (h == height) return;
	if (p * 2 + 1 < tc[h - 1]) {
		tree[h][p]->loser = max(tree[h - 1][p * 2]->winner, tree[h - 1][p * 2 + 1]->winner);
		tree[h][p]->winner = min(tree[h - 1][p * 2]->winner, tree[h - 1][p * 2 + 1]->winner);
	}
	update(h + 1, p / 2);
}

void print() {
	printf("%d", tree[height - 1][0]->winner);
	for (int i = height - 1; i > 0; i--) {
		for (int j = 0; j < tc[i]; j++) {
			if (tree[i][j]->stamp < gstamp) {
				printf(" %d", tree[i][j]->loser);
				tree[i][j]->stamp = gstamp;
			}
		}
	}
	puts("");
	gstamp++;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	initial = new node *[n];
	for (int i = 0; i < n; i++) {
		initial[i] = new node;
		scanf("%d", &initial[i]->winner);
	}
	build(initial, n);
	print();
	while (m--) {
		int p, v;
		scanf("%d%d", &p, &v);
		initial[p]->winner = v;
		update(1, p / 2);
		print();
	}
	return 0;
}
