#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

struct matrix {
    ll data[101][101];
    matrix() {
        memset(data, 0, sizeof(data));
    }
    ll *operator [] (int i) {
        return data[i];
    }
}E;

int n, m, k;

matrix operator * (matrix &x, matrix &y) {
    matrix r;
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k <= n; k++) {
            if (x[i][k] == 0) continue;
            for (int j = 0; j <= n; j++) {
                r[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return r;
}

matrix qpow(matrix x, int k) {
    if (k == 0) {
        return E;
    }
    matrix r = qpow(x * x, k >> 1);
    return (k & 1) == 0 ? r : r * x;
}

void init() {
    for (int i = 0; i <= 100; i++) {
        E[i][i] = 1;
    }
}

int main() {
    init();
    while (true) {
        scanf("%d%d%d", &n, &m, &k);
        if (n == 0 && m == 0 && k == 0) break;
        matrix M = E;
        while (k--) {
            char op[2];
            int x, y;
            scanf("%s%d", op, &x);
            if (op[0] == 'g') {
                M.data[x][0]++;
            }
            else if (op[0] == 'e') {
                memset(M[x], 0, 101 * sizeof(ll));
            }
            else {
                scanf("%d", &y);
                for (int i = 0; i <= n; i++) {
                    swap(M[x][i], M[y][i]);
                }
            }
        }
        M = qpow(M, m);
        printf("%lld", M[1][0]);
        for (int i = 2; i <= n; i++) {
            printf(" %lld", M[i][0]);
        }
        puts("");
    }
    return 0;
}
