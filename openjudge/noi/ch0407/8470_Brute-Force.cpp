// Problem Name: DNA

#include <algorithm>
#include <cstdio>
#include <cstring>

#define INF 1000000000

using namespace std;

int T, n, len[9], ans;
char s[9][16], t[15 * 9 + 1];
bool used[9];

void dfs(int k, int p, int l) {
	if (l >= ans) return;
	if (k == n) {
		if (l < ans) ans = l;
		return;
	}
	for (int w = 0; w < n; w++) {
		if (used[w] == true) continue;
		used[w] = true;
		for (int i = p; i <= l; i++) {
			bool can = true;
			for (int j = i; j < l && j - i < len[w]; j++) {
				if (s[w][j - i] != t[j]) {
					can = false;
					break;
				}
			}
			if (can) {
				int j;
				for (j = i; j - i < len[w]; j++) {
					t[j] = s[w][j - i];
				}
				dfs(k + 1, i, max(j, l));
				break;
			}
		}
		used[w] = false;
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", s[i]);
			len[i] = strlen(s[i]);
		}
		ans = INF;
		dfs(0, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
