#include <cstdio>

using namespace std;

int main()
{
	int t, n;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("%s\n", n <= 3 ? "1" : "-1");
	}
	return 0;
}
