// Problem Name: 赛车
// Source: [JLOI2013]

#include <cstdio>

#define INF 1000000000

using namespace std;

int n, k[10010], v[10010], cnt, res[10010], rc;

int main()
{
	scanf("%d", &n);
	int *_read = k;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", _read++);
	}
	_read = v;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", _read++);
	}
	for (int i = 0; i < n; i++)
	{
		double last_slow = 0, first_fast = INF;
		for (int j = 0; j < n; j++)
		{
			if (j == i) continue;
			if (v[i] > v[j])
			{
				if (k[i] < k[j])
				{
					double t = (double)(k[j] - k[i]) / (double)(v[i] - v[j]);
					if (t > last_slow) last_slow = t;
				}
			}
			else if (v[i] < v[j])
			{
				if (k[i] >= k[j])
				{
					double t = (double)(k[i] - k[j]) / (double)(v[j] - v[i]);
					if (t < first_fast) first_fast = t;
				}
				else goto NEXT;
			}
			else
			{
				if (k[i] < k[j]) goto NEXT;
			}
			if (last_slow > first_fast) goto NEXT;
		}
		res[rc++] = i;
	NEXT:;
	}
	printf("%d\n%d", rc, res[0] + 1);
	for (int i = 1; i < rc; i++)
	{
		printf(" %d", res[i] + 1);
	}
	return 0;
}
