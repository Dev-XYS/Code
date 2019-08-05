// Problem Name: Important Exam
// Source: Codeforces Round #577 (Div. 2), Problem A

#include <cstdio>

int n, m, cnt[1000][5];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		char ch[1001];
		scanf("%s", ch);
		for (int j = 0; j < m; j++) {
			cnt[j][ch[j] - 'A']++;
		}
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
		int max = 0;
		for (int j = 0; j < 5; j++) {
			if (cnt[i][j] > max) {
				max = cnt[i][j];
			}
		}
		int score;
		scanf("%d", &score);
		ans += score * max;
	}
	printf("%d\n", ans);
	return 0;
}
