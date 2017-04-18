// Problem Name: 完全平方数
// Source: [中山市选2011]

#include <cstdio>

using namespace std;

const int prime[] = { 4, 9, 25, 49, 121, 169, 289 };
const int pown1[] = { 1, -1, 1, -1, 1, -1, 1 };

int count(int n)
{
	int res = 0;
	for (int i = 0; i < (1 << 6); i++)
	{
		int c = 0, div = 1;
		for (int k = 0; k < 6; k++)
		{
			if ((i & (1 << k)) != 0)
			{
				c++;
				div *= prime[k];
			}
		}
		res += pown1[c] * n / div;
	}
	return res;
}

int solve(int k)
{
	int l = 1, r = k * 2;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (count(mid) >= k) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main()
{
	int T, k;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &k);
		printf("%d\n", solve(k));
	}
	return 0;
}
