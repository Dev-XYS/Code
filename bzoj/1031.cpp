#include <cstdio>
#include <cstring>

using namespace std;

struct sort_info
{
	int a, b, ord;
	sort_info(int _a = 0, int _b = 0, int _ord = 0) : a(_a), b(_b), ord(_ord) { }
	inline bool operator == (const sort_info &x) { return a == x.a && b == x.b; }
};

char s[200010];
int len, rank[400010], sa[400010], cnt[200010];

void radix_sort(sort_info *d)
{
	static sort_info _d[200010];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < len; i++)
	{
		cnt[d[i].b]++;
	}
	for (int i = 1; i <= len; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = len - 1; i >= 0; i--)
	{
		_d[--cnt[d[i].b]] = d[i];
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < len; i++)
	{
		cnt[_d[i].a]++;
	}
	for (int i = 1; i <= len; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = len - 1; i >= 0; i--)
	{
		d[--cnt[_d[i].a]] = _d[i];
	}
}

void init_rank()
{
	for (int i = 0; i < len; i++)
	{
		cnt[(int)s[i]]++;
	}
	int _rank[256];
	_rank[0] = 0;
	for (int i = 1; i < 256; i++)
	{
		_rank[i] = cnt[i] == 0 ? _rank[i - 1] : (_rank[i - 1] + 1);
	}
	for (int i = 0; i < len; i++)
	{
		rank[i] = _rank[(int)s[i]];
	}
	for (int l = 1; l < len; l <<= 1)
	{
		static sort_info d[200010];
		for (int i = 0; i < len; i++)
		{
			d[i] = sort_info(rank[i], rank[i + l], i);
		}
		radix_sort(d);
		int k = 1;
		rank[d[0].ord] = 1;
		for (int i = 1; i < len; i++)
		{
			rank[d[i].ord] = d[i] == d[i - 1] ? k : ++k;
		}
		if (k == len) break;
	}
}

void init_sa()
{
	for (int i = 0; i < len; i++)
	{
		sa[rank[i]] = i;
	}
}

int main()
{
	scanf("%s", s);
	len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		s[i + len] = s[i];
	}
	len <<= 1;
	init_rank();
	init_sa();
	for (int i = 1; i <= len; i++)
	{
		if (sa[i] < (len >> 1)) printf("%c", s[sa[i] + (len >> 1) - 1]);
	}
	return 0;
}
