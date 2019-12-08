// Problem Name: 置换选择排序

#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int m, n, R[100000];

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 0; i < m; i++) {
		scanf("%d", R + i);
	}
	priority_queue< int, vector<int>, greater<int> > Q;
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		Q.push(x);
	}
	int i = 0;
	while (i < m && !Q.empty()) {
		int x = Q.top();
		Q.pop();
		printf("%d ", x);
		if (R[i] >= x) {
			Q.push(R[i]);
		}
		i++;
	}
	puts("");
	return 0;
}
