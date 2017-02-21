#include <cstdio>

using namespace std;

int n, len, least[1000010];

int binary_search(int x)
{
	int l = 0, r = len;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (x > least[mid]) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main()
{
	int x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		if (x > least[len]) least[++len] = x;
		else least[binary_search(x) + 1] = x;
	}
	printf("%d", len);
	return 0;
}
