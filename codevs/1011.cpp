#include <cstdio>

using namespace std;

int transform(int n)
{
	int res = 0;
	for (int i = 1; i * 2 <= n; i++)
	{
		res += transform(i) + 1;
	}
	return res;
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d", transform(n) + 1);
	return 0;
}
