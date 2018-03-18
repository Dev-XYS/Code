// Problem Name: Binary Cards
// Source: Codeforces Round #469 (Div. 1), Problem E

#include <cstdio>
#include <cstring>
#include <cassert>

#define INF 1000000000

using namespace std;

int n, ans_count = INF, deck[25], ans_deck[25];

inline int index(int i, int k)
{
	return i + (1 << k);
}

void solve(int k, int cnt[], int count)
{
	if (k == 0)
	{
		if (cnt[0] > 0 || cnt[2] > 0)
		{
			return;
		}
		if (cnt[0] > 0 && cnt[2] == 0)
		{
			deck[count++] = -(1 << 20);
		}
		else if (cnt[0] == 0 && cnt[2] > 0)
		{
			deck[count++] = 1 << 20;
		}
		if (count < ans_count)
		{
			ans_count = count;
			memcpy(ans_deck, deck, 100);
		}
	}
	else
	{
		bool has = false;
		for (int i = -(1 << k) + 1; i < (1 << k); i += 2)
		{
			if (cnt[index(i, k)] > 0)
			{
				has = true;
				break;
			}
		}
		int *next = new int[(1 << k) + 1];
		memset(next, 0, ((1 << k) + 1) * 4);
		for (int i = -(1 << k); i <= (1 << k); i++)
		{
			next[index((i + (i & 1)) >> 1, k - 1)] += cnt[index(i, k)];
		}
		deck[count] = -(1 << (20 - k));
		solve(k - 1, next, count + (has == true ? 1 : 0));
		memset(next, 0, ((1 << k) + 1) * 4);
		for (int i = -(1 << k); i <= (1 << k); i++)
		{
			next[index((i - (i & 1)) >> 1, k - 1)] += cnt[index(i, k)];
		}
		deck[count] = (1 << (20 - k));
		solve(k - 1, next, count + (has == true ? 1 : 0));
		delete[] next;
	}
}

int main()
{
	scanf("%d", &n);
	int a;
	int *next = new int[(1 << 21) + 1];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		next[index(a, 20)]++;
	}
	solve(20, next, 0);
	printf("%d\n", ans_count);
	for (int i = 0; i < ans_count; i++)
	{
		printf("%d ", ans_deck[i]);
	}
	return 0;
}
