#include <cstdio>

using namespace std;

int main()
{
	int n, c = 1, ans = 0;
	scanf("%d", &n);
	while (n - c >= 0)
	{
		n -= c;
		ans++;
		c <<= 1;
	}
	if (n > 0)
	{
		ans++;
	}
	printf("%d", ans);
	return 0;
}
