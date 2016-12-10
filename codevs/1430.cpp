#include <cstdio>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			printf("\\n");
			return 0;
		}
	}
	printf("\\t");
	return 0;
}
