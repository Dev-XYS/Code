#include <cstdio>
#include <cstring>

struct node {
    node *next[26];
    int cnt;
    node() : cnt(0) {
        memset(next, 0, sizeof(next));
    }
}*root;

int n;
char str[2000][21];

void init() {
    root = new node;
}

void add(char *s) {
    node *u = root;
    while (*s) {
        u->cnt++;
        if (u->next[*s - 'a'] == NULL) {
            u->next[*s - 'a'] = new node;
        }
        u = u->next[*s - 'a'];
        s++;
    }
    u->cnt++;
}

void print(char *s) {
    node *u = root;
    while (*s) {
        if (u->cnt == 1) {
            return;
        }
        putchar(*s);
        u = u->next[*s - 'a'];
        s++;
    }
}

int main() {
    char s[21];
    init();
    while (scanf("%s", s) > 0) {
        strcpy(str[n], s);
        n++;
        add(s);
    }
    for (int i = 0; i < n; i++) {
        printf("%s ", str[i]);
        print(str[i]);
        putchar('\n');
    }
    return 0;
}
