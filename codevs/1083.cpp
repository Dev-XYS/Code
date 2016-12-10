#include <cstdio>

using namespace std;

int main()
{
	int n, a = 1, b = 1;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		if (a == 1 && (b & 1) == 1)
		{
			b++;
		}
		else if (b == 1 && (a & 1) == 0)
		{
			a++;
		}
		else if (((a + b) & 1) == 1)
		{
			a++;
			b--;
		}
		else
		{
			a--;
			b++;
		}
	}
	printf("%d/%d", a, b);
	return 0;
}
