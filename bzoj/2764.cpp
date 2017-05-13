// Problem Name: 基因补全
// Source: [JLOI2011]

#include <cstdio>

#define L 200

typedef unsigned char byte;

using namespace std;

int l1, l2, cnt[26];
char s1[2010], s2[2010];
byte dp[2010][L + 1];
int len[2010];

void add(byte *a, byte *b)
{
	int d = 0;
	for (int i = 0; i <= L; i++)
	{
		d += a[i] + b[i];
		a[i] = d % 10;
		d /= 10;
	}
}

void mov(byte *a, int x)
{
	int i = 0;
	while (x > 0)
	{
		a[i++] = x % 10;
		x /= 10;
	}
}

void out(byte *a)
{
	int i;
	for (i = L; i >= 0; i--)
	{
		if (a[i] != 0) break;
	}
	if (i == -1) printf("0");
	for (; i >= 0; i--)
	{
		printf("%c", (char)(a[i] + '0'));
	}
}

inline char convert(char x)
{
	switch (x)
	{
	case 'A':
		return 'T';
	case 'T':
		return 'A';
	case 'C':
		return 'G';
	case 'G':
		return 'C';
	default:
		return 0;
	}
}

int main()
{
	scanf("%d%d%s%s", &l1, &l2, s1, s2);
	for (int i = 0; i < l2; i++)
	{
		s2[i] = convert(s2[i]);
	}
	for (int i = 0; i < l1; i++)
	{
		for (int j = l2 - 1; j > 0; j--)
		{
			if (s1[i] == s2[j]) add(dp[j], dp[j - 1]);
		}
		cnt[s1[i] - 'A']++;
		mov(dp[0], cnt[s2[0] - 'A']);
	}
	out(dp[l2 - 1]);
	return 0;
}
