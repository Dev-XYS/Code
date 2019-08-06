// Problem Name: Maximum Median
// Source: Codeforces Round #577 (Div. 2), Problem C

#include <algorithm>
#include <cstdio>

using namespace std;

int n, k, a[200000];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	sort(a, a + n);
	int p = n >> 1;
	int ans = a[p];
	while (true) {
		int v = a[p];
		while (p < n && a[p] == v) {
			p++;
		}
		if (p == n) {
			break;
		}
		if (k / (p - (n >> 1)) >= a[p] - ans) {
			k -= (p - (n >> 1)) * (a[p] - ans);
			ans = a[p];
		}
		else {
			ans += k / (p - (n >> 1));
			k %= (p - (n >> 1));
			goto END;
		}
	}
END:
	printf("%d\n", ans + k / ((n >> 1) + 1));
	return 0;
}
