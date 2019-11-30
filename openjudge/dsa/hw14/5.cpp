#include <cstdio>
#include <cstring>

struct node {
	node *next[26];
	int cnt;
	node(int cnt = 1) : cnt(cnt) {
		memset(next, 0, sizeof(next));
	}
}*root;

int n;
char words[1000][21];

void init() {
	root = new node(-1);
}

void insert(char *s) {
	node *u = root;
	for (int l = strlen(s), i = 0; i < l; i++) {
		int x = s[i] - 'a';
		if (!u->next[x]) {
			u->next[x] = new node;
		}
		else {
			u->next[x]->cnt++;
		}
		u = u->next[x];
	}
}

void search_and_print(char *s) {
	node *u = root;
	for (int l = strlen(s), i = 0; i < l; i++) {
		if (u->cnt == 1) {
			break;
		}
		else {
			putchar(s[i]);
			u = u->next[s[i] - 'a'];
		}
	}
}

int main() {
	init();
	while (scanf("%s", words[n]) > 0) {
		insert(words[n++]);
	}
	for (int i = 0; i < n; i++) {
		printf("%s ", words[i]);
		search_and_print(words[i]);
		puts("");
	}
	return 0;
}
