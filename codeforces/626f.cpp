#include <cstdio>
#include <algorithm>

#define MOD 1000000007

using namespace std;

int n, hn, K, a[201], dp[201][101][1001];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    a[0] = a[1];
    hn = n / 2;
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= hn; j++) {
            for (int k = 0; k <= K; k++) {
                int d = a[i] - a[i - 1];
                if (k - d * j >= 0) {
                    dp[i][j][k] += (long long)(j + 1) * dp[i - 1][j][k - d * j] % MOD;
                    dp[i][j][k] %= MOD;
                }
                if (j + 1 <= hn && k - d * (j + 1) >= 0) {
                    dp[i][j][k] += (long long)(j + 1) * dp[i - 1][j + 1][k - d * (j + 1)] % MOD;
                    dp[i][j][k] %= MOD;
                }
                if (j - 1 >= 0 && k - d * (j - 1) >= 0) {
                    dp[i][j][k] += dp[i - 1][j - 1][k - d * (j - 1)];
                    dp[i][j][k] %= MOD;
                }
            }
        }
    }
    int ans = 0;
    for (int k = 0; k <= K; k++) {
        ans = (ans + dp[n][0][k]) % MOD;
    }
    printf("%d\n", ans);
    return 0;
}
