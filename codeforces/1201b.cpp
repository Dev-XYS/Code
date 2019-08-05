// Problem Name: Zero Array
// Source: Codeforces Round #577 (Div. 2), Problem B

#include <cstdio>

int n;

int main() {
	scanf("%d", &n);
	int max = 0;
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		if (a > max) {
			max = a;
		}
		sum += a;
	}
	if (max <= sum - max && (sum & 1) == 0) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}
