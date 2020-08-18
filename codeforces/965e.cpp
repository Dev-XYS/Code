#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

struct node {
    node *next[26];
    int mark;
    __gnu_pbds::priority_queue<int> Q;
    node(int mark = 0) : mark(mark) {
        memset(next, 0, sizeof(next));
    }
}*root;

int n;
char buf[100001];

void init() {
    root = new node(1);
}

void add(char *s) {
    node *u = root;
    while (*s) {
        if (u->next[*s - 'a'] == NULL) {
            u->next[*s - 'a'] = new node;
        }
        u = u->next[*s - 'a'];
        s++;
    }
    u->mark++;
}

int dfs(node *u, int depth) {
    int r = 0;
    for (int i = 0; i < 26; i++) {
        if (u->next[i]) {
            r += dfs(u->next[i], depth + 1);
            u->Q.join(u->next[i]->Q);
        }
    }
    if (u->mark == 0) {
        r -= u->Q.top();
        u->Q.pop();
    }
    u->Q.push(depth);
    return r + depth;
}

int main() {
    scanf("%d", &n);
    init();
    while (n--) {
        scanf("%s", buf);
        add(buf);
    }
    printf("%d\n", dfs(root, 0));
    return 0;
}
