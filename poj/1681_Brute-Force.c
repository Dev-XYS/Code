#include <stdio.h>

#define INF 1000000000

int t, n;
char board[15][16], tmp[15][16];

void copy() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp[i][j] = board[i][j];
		}
	}
}

void reverse(int x, int y) {
	if (tmp[x][y] == 'w') tmp[x][y] = 'y';
	else tmp[x][y] = 'w';
}

void paint(int x, int y) {
	reverse(x, y);
	if (x > 0) reverse(x - 1, y);
	if (x < n - 1) reverse(x + 1, y);
	if (y > 0) reverse(x, y - 1);
	if (y < n - 1) reverse(x, y + 1);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", board[i]);
		}
		int ans = INF;
		for (int mask = (1 << n) - 1; mask >= 0; mask--) {
			int step = 0;
			copy();
			for (int j = 0; j < n; j++) {
				if ((mask & (1 << j)) != 0) {
					paint(0, j);
					step++;
				}
			}
			for (int i = 1; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (tmp[i - 1][j] == 'w') {
						paint(i, j);
						step++;
					}
				}
			}
			int complete = 1;
			for (int j = 0; j < n; j++) {
				if (tmp[n - 1][j] == 'w') {
					complete = 0;
					break;
				}
			}
			if (complete) {
				if (step < ans) {
					ans = step;
				}
			}
		}
		if (ans == INF) {
			printf("inf\n");
		}
		else {
			printf("%d\n", ans);
		}
	}
	return 0;
}
