// Problem Name: [HAOI2009] 逆序对数列

#include <cstdio>
#include <cstring>
 
#define MOD 10000
 
using namespace std;
 
int dp[1010][1010];
 
inline int min(int x, int y)
{
    return x < y ? x : y;
}
 
int solve(int n, int k)
{
    if (dp[n][k] != -1) return dp[n][k];
    if (k == 0) return 1;
    dp[n][k] = 0;
    for (int i = min(n - 1, k); i >= 0; i--)
    {
        dp[n][k] = (dp[n][k] + solve(n - 1, k - i)) % MOD;
    }
    return dp[n][k];
}
 
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    memset(dp, -1, sizeof(dp));
    printf("%d", solve(n, k));
    return 0;
}
