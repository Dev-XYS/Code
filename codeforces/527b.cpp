#include <cstdio>
#include <cstring>

int n, ind[26][26], hd;
char s[200002], t[200002];

void get_Hamming_distance() {
    for (int i = 1; i <= n; i++) {
        hd += (s[i] != t[i]);
    }
}

int main() {
    scanf("%d%s%s", &n, s + 1, t + 1);
    get_Hamming_distance();
    for (int i = 1; i <= n; i++) {
        int x = s[i] - 'a', y = t[i] - 'a';
        if (x == y) continue;
        if (ind[y][x] != 0) {
            printf("%d\n%d %d\n", hd - 2, ind[y][x], i);
            return 0;
        }
        ind[x][y] = i;
    }
    memset(ind, 0, sizeof(ind));
    for (int i = 1; i <= n; i++) {
        int x = s[i] - 'a', y = t[i] - 'a';
        if (x == y) continue;
        for (int k = 0; k < 26; k++) {
            if (ind[k][x] != 0) {
                printf("%d\n%d %d\n", hd - 1, ind[k][x], i);
                return 0;
            }
            if (ind[y][k] != 0) {
                printf("%d\n%d %d\n", hd - 1, ind[y][k], i);
                return 0;
            }
        }
        ind[x][y] = i;
    }
    printf("%d\n-1 -1\n", hd);
    return 0;
}
