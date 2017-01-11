#include <cstdio>

using namespace std;

int main()
{
	int n, x, cnt = 0, ans = -1000000001;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if (cnt == 0)
		{
			ans = x;
			cnt = 1;
		}
		else
		{
			if (ans == x) cnt++;
			else cnt--;
		}
	}
	printf("%d", ans);
	return 0;
}
