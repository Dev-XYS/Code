#include <cstdio>
#include <unordered_map>

using namespace std;

int T, n, affect[30];

void init() {
	for (int i = 0; i < n; i++) {
		affect[i] = 1 << i;
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int start = 0;
		int end = 0;
		int x, y;
		unordered_map<int, int> M;
		init();
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			start |= (x << i);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			end |= (x << i);
		}
		while (true) {
			scanf("%d%d", &x, &y);
			if (x == 0 && y == 0) break;
			if (x > n || y > n) continue;
			x--;
			y--;
			affect[x] |= (1 << y);
		}
		int t = n / 2;
		for (int i = (1 << t) - 1; i >= 0; i--) {
			int mask = 0;
			for (int k = 0; k < t; k++) {
				if (i & (1 << k)) {
					mask ^= affect[k];
				}
			}
			if (M.count(mask)) {
				M[mask]++;
			}
			else {
				M[mask] = 1;
			}
		}
		int ans = 0;
		int s = 1 << t;
		for (int i = (1 << n) - s; i >= 0; i -= s) {
			int mask = start;
			for (int k = t; k < n; k++) {
				if (i & (1 << k)) {
					mask ^= affect[k];
				}
			}
			if (M.count(mask ^ end)) {
				ans += M[mask ^ end];
			}
		}
		if (ans) {
			printf("%d\n", ans);
		}
		else {
			printf("Oh,it's impossible~!!\n");
		}
	}
	return 0;
}
