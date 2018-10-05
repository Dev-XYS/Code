#pragma GCC optimize("O2")

#include <stdio.h>
#include <string.h>

#define INF 1000000000

/* BEGIN IO */

char _buffer_in_[5000], _buffer_out_[100];
int _pos_in_, _pos_out_;

void Iinit() {
	fread(_buffer_in_, 5000, 1, stdin);
}

int Iint() {
	while (_buffer_in_[_pos_in_] == '\n') _pos_in_++;
	int res = 0;
	do {
		res = res * 10 + (_buffer_in_[_pos_in_++] - '0');
	} while (_buffer_in_[_pos_in_] != '\n');
	return res;
}

void Istring(char *s) {
	while (_buffer_in_[_pos_in_] == '\n') _pos_in_++;
	int i = 0;
	do {
		s[i++] = _buffer_in_[_pos_in_++];
	} while (_buffer_in_[_pos_in_] != '\n');
}

void Oint(int x) {
	char buf[10];
	int i = 0;
	while (x > 0) {
		buf[i++] = (char)(x % 10 + '0');
		x /= 10;
	}
	if (i == 0) buf[i++] = '0';
	while (--i >= 0) {
		_buffer_out_[_pos_out_++] = buf[i];
	}
}

void Ostring(char *s) {
	for (int i = 0, l = strlen(s); i < l; i++) {
		_buffer_out_[_pos_out_++] = s[i];
	}
}

void Owrite() {
	fwrite(_buffer_out_, _pos_out_, 1, stdout);
}

/* END IO */

int t, n, mask2[1 << 15], steps[1 << 15], board[16], tmp[16];

void init() {
	for (int mask = (1 << 15) - 1; mask >= 0; mask--) {
		if ((mask & 1) != 0) {
			mask2[mask] ^= 3;
			steps[mask]++;
		}
		for (int i = 1; i < 15; i++) {
			if ((mask & (1 << i)) != 0) {
				mask2[mask] ^= (1 << i - 1) + (1 << i) + (1 << i + 1);
				steps[mask]++;
			}
		}
	}
}

int parse(char *s) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'w') res += (1 << i);
	}
	return res;
}

int main() {
	Iinit();
	//scanf("%d", &t);
	t = Iint();
	init();
	while (t--) {
		//scanf("%d", &n);
		n = Iint();
		char s[16];
		for (int i = 0; i < n; i++) {
			//scanf("%s", s);
			Istring(s);
			board[i] = parse(s);
		}
		int ans = INF;
		for (int mask = (1 << n) - 1; mask >= 0; mask--) {
			memcpy(tmp, board, sizeof(board));
			int step = steps[mask];
			tmp[1] ^= mask;
			tmp[0] ^= mask2[mask];
			tmp[0] &= (1 << n) - 1;
			for (int i = 1; i < n; i++) {
				int prev = tmp[i - 1];
				step += steps[prev];
				tmp[i + 1] ^= prev;
				tmp[i] ^= mask2[prev];
				tmp[i] &= (1 << n) - 1;
			}
			if (tmp[n - 1] == 0) {
				if (step < ans) ans = step;
			}
		}
		if (ans == INF) {
			//printf("inf\n");
			Ostring("inf\n");
		}
		else {
			//printf("%d\n", ans);
			Oint(ans);
			Ostring("\n");
		}
	}
	Owrite();
	return 0;
}
