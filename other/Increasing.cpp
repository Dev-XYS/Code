#include <cstdio>

#define INF 1000000000

using namespace std;

int n, len, least[100010];

int binary_search(int x)
{
	int l = 0, r = len;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (least[mid] > x) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main()
{
	int x;
	scanf("%d", &n);
	least[0] = -INF;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		x -= i;
		if (x >= least[len]) least[++len] = x;
		else least[binary_search(x)] = x;
	}
	printf("%d", n - len);
	return 0;
}
