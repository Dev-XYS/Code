#include <cstdio>

#define INF 2147483647

int n, K, t, d[5000][5];

inline int sqr(int x) {
	return x * x;
}

int main() {
	while (scanf("%d%d", &n, &K) > 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < K; j++) {
				scanf("%d", &d[i][j]);
			}
		}
		scanf("%d", &t);
		while (t--) {
			int p[5], M;
			for (int i = 0; i < K; i++) {
				scanf("%d", p + i);
			}
			scanf("%d", &M);
			printf("the closest %d points are:\n", M);
			for (int k = 0; k < M; k++) {
				int min_ind = k;
				int min_dist = INF;
				for (int i = k; i < n; i++) {
					int dist = 0;
					for (int j = 0; j < K; j++) {
						dist += sqr(d[i][j] - p[j]);
					}
					if (dist < min_dist) {
						min_ind = i;
						min_dist = dist;
					}
				}
				for (int j = 0; j < K; j++) {
					int tmp = d[min_ind][j];
					d[min_ind][j] = d[k][j];
					d[k][j] = tmp;
					printf("%d ", tmp);
				}
				puts("");
			}
		}
	}
	return 0;
}
