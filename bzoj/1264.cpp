// Problem Name: 基因匹配 Match
// Source: [AHOI2006]

#include <cstdio>
#include <vector>

using namespace std;

int n, A[100010], B[100010], d[500010], mn[500010];
vector<int> pos[20010];

int lis()
{
	n *= 25;
	int len = 0;
	mn[0] = -1;
	for (int i = 0; i < n; i++)
	{
		if (d[i] > mn[len])
		{
			mn[++len] = d[i];
		}
		else
		{
			int l = 0, r = len;
			while (l < r)
			{
				int mid = (l + r) >> 1;
				if (mn[mid] < d[i]) l = mid + 1;
				else r = mid;
			}
			mn[l] = d[i];
		}
	}
	return len;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n * 5; i++)
	{
		scanf("%d", &A[i]);
	}
	for (int i = 0; i < n * 5; i++)
	{
		scanf("%d", &B[i]);
		pos[B[i]].push_back(i);
	}
	for (int i = 0; i < n * 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			d[i * 5 + j] = pos[A[i]][4 - j];
		}
	}
	printf("%d\n", lis());
	return 0;
}
