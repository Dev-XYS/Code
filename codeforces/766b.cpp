#include <cstdio>
#include <algorithm>

using namespace std;

int n, a[100010];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	for (int i = 2; i < n; i++)
	{
		if (a[i - 2] + a[i - 1] > a[i])
		{
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
