// Problem Name: 发现它，抓住它

#include <cstdio>

int T, n, m, p[100001];
bool d[100001];

void init() {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		d[i] = false;
	}
}

int getrt(int x) {
	if (p[x] == x) return x;
	int r = getrt(p[x]);
	d[x] ^= d[p[x]];
	return p[x] = r;
}

void diff(int x, int y) {
	int rx = getrt(x), ry = getrt(y);
	if (rx == ry) return;
	p[rx] = ry;
	d[rx] = d[x] ^ d[y] ^ true;
}

void query(int x, int y) {
	int rx = getrt(x), ry = getrt(y);
	if (rx != ry) {
		puts("Not sure yet.");
	}
	else {
		puts(d[x] ^ d[y] ? "In different gangs." : "In the same gang.");
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		init();
		while (m--) {
			char op[2];
			int x, y;
			scanf("%s%d%d", op, &x, &y);
			if (op[0] == 'A') query(x, y);
			else diff(x, y);
		}
	}
	return 0;
}
